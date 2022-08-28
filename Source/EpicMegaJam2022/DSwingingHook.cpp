// Fill out your copyright notice in the Description page of Project Settings.


#include "DSwingingHook.h"

// Sets default values
ADSwingingHook::ADSwingingHook()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("StaticMeshComponent");
	SphereComponent = CreateDefaultSubobject<USphereComponent>("SphereComponent");
	PhysicsConstraintComponent = CreateDefaultSubobject<UPhysicsConstraintComponent>("PhysicsConstraintComponent");
	
	RootComponent = StaticMeshComponent;
	SphereComponent->SetupAttachment(RootComponent);
	PhysicsConstraintComponent->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ADSwingingHook::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADSwingingHook::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

