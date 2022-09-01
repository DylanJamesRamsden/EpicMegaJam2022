// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DActivator.h"
#include "DPressurePlate.generated.h"

/**
 * 
 */
UCLASS()
class EPICMEGAJAM2022_API ADPressurePlate : public ADActivator
{
	GENERATED_BODY()

public:

	virtual void Action() override;
};
