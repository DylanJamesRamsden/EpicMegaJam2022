// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SphereComponent.h"
#include "GameFramework/Actor.h"
#include "PhysicsEngine/PhysicsConstraintComponent.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "DSwingingHook.generated.h"

class ADCharacter;

UCLASS()
class EPICMEGAJAM2022_API ADSwingingHook : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADSwingingHook();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// TMP Just storing the actor that is swinging so that we can get some debug info
	UPROPERTY()
	AActor* SwingingActor;
	
public:

	UPROPERTY(EditDefaultsOnly)
	UStaticMeshComponent* StaticMeshComponent;

	UPROPERTY(EditDefaultsOnly)
	USphereComponent* SphereComponent;

	UPROPERTY(EditDefaultsOnly)
	UPhysicsConstraintComponent* PhysicsConstraintComponent;

	// Attaches a given actor to the swinging hook and allows it to swing
	void EnableSwinging(ADCharacter* Character);

	// Detaches a given actor from the swinging hook and ends their swing
	void DisableSwinging(ADCharacter* Character);
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
