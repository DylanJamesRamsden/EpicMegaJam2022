// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
//#include "DCharacter.h"
#include "GameFramework/GameModeBase.h"
#include "DGameplayGameMode.generated.h"

/**
 * 
 */

class ADCharacter;

UCLASS()
class EPICMEGAJAM2022_API ADGameplayGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
protected:

	// A custom function in order to spawn a given number of local ADCharacters
	void SpawnPlayerPawns();
	
public:

	// The type of character we want to spawn
	UPROPERTY(EditDefaultsOnly, Category = "Spawning")
	TSubclassOf<ADCharacter> Characters;

	// The number of characters we want to spawn
	UPROPERTY(EditDefaultsOnly, Category = "Spawning")
	int NumberOfCharactersToSpawn;

	// ¬ Begin APlayerController interface
	virtual void BeginPlay() override;
	// ¬ End APlayerController interface
};
