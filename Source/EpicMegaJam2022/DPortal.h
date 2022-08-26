// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Actor.h"
#include "DPortal.generated.h"

UCLASS()
class EPICMEGAJAM2022_API ADPortal : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADPortal();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:

	UPROPERTY(EditDefaultsOnly)
	UStaticMeshComponent* StaticMeshComponent;

	UPROPERTY(EditDefaultsOnly)
	UBoxComponent* BoxComponent;
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
