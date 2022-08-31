// Fill out your copyright notice in the Description page of Project Settings.


#include "DActivator.h"

#include "EngineUtils.h"

void ADActivator::BeginPlay()
{
	Super::BeginPlay();

	//Checks the world for a partner, if found we store it
	if (PartnerID != 0)
	{
		for (TActorIterator<ADActivatable> It(GetWorld()); It; ++It)
		{
			if (It->ActivatorID == ActivatableID)
			{
				Activatable = *It;
			}
		}
	}
}

void ADActivator::Action()
{
	Super::Action();

	if (Activatable)
	{
		Activatable->Action();
	}
}
