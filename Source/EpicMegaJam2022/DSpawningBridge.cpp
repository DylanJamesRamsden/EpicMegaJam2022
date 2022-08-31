// Fill out your copyright notice in the Description page of Project Settings.


#include "DSpawningBridge.h"

#include "Engine/StaticMeshActor.h"

// Sets default values
ADSpawningBridge::ADSpawningBridge()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ADSpawningBridge::BeginPlay()
{
	Super::BeginPlay();

	if (UWorld* World = GetWorld())
	{
		FVector SpawnLocation = GetActorLocation();
		FRotator SpawnRotation = GetActorRotation();
		
		for (int i = 0; i < NumberOfPlanks; i++)
		{
			AStaticMeshActor* SpawnedPlank = World->SpawnActor<AStaticMeshActor>(SpawnLocation, SpawnRotation);

			int MeshToUse = FMath::RandRange(0, PlankMeshes.Num() - 1);
			SpawnedPlank->GetStaticMeshComponent()->SetStaticMesh(PlankMeshes[MeshToUse]);
			SpawnedPlank->SetActorHiddenInGame(true);
			SpawnedPlank->SetActorEnableCollision(false);

			SpawnedPlanks.Add(SpawnedPlank);

			SpawnLocation += GetActorRightVector() * SpaceBetweenPlanks;
		}
	}
}

void ADSpawningBridge::ShowPlank()
{
	SpawnedPlanks[ShownPlankIndex]->SetActorHiddenInGame(false);

	SpawnedPlanks[ShownPlankIndex]->SetActorEnableCollision(true);
	
	ShownPlankIndex++;
	
	if (ShownPlankIndex < SpawnedPlanks.Num())
	{
		FTimerHandle ShowPlankTimerHandle;
		GetWorldTimerManager().SetTimer(ShowPlankTimerHandle, this, &ADSpawningBridge::ShowPlank, TimeToShowPlank);
	}
}

// Called every frame
void ADSpawningBridge::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

