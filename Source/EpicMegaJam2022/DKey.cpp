// Fill out your copyright notice in the Description page of Project Settings.


#include "DKey.h"

ADKey::ADKey()
{
	RotatingMovementComponent = CreateDefaultSubobject<URotatingMovementComponent>("RotatingMovementComponent");
}

void ADKey::DestroyKey()
{
	Destroy();
}

void ADKey::Action()
{
	Super::Action();

	GetWorldTimerManager().SetTimerForNextTick(this, &ADKey::DestroyKey);
}
