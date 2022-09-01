// Fill out your copyright notice in the Description page of Project Settings.


#include "DCharacter.h"

#include "DDoor.h"
#include "DKey.h"
#include "DLeaver.h"
#include "DPlayerState.h"
#include "DPressurePlate.h"
#include "DrawDebugHelpers.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ADCharacter::ADCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>("SpringArmComponent");
	CameraComponent = CreateDefaultSubobject<UCameraComponent>("CameraComponent");

	SpringArmComponent->SetupAttachment(RootComponent);
	CameraComponent->SetupAttachment(SpringArmComponent);

	SpringArmComponent->bEnableCameraLag = true;

	SpringArmComponent->TargetArmLength = 2000;
	SpringArmComponent->SetRelativeRotation(FRotator(-30.0f, 0.0f, 0.0f));
	SpringArmComponent->SetUsingAbsoluteRotation(true);
	SpringArmComponent->bDoCollisionTest = false;

	// Changing our air control so our character has more control in the air when jumping
	GetCharacterMovement()->AirControl = 0.35f;
	//WE still want our pawn to run physics even if it isn't possessed
	GetCharacterMovement()->bRunPhysicsWithNoController = true;
}

// Called when the game starts or when spawned
void ADCharacter::BeginPlay()
{
	Super::BeginPlay();

	// Binding our custom OnOverlapBegin and OnOverlapEnd functions to the BoxComponent's overlap events
	GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &ADCharacter::OnBeginOverlap);
	GetCapsuleComponent()->OnComponentEndOverlap.AddDynamic(this, &ADCharacter::OnEndOverlap);

	StartLocation = GetActorLocation();
}

void ADCharacter::MoveHorizontal(float Value)
{
	if (!bLockMovement)
	{
		AddMovementInput(FVector::RightVector * Value);

		/*if (Value != 0)
		{
			if (Value > 0)
			{
				if (!bIsWalkingRight)
				{
					bIsWalkingRight = true;

					GetMesh()->SetWorldRotation(FRotator(0.0f, 0.0f, 0.0f));
				}
			}
			else
			{
				if (bIsWalkingRight)
				{
					bIsWalkingRight = false;

					GetMesh()->SetWorldRotation(FRotator(0.0f, 180.0f, 0.0f));
				}
			}
		}*/
	}	
}

void ADCharacter::JumpStart()
{
	// We can only start charging a jump if we are not falling
	if (!GetCharacterMovement()->IsFalling())
	{
		bIsChargingJump = true;

		if (ChargeJumpAnimation)
		{
			float AnimLength = PlayAnimMontage(ChargeJumpAnimation);
		}
		

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
		if (bIsChargingJump)
		{
			// We get our jump velocity based on a lerp between our min jump and max jump. The alpha is our jump charge
			const float JumpVelocity = FMath::Lerp(MinJumpVelocity, MaxJumpVelocity, JumpCharge);

			LaunchCharacter(FVector(0.0f, 0.0f, JumpVelocity), false, false);

			JumpCharge = 0;
			bIsChargingJump = false;
			bLockMovement = false;

			if (ChargeJumpAnimation)
			{
				StopAnimMontage();
			}
		}
	}
	else
	{
		if (bIsBufferingJump) bIsBufferingJump = false;
	}
}

void ADCharacter::Interact()
{
	if (bCanInteractWithInteractable)
	{
		if (InteractableActor->IsA(ADKey::StaticClass()))
		{
			if (ADPlayerState* PS = GetPlayerState<ADPlayerState>())
			{
				PS->PickupKey();
			}
		}
		else if (InteractableActor->IsA(ADDoor::StaticClass()))
		{
			if (ADPlayerState* PS = GetPlayerState<ADPlayerState>())
			{
				if (!PS->HasKey()) return;
			}
		}

		InteractableActor->StartMirroredAction();
	}
}

void ADCharacter::OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
                                 UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// @TODO We need an interact interface (thought we didn't need it)
	if (OtherActor->IsA(ADLeaver::StaticClass()) ||
		OtherActor->IsA(ADDoor::StaticClass()) ||
		OtherActor->IsA(ADKey::StaticClass()))
	{
		InteractableActor = Cast<ADMirroredActor>(OtherActor);
		
		bCanInteractWithInteractable = true;
	}
	else if (OtherActor->IsA(ADPressurePlate::StaticClass()))
	{
		ADActivator* PressurePlate = Cast<ADActivator>(OtherActor);
		PressurePlate->StartMirroredAction();
	}
}

void ADCharacter::OnEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex)
{
	if (OtherActor == InteractableActor)
	{
		InteractableActor = nullptr;
		
		bCanInteractWithInteractable = false;
	}
	else if (OtherActor->IsA(ADPressurePlate::StaticClass()))
	{
		ADActivator* PressurePlate = Cast<ADActivator>(OtherActor);
		PressurePlate->StartMirroredAction();
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
}

// Called to bind functionality to input
void ADCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveHorizontal", this, &ADCharacter::MoveHorizontal);

	//PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ADCharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ADCharacter::JumpStart);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ADCharacter::JumpEnd);
	
	PlayerInputComponent->BindAction("Interact", IE_Pressed, this, &ADCharacter::Interact);
}

void ADCharacter::Landed(const FHitResult& Hit)
{
	Super::Landed(Hit);

	if (bIsBufferingJump)
	{
		bIsChargingJump = true;
		bIsBufferingJump = false;

		if (ChargeJumpAnimation)
		{
			float AnimLength = PlayAnimMontage(ChargeJumpAnimation);
		}
	}
}

void ADCharacter::FellOutOfWorld(const UDamageType& dmgType)
{
	// We just overwrite fell out of world and set our character's location to the location they started in
	SetActorLocation(StartLocation);

	if (bIsChargingJump)
	{
		bIsChargingJump = false;
		bLockMovement = false;
	}
}

