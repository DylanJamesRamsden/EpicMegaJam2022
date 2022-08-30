// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ArrowComponent.h"
#include "Engine/StaticMeshActor.h"
#include "GameFramework/Actor.h"
#include "DSpawningBridge.generated.h"

UCLASS()
class EPICMEGAJAM2022_API ADSpawningBridge : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADSpawningBridge();

protected:

	UPROPERTY()
	TArray<AStaticMeshActor*> SpawnedPlanks;

	int ShownPlankIndex;
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void ShowPlank();

public:

	UPROPERTY(EditAnywhere)
	TArray<UStaticMesh*> PlankMeshes;

	// The number of planks the bridge must consist of
	UPROPERTY(EditAnywhere)
	int NumberOfPlanks = 10;

	UPROPERTY(EditAnywhere)
	float SpaceBetweenPlanks = 2.0f;

	UPROPERTY(EditDefaultsOnly)
	float TimeToShowPlank;
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
