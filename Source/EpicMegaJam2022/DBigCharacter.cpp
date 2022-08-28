// Fill out your copyright notice in the Description page of Project Settings.


#include "DBigCharacter.h"

#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"

void ADBigCharacter::Smash()
{
	if (!bSmashing && GetCharacterMovement()->IsFalling())
	{
		bSmashing = true;
		
		LaunchCharacter(FVector(0.0f, 0.0f, SmashVelocity), true, true);
	}
}

void ADBigCharacter::OnSmashMovementLockComplete() const
{
	GetCharacterMovement()->SetDefaultMovementMode();
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
		bSmashing = false;

		if (SmashMovementLockOnHitTime > 0)
		{
			// Disables our movement on smash impact
			GetCharacterMovement()->DisableMovement();
			
			FTimerHandle SmashMovementLockTimerHandle;
			GetWorldTimerManager().SetTimer(SmashMovementLockTimerHandle, this, &ADBigCharacter::OnSmashMovementLockComplete,
				SmashMovementLockOnHitTime, false);
		}

		UGameplayStatics::PlayWorldCameraShake(this, SmashCameraShake,GetActorLocation(), 0.0f, 5000, 1);
	}
}
