// Fill out your copyright notice in the Description page of Project Settings.


#include "DLeaver.h"

#include "DSpawningBridge.h"
#include "EngineUtils.h"

// Sets default values
ADLeaver::ADLeaver()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	
}

// Called when the game starts or when spawned
void ADLeaver::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADLeaver::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ADLeaver::Action()
{
	if (!bIsActivated)
	{
		bIsActivated = true;
		
		Super::Action();	
	}
}

