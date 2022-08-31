// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DMirroredActor.h"
#include "DDoor.generated.h"

/**
 * 
 */
UCLASS()
class EPICMEGAJAM2022_API ADDoor : public ADMirroredActor
{
	GENERATED_BODY()

public:

	ADDoor();

protected:

	bool bIsOpening;
	
	bool bIsOpen;

public:

	UPROPERTY(EditDefaultsOnly)
	UStaticMeshComponent* GateFrameStaticMesh;

	UPROPERTY(EditDefaultsOnly)
	UStaticMeshComponent* GateStaticMesh;

	UPROPERTY(EditDefaultsOnly)
	USceneComponent* OpenPoint;

	virtual void Action() override;

	virtual void Tick(float DeltaSeconds) override;
};
