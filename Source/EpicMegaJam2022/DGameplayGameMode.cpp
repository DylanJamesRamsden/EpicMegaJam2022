// Fill out your copyright notice in the Description page of Project Settings.


#include "DGameplayGameMode.h"

#include "DCharacter.h"
#include "GameFramework/PlayerStart.h"
#include "Kismet/GameplayStatics.h"

void ADGameplayGameMode::AddCharacterOnPortal()
{
	NumCharactersOnPortals++;

	if (NumCharactersOnPortals == NumberOfCharactersToSpawn)
	{
		// @TODO add level win con here
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("You won!"));
	}
}

void ADGameplayGameMode::RemoveCharacterOnPortal()
{
	NumCharactersOnPortals--;
}

void ADGameplayGameMode::BeginPlay()
{
	Super::BeginPlay();

	SpawnPlayerPawns();
}

void ADGameplayGameMode::SpawnPlayerPawns()
{
	if (UWorld* World = GetWorld())
	{
		if (Characters)
		{
			// Get all of the player starts in the level
			TArray<AActor*> PlayerStarts;
			UGameplayStatics::GetAllActorsOfClass(World ,APlayerStart::StaticClass(), PlayerStarts);

			// Spawn the specified number of characters until it reaches the total number of spawn points available in the world
			for (int i = 0; i < NumberOfCharactersToSpawn; i++)
			{
				if (i + 1 <= PlayerStarts.Num())
				{
					World->SpawnActor(Characters, &PlayerStarts[i]->GetTransform());	
				}
				else break;
			}
		}
	}
}
