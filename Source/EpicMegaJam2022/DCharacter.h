// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DSwingingHook.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/SpringArmComponent.h"
#include "DCharacter.generated.h"

class ADLeaver;
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
	virtual void MoveHorizontal(float Value);

	// ~ Start jump logic

	virtual void JumpStart();

	virtual void JumpEnd();

	// A value between 0 and 1, determining how much of our jump has been charged (0 being none and 1 being full)
	float JumpCharge;

	bool bIsChargingJump;

	// Used as a buffer when the player tries to charge a jump while they are falling
	// When they hit the ground, the jump will start charging
	bool bIsBufferingJump;

	bool bLockMovement;

	// ~ End jump logic
	
	virtual void Interact();

	UFUNCTION()
    virtual void OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	virtual void OnEndOverlap(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	bool bCanInteractWithInteractable;

	// @TODO gonna need to change this when we create the interface (change to actor and just check if it implements the interface)
	UPROPERTY()
	ADLeaver* InteractableActor;

public:

	UPROPERTY(EditDefaultsOnly)
	USpringArmComponent* SpringArmComponent;

	UPROPERTY(EditDefaultsOnly)
	UCameraComponent* CameraComponent;

	// The velocity of a jump with an empty jump charge
	UPROPERTY(EditDefaultsOnly, Category = "Movement | Jumping")
	float MinJumpVelocity;

	// The velocity of a jump with a full jump charge
	UPROPERTY(EditDefaultsOnly, Category = "Movement | Jumping")
	float MaxJumpVelocity;

	// The time it takes to fully charge up a jump
	UPROPERTY(EditDefaultsOnly, Category = "Movement | Jumping")
	float JumpChargeDuration;

	// At what threshold should our character not be able to move when charging a jump.
	// 0 means there is no threshold and the character's movement won't be locked
	UPROPERTY(EditDefaultsOnly, Category = "Movement | Jumping")
	float MovementLockThresholdOnJumpCharge;

	UPROPERTY(EditDefaultsOnly)
	UAnimMontage* ChargeJumpAnimation;

	FTimerHandle ChargeAnimTimerHandle;
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void Landed(const FHitResult& Hit) override;

};
