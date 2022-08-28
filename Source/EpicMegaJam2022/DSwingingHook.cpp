// Fill out your copyright notice in the Description page of Project Settings.


#include "DSwingingHook.h"

#include "DCharacter.h"
#include "DrawDebugHelpers.h"
#include "Components/CapsuleComponent.h"

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

	PhysicsConstraintComponent->SetAngularSwing1Limit(EAngularConstraintMotion::ACM_Locked, 45.0f);
	PhysicsConstraintComponent->SetAngularSwing2Limit(EAngularConstraintMotion::ACM_Locked, 45.0f);
}

// Called when the game starts or when spawned
void ADSwingingHook::BeginPlay()
{
	Super::BeginPlay();
	
}

void ADSwingingHook::EnableSwinging(ADCharacter* Character)
{
	// Attaches the character as a constraint component and set's it's physics to simulate
	PhysicsConstraintComponent->SetConstrainedComponents(Character->GetCapsuleComponent(), FName(""), nullptr, FName(""));
	Character->GetCapsuleComponent()->SetSimulatePhysics(true);

	// TMP Debugging
	SwingingActor = Character;
}

void ADSwingingHook::DisableSwinging(ADCharacter* Character)
{
	// Removes the character as a constraint component and set's it's physics to not simulate
	PhysicsConstraintComponent->SetConstrainedComponents(nullptr, FName(""), nullptr, FName(""));
	Character->GetCapsuleComponent()->SetSimulatePhysics(false);

	// TMP Debugging
	SwingingActor = nullptr;
}

// Called every frame
void ADSwingingHook::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	DrawDebugCircle( GetWorld(), SphereComponent->GetComponentLocation(), SphereComponent->GetUnscaledSphereRadius(), 32, FColor::Orange, false, 0.0f );

	if (SwingingActor)
	{
		DrawDebugLine(GetWorld(), PhysicsConstraintComponent->GetComponentLocation(), SwingingActor->GetActorLocation(),
			FColor::Yellow, false, 0.0f, 0, 4);
	}
}

