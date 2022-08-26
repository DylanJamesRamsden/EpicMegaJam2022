// Fill out your copyright notice in the Description page of Project Settings.


#include "DPlayerController.h"

#include "EngineUtils.h"
#include "Camera/CameraActor.h"
#include "Kismet/GameplayStatics.h"
#include "DCharacter.h"

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

	// Just grabbing and storing all of the available ADCharacters in the world
	// NB! Haven't worked with a non-multiplayer game in a while, but going to assume there are no timing issues
	// regarding having to wait for the characters to have been spawned before we store them
	for (TActorIterator<ADCharacter> It(GetWorld()); It; ++It)
	{
		AvailableCharacters.Add(*It);
	}

}
