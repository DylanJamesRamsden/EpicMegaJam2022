// Fill out your copyright notice in the Description page of Project Settings.


#include "DSizeChangingRock.h"

#include "DBigCharacter.h"
#include "EngineUtils.h"

// Sets default values
ADSizeChangingRock::ADSizeChangingRock()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ADSizeChangingRock::BeginPlay()
{
	Super::BeginPlay();

	// Binding our custom OnOverlapBegin and OnOverlapEnd functions to the BoxComponent's overlap events
	BoxComponent->OnComponentBeginOverlap.AddDynamic(this, &ADSizeChangingRock::OnBeginOverlapWithRock);
}

void ADSizeChangingRock::OnBeginOverlapWithRock(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!bHasChanged)
	{
		if (ADBigCharacter* Character = Cast<ADBigCharacter>(OtherActor))
		{
			if (Character->bSmashing)
			{
				StartMirroredAction();
			}
		}	
	}
}

void ADSizeChangingRock::ResetHasChanged()
{
	bHasChanged = false;
}

// Called every frame
void ADSizeChangingRock::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ADSizeChangingRock::Action()
{
	Super::Action();

	if (!bHasChanged)
	{
		FVector CurrentScale = StaticMeshComponent->GetComponentScale();
		
		if (bShouldShrink)
		{
			StaticMeshComponent->SetWorldScale3D(FVector(CurrentScale.X, CurrentScale.Y, FMath::Clamp((CurrentScale.Z - ZScaleChangeRate), MaxMinZScale, CurrentScale.Z)));
		}
		else
		{
			StaticMeshComponent->SetWorldScale3D(FVector(CurrentScale.X, CurrentScale.Y, FMath::Clamp((CurrentScale.Z + ZScaleChangeRate), CurrentScale.Z, MaxMinZScale)));
		}

		bHasChanged = true;

		FTimerHandle ChangedTimerHandle;
		GetWorldTimerManager().SetTimer(ChangedTimerHandle, this, &ADSizeChangingRock::ResetHasChanged, 0.2);
	}
}

