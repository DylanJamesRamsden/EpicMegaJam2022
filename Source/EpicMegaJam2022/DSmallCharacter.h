// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DCharacter.h"
#include "DSmallCharacter.generated.h"

/**
 * 
 */
UCLASS()
class EPICMEGAJAM2022_API ADSmallCharacter : public ADCharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ADSmallCharacter();

protected:

	virtual void MoveHorizontal(float Value) override;

	void MoveVertical(float Value);

	virtual void Interact() override;
	
	virtual void OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;
	
	virtual void OnEndOverlap(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) override;

	// Determines if the character can swing or not (set based on if the character is in the range of a swinging hook)
	bool bCanSwing;

	// Determines if the character is currently swinging or not
	bool bIsSwinging;

	// Currently just storing this as we need a reference to it when the character needs to end their swing
	UPROPERTY()
	ADSwingingHook* AvailableSwingingHook;

	// Used as a check after a swing to level out the character's rotation when falling to the ground
	bool bResetRotationOnSwing;

	// Determines whether or not the character is climbing on a ladder
	bool bIsClimbingLadder;

public:

	UPROPERTY(EditDefaultsOnly, Category = "Movement | Swinging")
	float RateToResetRotationOnSwing;

	UPROPERTY(EditDefaultsOnly, Category = "Movement | Swinging")
	float SwingHorizontalVelocity = 100000.0f;

	virtual void Tick(float DeltaSeconds) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
};
