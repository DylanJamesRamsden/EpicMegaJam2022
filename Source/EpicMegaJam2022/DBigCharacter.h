// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DCharacter.h"
#include "DPushable.h"
#include "DBigCharacter.generated.h"

/**
 * 
 */
UCLASS()
class EPICMEGAJAM2022_API ADBigCharacter : public ADCharacter
{
	GENERATED_BODY()

protected:

	virtual void Interact() override;

	void Smash();

	// Unlocks our characters movement comp after the smash lock movement timer is complete
	void OnSmashMovementLockComplete() const;

	virtual void OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;
	
	virtual void OnEndOverlap(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) override;

	bool bCanPush;

	UPROPERTY()
	ADPushable* AvailablePushable;

	bool bIsPushing;

public:

	// Indicates whether or not the character is in the middle of a smash sequence
	bool bSmashing;

	// The velocity at which our character smashes underneath them
	UPROPERTY(EditDefaultsOnly, Category = "Movement | Abilities")
	float SmashVelocity;

	// The velocity at which our character smashes underneath them
	UPROPERTY(EditDefaultsOnly, Category = "Movement | Abilities")
	float SmashMovementLockOnHitTime;

	UPROPERTY(EditDefaultsOnly, Category = "Movement | Abilities")
	TSubclassOf<UCameraShakeBase> SmashCameraShake;
	
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void Landed(const FHitResult& Hit) override;
	
};
