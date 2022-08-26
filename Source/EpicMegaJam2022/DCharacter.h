// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "DCharacter.generated.h"

UCLASS()
class EPICMEGAJAM2022_API ADCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ADCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Moves the character either right or left, depending on the player input
	void MoveHorizontal(float Value);

	void JumpStart();

	void JumpEnd();

	// A value between 0 and 1, determining how much of our jump has been charged (0 being none and 1 being full)
	float JumpCharge;

	bool bIsChargingJump;
	
	float bIsFalling;

	// Used as a buffer when the player tries to charge a jump while they are falling
	// When they hit the ground, the jump will start charging
	bool bIsBufferingJump;

	bool bLockMovement;

public:

	// The velocity of a jump with an empty jump charge
	UPROPERTY(EditDefaultsOnly, Category = "Jumping")
	float MinJumpVelocity;

	// The velocity of a jump with a full jump charge
	UPROPERTY(EditDefaultsOnly, Category = "Jumping")
	float MaxJumpVelocity;

	// The time it takes to fully charge up a jump
	UPROPERTY(EditDefaultsOnly, Category = "Jumping")
	float JumpChargeDuration;

	// At what threshold should our character not be able to move when charging a jump.
	// 0 means there is no threshold and the character's movement won't be locked
	UPROPERTY(EditDefaultsOnly, Category = "Jumping")
	float MovementLockThresholdOnJumpCharge;
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void Landed(const FHitResult& Hit) override;

};
