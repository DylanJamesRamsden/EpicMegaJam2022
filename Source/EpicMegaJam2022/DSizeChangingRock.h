// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DMirroredActor.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Actor.h"
#include "DSizeChangingRock.generated.h"

UCLASS()
class EPICMEGAJAM2022_API ADSizeChangingRock : public ADMirroredActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADSizeChangingRock();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	bool bHasChanged;

	UFUNCTION()
    void OnBeginOverlapWithRock(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	void ResetHasChanged();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Determines if the rock should shrink or grow
	UPROPERTY(EditAnywhere)
	bool bShouldShrink = true;

	// The rate at which to change the Z scale of the rock
	UPROPERTY(EditAnywhere)
	float ZScaleChangeRate;

	// Max/min scale the rock can change to
	UPROPERTY(EditAnywhere)
	float MaxMinZScale;

	virtual void Action() override;
};
