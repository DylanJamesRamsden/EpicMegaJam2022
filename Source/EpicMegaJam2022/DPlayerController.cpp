// Fill out your copyright notice in the Description page of Project Settings.


#include "DPlayerController.h"

#include "Camera/CameraActor.h"
#include "Kismet/GameplayStatics.h"

void ADPlayerController::BeginPlay()
{
	Super::BeginPlay();

	// @TODO Can update this to only grab camera that have a 'Level Camera' tag
	if (AActor* FoundCameraActor = UGameplayStatics::GetActorOfClass(this, ACameraActor::StaticClass()))
	{
		LevelCamera = Cast<ACameraActor>(FoundCameraActor);
		ensure(LevelCamera);
		
		SetViewTarget(LevelCamera);
	}
}
