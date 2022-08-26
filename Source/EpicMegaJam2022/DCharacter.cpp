// Fill out your copyright notice in the Description page of Project Settings.


#include "DCharacter.h"

#include "DrawDebugHelpers.h"
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
	
}

void ADCharacter::MoveHorizontal(float Value)
{
	if (!bLockMovement)
	{
		AddMovementInput(FVector::RightVector * Value);	
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

