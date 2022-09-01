// Fill out your copyright notice in the Description page of Project Settings.


#include "DPressurePlate.h"

void ADPressurePlate::Action()
{
	// Basically just ping ponging between activated and deactivated
	if (!bIsActivated)
	{
		bIsActivated = true;
	}
	else
	{
		bIsActivated = false;
	}

	Super::Action();
}
