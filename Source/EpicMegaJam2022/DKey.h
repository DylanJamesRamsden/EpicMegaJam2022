// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DMirroredActor.h"
#include "GameFramework/RotatingMovementComponent.h"
#include "DKey.generated.h"

/**
 * 
 */
UCLASS()
class EPICMEGAJAM2022_API ADKey : public ADMirroredActor
{
	GENERATED_BODY()

public:

	ADKey();

protected:
	
	void DestroyKey();

public:

	UPROPERTY(EditDefaultsOnly)
	URotatingMovementComponent* RotatingMovementComponent;

	virtual void Action() override;
};
