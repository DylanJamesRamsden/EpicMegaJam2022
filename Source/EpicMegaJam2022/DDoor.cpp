// Fill out your copyright notice in the Description page of Project Settings.


#include "DDoor.h"

ADDoor::ADDoor()
{
	GateFrameStaticMesh = CreateDefaultSubobject<UStaticMeshComponent>("GateFrameStaticMesh");
	GateStaticMesh = CreateDefaultSubobject<UStaticMeshComponent>("GateStaticMesh");
	OpenPoint = CreateDefaultSubobject<USceneComponent>("OpenPoint");

	GateFrameStaticMesh->SetupAttachment(RootComponent);
	GateStaticMesh->SetupAttachment(RootComponent);
	OpenPoint->SetupAttachment(RootComponent);
}

void ADDoor::Action()
{
	if (!bIsOpen)
	{
		bIsOpening = true;
		
		Super::Action();
	}
}

void ADDoor::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (bIsOpening)
	{
		if (!FMath::IsNearlyEqual(FVector::Dist(GateStaticMesh->GetRelativeLocation(), OpenPoint->GetRelativeLocation()), 1.0f))
		{
			GateStaticMesh->SetRelativeLocation(FMath::VInterpTo(GateStaticMesh->GetRelativeLocation(),
			OpenPoint->GetRelativeLocation(), DeltaSeconds, 0.4));	
		}
		else
		{
			bIsOpening = false;

			bIsOpen = true;
		}
	}
}
