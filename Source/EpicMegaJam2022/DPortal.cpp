// Fill out your copyright notice in the Description page of Project Settings.


#include "DPortal.h"

#include "DCharacter.h"

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

	// Binding our custom OnOverlapBegin and OnOverlapEnd functions to the BoxComponent's overlap events
	BoxComponent->OnComponentBeginOverlap.AddDynamic(this, &ADPortal::OnBeginOverlapWithPortal);
	BoxComponent->OnComponentEndOverlap.AddDynamic(this, &ADPortal::OnEndOverlapWithPortal);
}

// Called every frame
void ADPortal::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ADPortal::OnBeginOverlapWithPortal(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// @TODO These are firing twice (because of our character capsule and skeletal mesh both overlapping)
	if (OtherActor->IsA(ADCharacter::StaticClass()))
	{
		OnPortalEntered();
	}
}

void ADPortal::OnEndOverlapWithPortal(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex)
{
	// @TODO These are firing twice (because of our character capsule and skeletal mesh both overlapping)
	if (OtherActor->IsA(ADCharacter::StaticClass()))
	{
		OnPortalExited();
	}
}

