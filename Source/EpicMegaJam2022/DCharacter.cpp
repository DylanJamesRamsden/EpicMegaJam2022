// Fill out your copyright notice in the Description page of Project Settings.


#include "DCharacter.h"

#include "DrawDebugHelpers.h"
#include "DSwingingHook.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ADCharacter::ADCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Changing our air control so our character has more control in the air when jumping
	GetCharacterMovement()->AirControl = 0.35f;
}

// Called when the game starts or when spawned
void ADCharacter::BeginPlay()
{
	Super::BeginPlay();

	// Binding our custom OnOverlapBegin and OnOverlapEnd functions to the BoxComponent's overlap events
	GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &ADCharacter::OnBeginOverlap);
	GetCapsuleComponent()->OnComponentEndOverlap.AddDynamic(this, &ADCharacter::OnEndOverlap);
}

void ADCharacter::MoveHorizontal(float Value)
{
	if (!bIsSwinging)
	{
		if (!bLockMovement)
		{
			AddMovementInput(FVector::RightVector * Value);	
		}	
	}
	else
	{
		// If the character is swinging, we cannot use the build in ACharacter functionality for movement as we are simulating
		// physics. So we need to add a force to move left and right.
		GetCapsuleComponent()->AddForce(GetActorRightVector() * SwingHorizontalVelocity * Value);
	}
}

void ADCharacter::JumpStart()
{
	// We can only start charging a jump if we are not falling
	if (!GetCharacterMovement()->IsFalling())
	{
		bIsChargingJump = true;
	}
	else
	{
		bIsBufferingJump = true;
	}
}

void ADCharacter::JumpEnd()
{
	// We can only stop charging a jump and jump if we are not falling
	if (!GetCharacterMovement()->IsFalling())
	{
		// We get our jump velocity based on a lerp between our min jump and max jump. The alpha is our jump charge
		const float JumpVelocity = FMath::Lerp(MinJumpVelocity, MaxJumpVelocity, JumpCharge);

		LaunchCharacter(FVector(0.0f, 0.0f, JumpVelocity), false, false);

		JumpCharge = 0;
		bIsChargingJump = false;
		bLockMovement = false;
	}
	else
	{
		if (bIsBufferingJump) bIsBufferingJump = false;
	}
}

void ADCharacter::Smash()
{
	if (!bSmashing && GetCharacterMovement()->IsFalling())
	{
		bSmashing = true;
		
		LaunchCharacter(FVector(0.0f, 0.0f, SmashVelocity), true, true);
	}
}

void ADCharacter::OnSmashMovementLockComplete() const
{
	GetCharacterMovement()->SetDefaultMovementMode();
}

void ADCharacter::Interact()
{
	if (!bIsSwinging)
	{
		// If we can swing and we have an available swinging hook, we enable the swing
		if (bCanSwing && AvailableSwingingHook)
		{
			AvailableSwingingHook->EnableSwinging(this);
			bIsSwinging = true;
		}	
	}
	else
	{
		// If we interact again while we are swinging, we disable the swing
		if (AvailableSwingingHook)
		{
			// Storing the characters physics linear velocity before we end the swing, so we can apply it as a velocity on
			// the character with LaunchCharacter as they are no longer simulating physics
			FVector LinearSwingVelocity = GetCapsuleComponent()->GetPhysicsLinearVelocity();
			
			AvailableSwingingHook->DisableSwinging(this);
			bIsSwinging = false;
			bResetRotationOnSwing = true;

			LaunchCharacter(FVector(LinearSwingVelocity), true, true);
		}
	}
}

void ADCharacter::OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
                                 UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->IsA(ADSwingingHook::StaticClass()))
	{
		// If the character has overlapped with a swinging hook, we store it and set CanSwing to true
		if (ADSwingingHook* SwingingHook = Cast<ADSwingingHook>(OtherActor))
		{
			AvailableSwingingHook = SwingingHook;
			bCanSwing = true;
		}
	}
}

void ADCharacter::OnEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex)
{
	if (OtherActor->IsA(ADSwingingHook::StaticClass()))
	{
		if (ADSwingingHook* SwingingHook = Cast<ADSwingingHook>(OtherActor))
		{
			// Only if the character isn't already swinging, we set CanSwing to false when ending an overlap with the swinging hook
			if (!bIsSwinging && AvailableSwingingHook == SwingingHook)
			{
				AvailableSwingingHook = nullptr;
				bCanSwing = false;
			}
		}
	}
}

// Called every frame
void ADCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	//Created this variable and putting in tick just because I know we will need some UI/cosmetic updates
	if (bIsChargingJump)
	{
		JumpCharge = FMath::Clamp<float>((DeltaTime / JumpChargeDuration) + JumpCharge, 0, 1);

		if (MovementLockThresholdOnJumpCharge > 0)
		{
			if (JumpCharge >= MovementLockThresholdOnJumpCharge)
			{
				bLockMovement = true;
			}	
		}
		
		DrawDebugString(GetWorld(), FVector(GetActorLocation().X, GetActorLocation().Y, GetActorLocation().Z + 400.0f),
			FString::SanitizeFloat(JumpCharge), NULL, FColor::Yellow, 0.0f, false, 2);
	}

	// Level out the characters rotation when falling to the ground after a swing
	if (bResetRotationOnSwing)
	{
		FRotator OldRotation(0, 0, 0);
		FRotator CurrentRotation = GetActorRotation();

		SetActorRotation(FMath::InterpEaseIn(CurrentRotation, OldRotation, RateToResetRotationOnSwing, 1));

		// If our characters rotation is equal to zero (which is our default), we stop levelling out the rotation
		if (GetActorRotation() == FRotator::ZeroRotator)
		{
			bResetRotationOnSwing = false;
		}
	}
}

// Called to bind functionality to input
void ADCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveHorizontal", this, &ADCharacter::MoveHorizontal);

	//PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ADCharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ADCharacter::JumpStart);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ADCharacter::JumpEnd);

	PlayerInputComponent->BindAction("Smash", IE_Pressed, this, &ADCharacter::Smash);
	PlayerInputComponent->BindAction("Interact", IE_Pressed, this, &ADCharacter::Interact);
}

void ADCharacter::Landed(const FHitResult& Hit)
{
	Super::Landed(Hit);

	if (bIsBufferingJump)
	{
		bIsChargingJump = true;
		bIsBufferingJump = false;
	}

	if (bSmashing)
	{
		bSmashing = false;

		if (SmashMovementLockOnHitTime > 0)
		{
			// Disables our movement on smash impact
			GetCharacterMovement()->DisableMovement();
			
			FTimerHandle SmashMovementLockTimerHandle;
			GetWorldTimerManager().SetTimer(SmashMovementLockTimerHandle, this, &ADCharacter::OnSmashMovementLockComplete,
				SmashMovementLockOnHitTime, false);
		}

		UGameplayStatics::PlayWorldCameraShake(this, SmashCameraShake,GetActorLocation(), 0.0f, 5000, 1);
	}
}

