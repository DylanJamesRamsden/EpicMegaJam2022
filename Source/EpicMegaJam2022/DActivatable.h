// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DMirroredActor.h"
#include "DActivatable.generated.h"

/**
 * 
 */
UCLASS()
class EPICMEGAJAM2022_API ADActivatable : public ADMirroredActor
{
	GENERATED_BODY()

protected:

	bool bIsActivated;

public:

	UPROPERTY(EditAnywhere)
	int ActivatorID;
};
