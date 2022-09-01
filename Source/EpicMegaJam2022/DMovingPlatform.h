// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DActivatable.h"
#include "DMovingPlatform.generated.h"

/**
 * 
 */
UCLASS()
class EPICMEGAJAM2022_API ADMovingPlatform : public ADActivatable
{
	GENERATED_BODY()

public:

	ADMovingPlatform();

protected:

	bool bIsMovingToB = true;

public:

	UPROPERTY(EditAnywhere)
	USceneComponent* PositionAComponent;

	UPROPERTY(EditAnywhere)
	USceneComponent* PositionBComponent;

	virtual void Action() override;

	virtual void Tick(float DeltaSeconds) override;
};
