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

	if (bIsBeingPushed)
	{
		if (Partner)
		{
			FVector Newlocation(Partner->GetActorLocation().X, GetActorLocation().Y, Partner->GetActorLocation().Z);
			Partner->SetActorLocation(FVector(Newlocation));
		}
	}
}

void ADPushable::BeginPush(ADCharacter* Character)
{
	if (Character)
	{
		if (Character->IsA(ADBigCharacter::StaticClass()))
		{
			AttachToActor(Character, FAttachmentTransformRules(EAttachmentRule::KeepWorld, false));

			bIsBeingPushed = true;
		}
	}
}

void ADPushable::EndPush()
{
	DetachFromActor(FDetachmentTransformRules(EDetachmentRule::KeepWorld, false));

	bIsBeingPushed = true;
}

