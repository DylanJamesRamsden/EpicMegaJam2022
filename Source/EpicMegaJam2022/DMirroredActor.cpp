// Fill out your copyright notice in the Description page of Project Settings.


#include "DMirroredActor.h"

#include "EngineUtils.h"
#include "Components/BoxComponent.h"

// Sets default values
ADMirroredActor::ADMirroredActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>("SceneComponent");
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("StaticMeshComponent");
	BoxComponent = CreateDefaultSubobject<UBoxComponent>("BoxComponent");

	StaticMeshComponent->SetupAttachment(RootComponent);
	BoxComponent->SetupAttachment(StaticMeshComponent);

	BoxComponent->SetAbsolute(false, false, true);
}

// Called when the game starts or when spawned
void ADMirroredActor::BeginPlay()
{
	Super::BeginPlay();

	//Checks the world for a partner, if found we store it
	if (PartnerID != 0)
	{
		for (TActorIterator<ADMirroredActor> It(GetWorld()); It; ++It)
		{
			if (It->PartnerID == PartnerID)
			{
				Partner = *It;
			}
		}
	}
}

// Called every frame
void ADMirroredActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

