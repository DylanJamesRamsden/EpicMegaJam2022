// Fill out your copyright notice in the Description page of Project Settings.


#include "DBigCharacter.h"

#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"

void ADBigCharacter::BeginPlay()
{
	Super::BeginPlay();

	// Storing our normal walk speed so we can switch between the normal and penalty effected walk speed when pushing
	// something
	NormalWalkSpeed = GetCharacterMovement()->MaxWalkSpeed;
}

void ADBigCharacter::JumpStart()
{
	if (!bIsPushing) Super::JumpStart();
}

void ADBigCharacter::Interact()
{
	Super::Interact();
	
	if (AvailablePushable)
	{
		if (!bIsPushing)
		{
			AvailablePushable->BeginPush(this);
			bIsPushing = true;
			bCanPush = false;

			GetCharacterMovement()->MaxWalkSpeed = GetCharacterMovement()->MaxWalkSpeed - AvailablePushable->MovementPenaltyVelocity;
		}
		else
		{
			AvailablePushable->EndPush();
			bIsPushing = false;

			GetCharacterMovement()->MaxWalkSpeed = NormalWalkSpeed;

			
		}
	}
}

void ADBigCharacter::Smash()
{
	if (!bSmashing && GetCharacterMovement()->IsFalling())
	{
		bSmashing = true;
		
		LaunchCharacter(FVector(0.0f, 0.0f, SmashVelocity), true, true);
	}
}

void ADBigCharacter::OnSmashMovementLockComplete()
{
	GetCharacterMovement()->SetDefaultMovementMode();

	bInSmashSequence = false;
}

void ADBigCharacter::OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Super::OnBeginOverlap(OverlappedComp, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);

	if (!bIsPushing)
	{
		if (OtherActor->IsA(ADPushable::StaticClass()))
		{
			AvailablePushable = Cast<ADPushable>(OtherActor);
			bCanPush = true;

			OnCanInteract();
		}	
	}
}

void ADBigCharacter::OnEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	Super::OnEndOverlap(OverlappedComp, OtherActor, OtherComp, OtherBodyIndex);

	if (!bIsPushing)
	{
		if (OtherActor->IsA(ADPushable::StaticClass()))
		{
			if (OtherActor == AvailablePushable)
			{
				AvailablePushable = nullptr;
				bCanPush = false;

				OnCantInteract();
			}
		}
	}
}

void ADBigCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction("Smash", IE_Pressed, this, &ADBigCharacter::Smash);
}

void ADBigCharacter::Landed(const FHitResult& Hit)
{
	Super::Landed(Hit);

	if (bSmashing)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("This is an on screen message!"));
		
		bSmashing = false;

		if (SmashMovementLockOnHitTime > 0)
		{
			// Disables our movement on smash impact
			GetCharacterMovement()->DisableMovement();
			
			FTimerHandle SmashMovementLockTimerHandle;
			GetWorldTimerManager().SetTimer(SmashMovementLockTimerHandle, this, &ADBigCharacter::OnSmashMovementLockComplete,
				SmashMovementLockOnHitTime, false);

			bInSmashSequence = true;
		}

		UGameplayStatics::PlayWorldCameraShake(this, SmashCameraShake,GetActorLocation(), 0.0f, 5000, 1);
	}
}
