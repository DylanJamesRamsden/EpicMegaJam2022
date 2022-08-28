// Fill out your copyright notice in the Description page of Project Settings.


#include "DPlayerController.h"

#include "EngineUtils.h"
#include "Camera/CameraActor.h"
#include "Kismet/GameplayStatics.h"
#include "DCharacter.h"

void ADPlayerController::BeginPlay()
{
	Super::BeginPlay();

	// Just grabbing and storing all of the available ADCharacters in the world
	// NB! Haven't worked with a non-multiplayer game in a while, but going to assume there are no timing issues
	// regarding having to wait for the characters to have been spawned before we store them
	for (TActorIterator<ADCharacter> It(GetWorld()); It; ++It)
	{
		AvailableCharacters.Add(*It);
	}
	
	for (TActorIterator<ACameraActor> It(GetWorld()); It; ++It)
	{
		if (It->ActorHasTag(FName("View1")))
		{
			CharacterOneCamera = *It;
		}
		else if (It->ActorHasTag(FName("View2")))
		{
			CharacterTwoCamera = *It;
		}
		else if (It->ActorHasTag(FName("LevelView")))
		{
			LevelCamera = *It;
			SetViewTarget(LevelCamera);
		}
	}
}

void ADPlayerController::CyclePossessedPawn()
{
	if (ensure(AvailableCharacters.Num() > 0))
	{
		if (PossessedIndex < AvailableCharacters.Num() - 1)
		{
			PossessedIndex++;
		}
		else PossessedIndex = 0;

		Possess(AvailableCharacters[PossessedIndex]);

		switch (PossessedIndex)
		{
		case 0:
			BlendToCharacterOneCamera();
			break;
		case 1:
			BlendToCharacterTwoCamera();
			break;
		default:
			BlendToLevelCamera();
			break;
		}
	}
}

void ADPlayerController::BlendToLevelCamera()
{
	if (LevelCamera)
	{
		SetViewTargetWithBlend(LevelCamera, 0.25, VTBlend_Cubic, 0, true);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("No level camera!"));
	}
}

void ADPlayerController::BlendToCharacterOneCamera()
{
	if (CharacterOneCamera)
	{
		SetViewTargetWithBlend(CharacterOneCamera, 0.25, VTBlend_Cubic, 0, true);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("No camera for Character 1!"));
	}
}

void ADPlayerController::BlendToCharacterTwoCamera()
{
	if (CharacterTwoCamera)
	{
		SetViewTargetWithBlend(CharacterTwoCamera, 0.25, VTBlend_Cubic, 0, true);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("No camera for Character 2!"));
	}
}

void ADPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	if (InputComponent)
	{
		InputComponent->BindAction("CyclePawn", IE_Pressed, this, &ADPlayerController::CyclePossessedPawn);

		InputComponent->BindAction("LevelView", IE_Pressed, this, &ADPlayerController::BlendToLevelCamera);
		InputComponent->BindAction("Pawn1View", IE_Pressed, this, &ADPlayerController::BlendToCharacterOneCamera);
		InputComponent->BindAction("Pawn2View", IE_Pressed, this, &ADPlayerController::BlendToCharacterTwoCamera);
	}
}
