// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "DPlayerState.generated.h"

/**
 * 
 */
UCLASS()
class EPICMEGAJAM2022_API ADPlayerState : public APlayerState
{
	GENERATED_BODY()

protected:

	bool bHasKey;
	
public:

	void PickupKey();

	bool HasKey() const;
};
