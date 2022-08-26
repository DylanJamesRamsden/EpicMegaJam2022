// Fill out your copyright notice in the Description page of Project Settings.


#include "DPortal.h"

// Sets default values
ADPortal::ADPortal()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>("SceneComponent");
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("StaticMeshComponent");
	BoxComponent = CreateDefaultSubobject<UBoxComponent>("BoxComponent");

	StaticMeshComponent->SetupAttachment(RootComponent);
	BoxComponent->SetupAttachment(StaticMeshComponent);
}

// Called when the game starts or when spawned
void ADPortal::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADPortal::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

