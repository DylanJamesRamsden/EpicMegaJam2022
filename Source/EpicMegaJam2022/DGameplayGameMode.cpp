// Fill out your copyright notice in the Description page of Project Settings.


#include "DGameplayGameMode.h"

#include "GameFramework/PlayerStart.h"
#include "Kismet/GameplayStatics.h"

void ADGameplayGameMode::AddCharacterOnPortal()
{
	NumCharactersOnPortals++;

	if (NumCharactersOnPortals == 2)
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
		// Get all of the player starts in the level
		TArray<AActor*> PlayerStarts;
		UGameplayStatics::GetAllActorsOfClass(World ,APlayerStart::StaticClass(), PlayerStarts);

		ensure(PlayerStarts.Num() >= 2);
		ensure(BigCharacterTemplate);
		ensure(SmallCharacterTemplate);
		
		World->SpawnActor(BigCharacterTemplate, &PlayerStarts[0]->GetTransform());
		World->SpawnActor(SmallCharacterTemplate, &PlayerStarts[1]->GetTransform());
	}
}
