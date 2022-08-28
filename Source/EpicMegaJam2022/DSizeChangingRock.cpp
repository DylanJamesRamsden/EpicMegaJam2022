// Fill out your copyright notice in the Description page of Project Settings.


#include "DSizeChangingRock.h"

#include "DBigCharacter.h"
#include "EngineUtils.h"

// Sets default values
ADSizeChangingRock::ADSizeChangingRock()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>("SceneComponent");
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("StaticMeshComponent");
	BoxComponent = CreateDefaultSubobject<UBoxComponent>("BoxComponent");

	StaticMeshComponent->SetupAttachment(RootComponent);
	BoxComponent->SetupAttachment(StaticMeshComponent);

	BoxComponent->SetAbsolute(false, false, true);
}

// Called when the game starts or when spawned
void ADSizeChangingRock::BeginPlay()
{
	Super::BeginPlay();

	// Binding our custom OnOverlapBegin and OnOverlapEnd functions to the BoxComponent's overlap events
	BoxComponent->OnComponentBeginOverlap.AddDynamic(this, &ADSizeChangingRock::OnBeginOverlapWithRock);

	//Checks the world for a partner, if found we store it
	if (PartnerID != 0)
	{
		for (TActorIterator<ADSizeChangingRock> It(GetWorld()); It; ++It)
		{
			if (It->PartnerID == PartnerID)
			{
				Partner = *It;
			}
		}
	}
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
				ChangeSize();

				if (Partner)
				{
					Partner->ChangeSize();
				}

				bHasChanged = true;

				FTimerHandle ChangedTimerHandle;
				GetWorldTimerManager().SetTimer(ChangedTimerHandle, this, &ADSizeChangingRock::ResetHasChanged, 0.2);
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

void ADSizeChangingRock::ChangeSize()
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
}

