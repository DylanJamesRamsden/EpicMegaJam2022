// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DMirroredActor.generated.h"

class UBoxComponent;
UCLASS()
class EPICMEGAJAM2022_API ADMirroredActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADMirroredActor();

protected:

	UPROPERTY()
	ADMirroredActor* Partner;
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:

	UPROPERTY(EditDefaultsOnly)
	UStaticMeshComponent* StaticMeshComponent;

	UPROPERTY(EditDefaultsOnly)
	UBoxComponent* BoxComponent;

	// Starts the action between this actor and it's mirrored partner
	void StartMirroredAction();
	
	virtual void Action();

	// These rocks can be partnered up with another rock. When the rock's size changes, the opposite will happen to it's partner
	// e.g. If the rock shrinks, it's partner will grow
	// Used as an ID to find it's partner when the game starts
	UPROPERTY(EditAnywhere)
	int32 PartnerID;
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
