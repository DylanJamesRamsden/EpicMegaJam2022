// Fill out your copyright notice in the Description page of Project Settings.


#include "DMovingPlatform.h"

#include "Kismet/GameplayStatics.h"

ADMovingPlatform::ADMovingPlatform()
{
	PositionAComponent = CreateDefaultSubobject<USceneComponent>("PositionAComponent");
	PositionBComponent = CreateDefaultSubobject<USceneComponent>("PositionBComponent");

	PositionAComponent->SetupAttachment(RootComponent);
	PositionBComponent->SetupAttachment(RootComponent);
}

void ADMovingPlatform::Action()
{
	if (!bIsActivated)
	{
		Super::Action();

		bIsActivated = true;
	}
	else
	{
		bIsActivated = false;
	}
}

void ADMovingPlatform::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (bIsActivated)
	{
		if (bIsMovingToB)
		{
			if (FVector::Dist(StaticMeshComponent->GetComponentLocation(), PositionBComponent->GetComponentLocation()) > 25.0f)
			{
				StaticMeshComponent->SetWorldLocation(FMath::VInterpTo(StaticMeshComponent->GetComponentLocation(),
			PositionBComponent->GetComponentLocation(), DeltaSeconds, 0.3));	
			}
			else bIsMovingToB = false;
		}
		else
		{
			if (FVector::Dist(StaticMeshComponent->GetComponentLocation(), PositionAComponent->GetComponentLocation()) > 25.0f)
			{
				StaticMeshComponent->SetWorldLocation(FMath::VInterpTo(StaticMeshComponent->GetComponentLocation(),
			PositionAComponent->GetComponentLocation(), DeltaSeconds, 0.3));	
			}
			else bIsMovingToB = true;
		}
	}
}
