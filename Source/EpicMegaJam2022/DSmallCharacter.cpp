// Fill out your copyright notice in the Description page of Project Settings.


#include "DSmallCharacter.h"

#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

ADSmallCharacter::ADSmallCharacter()
{
	// Changing our air control so our character has more control in the air when jumping
	GetCharacterMovement()->AirControl = 0.20f;
}

void ADSmallCharacter::MoveHorizontal(float Value)
{
	if (bIsSwinging)
	{
		GetCapsuleComponent()->AddForce(GetActorRightVector() * SwingHorizontalVelocity * Value);
	}
	else Super::MoveHorizontal(Value);
}

void ADSmallCharacter::Interact()
{
	Super::Interact();

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

void ADSmallCharacter::OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
                                      UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Super::OnBeginOverlap(OverlappedComp, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);

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

void ADSmallCharacter::OnEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	Super::OnEndOverlap(OverlappedComp, OtherActor, OtherComp, OtherBodyIndex);

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

void ADSmallCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

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
