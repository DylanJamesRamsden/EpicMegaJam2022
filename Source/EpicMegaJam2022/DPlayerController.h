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

	// Sets our LevelCamera as our current view target
	void SetLevelCameraAsViewTarget();

	// Stores all of the available pawns we can possess
	UPROPERTY()
	TArray<ADCharacter*> AvailableCharacters;

	// Keeps track of the index of which pawn we are currently possessing
	int32 PossessedIndex;

	// Cycles between our available pawns, based on our PossessedIndex
	void CyclePossessedPawn();
public:

	// ¬ Begin APlayerController interface
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;
	// ¬ End APlayerController interface
	
};
