// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DGameplayGameMode.h"
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

	// Just a reference to our current game mode
	UPROPERTY()
	ADGameplayGameMode* GameplayGameMode;
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
    void OnBeginOverlapWithPortal(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnEndOverlapWithPortal(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	// A cosmetic event for when a character has entered a portal
	UFUNCTION(BlueprintImplementableEvent, BlueprintCosmetic)
	void OnPortalEntered();

	// A cosmetic event for when a character has exited a portal
	UFUNCTION(BlueprintImplementableEvent, BlueprintCosmetic)
	void OnPortalExited();

public:

	UPROPERTY(EditDefaultsOnly)
	UStaticMeshComponent* StaticMeshComponent;

	UPROPERTY(EditDefaultsOnly)
	UBoxComponent* BoxComponent;

	UPROPERTY(EditDefaultsOnly)
	USoundBase* SoundOnEntered;
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
