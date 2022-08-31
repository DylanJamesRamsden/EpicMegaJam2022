// Fill out your copyright notice in the Description page of Project Settings.


#include "DPlayerState.h"

void ADPlayerState::PickupKey()
{
	bHasKey = true;
}

bool ADPlayerState::HasKey() const
{
	return bHasKey;
}
