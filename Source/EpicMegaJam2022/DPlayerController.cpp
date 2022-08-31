// Fill out your copyright notice in the Description page of Project Settings.


#include "DPlayerController.h"

#include "EngineUtils.h"
#include "DCharacter.h"
#include "Camera/CameraActor.h"
#include "Kismet/GameplayStatics.h"

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

	if (AActor* FoundCamera = UGameplayStatics::GetActorOfClass(this, ACameraActor::StaticClass()))
	{
		LevelCamera = Cast<ACameraActor>(FoundCamera);
		
		SetViewTarget(LevelCamera);
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

		//SetViewTargetWithBlend(AvailableCharacters[PossessedIndex], 3.0f, VTBlend_Linear, 1, true);
		SetViewTargetWithBlend(AvailableCharacters[PossessedIndex], 1.0f, VTBlend_Linear, 0, true);
	}
}

void ADPlayerController::BlendToLevelCamera()
{
	
}

void ADPlayerController::BlendToCharacterOneCamera()
{
	
}

void ADPlayerController::BlendToCharacterTwoCamera()
{
	
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
