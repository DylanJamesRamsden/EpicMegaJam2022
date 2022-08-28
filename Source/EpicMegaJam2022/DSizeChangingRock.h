// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Actor.h"
#include "DSizeChangingRock.generated.h"

UCLASS()
class EPICMEGAJAM2022_API ADSizeChangingRock : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADSizeChangingRock();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY()
	ADSizeChangingRock* Partner;

	bool bHasChanged;

	UFUNCTION()
    void OnBeginOverlapWithRock(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	void ResetHasChanged();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditDefaultsOnly)
	UStaticMeshComponent* StaticMeshComponent;

	UPROPERTY(EditDefaultsOnly)
	UBoxComponent* BoxComponent;

	// Determines if the rock should shrink or grow
	UPROPERTY(EditAnywhere)
	bool bShouldShrink = true;

	// The rate at which to change the Z scale of the rock
	UPROPERTY(EditAnywhere)
	float ZScaleChangeRate;

	// Max/min scale the rock can change to
	UPROPERTY(EditAnywhere)
	float MaxMinZScale;

	// These rocks can be partnered up with another rock. When the rock's size changes, the opposite will happen to it's partner
	// e.g. If the rock shrinks, it's partner will grow
	// Used as an ID to find it's partner when the game starts
	UPROPERTY(EditAnywhere)
	int32 PartnerID;

	// Changes the size of our rock and the size of the partner if the rock has one
	void ChangeSize();
};
