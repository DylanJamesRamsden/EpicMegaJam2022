// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DActivatable.h"
#include "DMirroredActor.h"
#include "DActivator.generated.h"

/**
 * 
 */
UCLASS()
class EPICMEGAJAM2022_API ADActivator : public ADMirroredActor
{
	GENERATED_BODY()

protected:

	virtual void BeginPlay() override;

	UPROPERTY()
	ADActivatable* Activatable;

public:

	virtual void Action() override;

	UPROPERTY(EditAnywhere)
	int ActivatableID;
};
