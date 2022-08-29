// Fill out your copyright notice in the Description page of Project Settings.


#include "DPushable.h"

#include "DBigCharacter.h"
#include "DCharacter.h"


// Sets default values
ADPushable::ADPushable()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
}

// Called when the game starts or when spawned
void ADPushable::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADPushable::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ADPushable::BeginPush(ADCharacter* Character)
{
	if (Character)
	{
		if (Character->IsA(ADBigCharacter::StaticClass()))
		{
			AttachToActor(Character, FAttachmentTransformRules(EAttachmentRule::KeepWorld, false));
		}
	}
}

void ADPushable::EndPush()
{
	DetachFromActor(FDetachmentTransformRules(EDetachmentRule::KeepWorld, false));
}

