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

	//Checks the world for a partner, if found we store it
	if (PartnerID != 0)
	{
		for (TActorIterator<ADSpawningBridge> It(GetWorld()); It; ++It)
		{
			if (It->LeaverIndex == BridgeIndex)
			{
				SpawningBridgePartner = *It;
			}
		}
	}
}

void ADLeaver::PullLever()
{
	bIsActivated = true;
	
	if (SpawningBridgePartner)
	{
		SpawningBridgePartner->ShowPlank();
	}

	if (Partner->IsA(ADLeaver::StaticClass()))
	{
		ADLeaver* LeaverPartner = Cast<ADLeaver>(Partner);

		if (!LeaverPartner->bIsActivated)
		{
			LeaverPartner->PullLever();	
		}
	}
}

// Called every frame
void ADLeaver::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

