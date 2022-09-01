// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DBigCharacter.h"
#include "DSmallCharacter.h"
#include "GameFramework/GameModeBase.h"
#include "DGameplayGameMode.generated.h"

/**
 * 
 */

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnPlayerReachedPortal);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnPlayerLeftPortal);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnLevelComplete);

class ADCharacter;

UCLASS()
class EPICMEGAJAM2022_API ADGameplayGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
protected:

	// A custom function in order to spawn a given number of local ADCharacters
	void SpawnPlayerPawns();

	// Stores the number of characters that are successfully on portals
	UPROPERTY(BlueprintReadWrite)
	int32 NumCharactersOnPortals;
	
public:
	
	// The type of character we want to spawn
	UPROPERTY(EditDefaultsOnly, Category = "Spawning")
	TSubclassOf<ADBigCharacter> BigCharacterTemplate;

	// The type of character we want to spawn
	UPROPERTY(EditDefaultsOnly, Category = "Spawning")
	TSubclassOf<ADSmallCharacter> SmallCharacterTemplate;

	UPROPERTY(BlueprintAssignable)
	FOnLevelComplete OnLevelComplete;

	UPROPERTY(BlueprintAssignable)
	FOnPlayerReachedPortal OnPlayerReachedPortal;

	UPROPERTY(BlueprintAssignable)
	FOnPlayerReachedPortal OnPlayerLeftPortal;

	// Adds a character to our total number of characters successfully on portals
	void AddCharacterOnPortal();

	// Removes a character to our total number of characters successfully on portals
	void RemoveCharacterOnPortal();

	// ¬ Begin APlayerController interface
	virtual void BeginPlay() override;
	// ¬ End APlayerController interface

	UFUNCTION(BlueprintCallable, BlueprintPure)
	int GetNumCharactersOnPortals();
};
