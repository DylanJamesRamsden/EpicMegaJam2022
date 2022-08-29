// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DMirroredActor.h"
#include "GameFramework/Actor.h"
#include "DPushable.generated.h"

class ADCharacter;
class UBoxComponent;

UCLASS()
class EPICMEGAJAM2022_API ADPushable : public ADMirroredActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADPushable();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:

	// The velocity to negate from the pushing character's movement velocity when being pushed
	UPROPERTY(EditAnywhere)
	float MovementPenaltyVelocity;
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void BeginPush(ADCharacter* Character);

	void EndPush();
};
