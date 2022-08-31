// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DActivator.h"
#include "DSpawningBridge.h"
#include "DLeaver.generated.h"

UCLASS()
class EPICMEGAJAM2022_API ADLeaver : public ADActivator
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADLeaver();

protected:
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:

	UPROPERTY()
	ADSpawningBridge* SpawningBridgePartner;

	UPROPERTY(EditAnywhere)
	int SpawningBridgePartnerID;

	bool bIsActivated;
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void Action() override;
};
