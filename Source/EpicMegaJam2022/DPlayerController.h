// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "DPlayerController.generated.h"

/**
 * 
 */

class ADCharacter;

UCLASS()
class EPICMEGAJAM2022_API ADPlayerController : public APlayerController
{
	GENERATED_BODY()
	
protected:
	UPROPERTY()
	ACameraActor* LevelCamera;

	UPROPERTY()
	TArray<ADCharacter*> AvailableCharacters;
public:

	// ¬ Begin APlayerController interface
	virtual void BeginPlay() override;
	// ¬ End APlayerController interface
	
};
