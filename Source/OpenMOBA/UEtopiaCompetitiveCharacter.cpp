// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#include "UEtopiaCompetitiveCharacter.h"
#include "OpenMOBA.h"
#include "Kismet/HeadMountedDisplayFunctionLibrary.h"
#include "UnrealNetwork.h"
#include "MyPlayerController.h"
#include "MyPlayerState.h"
#include "MyGameInstance.h"


//////////////////////////////////////////////////////////////////////////
// AUEtopiaCompetitiveCharacter

AUEtopiaCompetitiveCharacter::AUEtopiaCompetitiveCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// set our turn rates for input
	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;

	// Modifying this to behave like first person character

	// Create a CameraComponent	
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FollowCamera->SetupAttachment(GetCapsuleComponent());
	FollowCamera->RelativeLocation = FVector(-39.56f, 1.75f, 64.f); // Position the camera
	FollowCamera->bUsePawnControlRotation = true;



	Health = 1.0f;

}

//////////////////////////////////////////////////////////////////////////
// Input

void AUEtopiaCompetitiveCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// Set up gameplay key bindings
	check(PlayerInputComponent);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &AUEtopiaCompetitiveCharacter::OnStartFire);
	PlayerInputComponent->BindAction("Fire", IE_Released, this, &AUEtopiaCompetitiveCharacter::OnStopFire);

	PlayerInputComponent->BindAxis("MoveForward", this, &AUEtopiaCompetitiveCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AUEtopiaCompetitiveCharacter::MoveRight);

	// We have 2 versions of the rotation bindings to handle different kinds of devices differently
	// "turn" handles devices that provide an absolute delta, such as a mouse.
	// "turnrate" is for devices that we choose to treat as a rate of change, such as an analog joystick
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("TurnRate", this, &AUEtopiaCompetitiveCharacter::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("LookUpRate", this, &AUEtopiaCompetitiveCharacter::LookUpAtRate);

	// handle touch devices
	PlayerInputComponent->BindTouch(IE_Pressed, this, &AUEtopiaCompetitiveCharacter::TouchStarted);
	PlayerInputComponent->BindTouch(IE_Released, this, &AUEtopiaCompetitiveCharacter::TouchStopped);

	// VR headset functionality
	PlayerInputComponent->BindAction("ResetVR", IE_Pressed, this, &AUEtopiaCompetitiveCharacter::OnResetVR);
}

void AUEtopiaCompetitiveCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void AUEtopiaCompetitiveCharacter::OnResetVR()
{
	UHeadMountedDisplayFunctionLibrary::ResetOrientationAndPosition();
}

void AUEtopiaCompetitiveCharacter::TouchStarted(ETouchIndex::Type FingerIndex, FVector Location)
{
	// jump, but only on the first touch
	if (FingerIndex == ETouchIndex::Touch1)
	{
		Jump();
	}
}

void AUEtopiaCompetitiveCharacter::TouchStopped(ETouchIndex::Type FingerIndex, FVector Location)
{
	if (FingerIndex == ETouchIndex::Touch1)
	{
		StopJumping();
	}
}

void AUEtopiaCompetitiveCharacter::TurnAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void AUEtopiaCompetitiveCharacter::LookUpAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

void AUEtopiaCompetitiveCharacter::MoveForward(float Value)
{
	if ((Controller != NULL) && (Value != 0.0f))
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}

void AUEtopiaCompetitiveCharacter::MoveRight(float Value)
{
	if ((Controller != NULL) && (Value != 0.0f))
	{
		// find out which way is right
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get right vector 
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		// add movement in that direction
		AddMovementInput(Direction, Value);
	}
}


void AUEtopiaCompetitiveCharacter::ClientChangeUIState_Implementation(EConnectUIState NewState)
{
	UE_LOG(LogTemp, Log, TEXT("[UETOPIA] [AUEtopiaCompetitiveCharacter] ClientChangeUIState_Implementation"));
	//OnUIStateChange.Broadcast(NewState);
	OnUIStateChange(NewState);
	return;
}

void AUEtopiaCompetitiveCharacter::OnUIStateChange_Implementation(EConnectUIState UIState)
{
	UE_LOG(LogTemp, Log, TEXT("[UETOPIA]AUEtopiaCompetitiveCharacter::OnUIStateChange_Implementation"));
}


void AUEtopiaCompetitiveCharacter::GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	// Replicate to everyone
	DOREPLIFETIME(AUEtopiaCompetitiveCharacter, Health);
	
}

void AUEtopiaCompetitiveCharacter::OnStartFire()
{
	UE_LOG(LogTemp, Log, TEXT("[UETOPIA] [AUEtopiaCompetitiveCharacter] [OnStartFire] "));
	

}

void AUEtopiaCompetitiveCharacter::OnStopFire()
{
	UE_LOG(LogTemp, Log, TEXT("[UETOPIA] [AUEtopiaCompetitiveCharacter] [OnStopFire] "));
	//StopWeaponFire();
}

float AUEtopiaCompetitiveCharacter::TakeDamageCustom(float Damage, struct FDamageEvent const& DamageEvent, class AActor* DamageCauser)
{
	UE_LOG(LogTemp, Log, TEXT("[UETOPIA] [AUEtopiaCompetitiveCharacter] [TakeDamageCustom] "));
	if (Role >= ROLE_Authority)
	{
		UE_LOG(LogTemp, Log, TEXT("[UETOPIA] [AUEtopiaCompetitiveCharacter] [TakeDamageCustom] SERVER "));

		Health -= Damage;
		if (Health <= 0)
		{
			Die(Damage, DamageEvent, DamageCauser);
			UE_LOG(LogTemp, Log, TEXT("[UETOPIA] [AUEtopiaCompetitiveCharacter] [TakeDamage] DIE "));
		}
		else
		{
			//PlayHit(ActualDamage, DamageEvent, EventInstigator ? EventInstigator->GetPawn() : NULL, DamageCauser);
			UE_LOG(LogTemp, Log, TEXT("[UETOPIA] [AUEtopiaCompetitiveCharacter] [TakeDamage] HIT "));

		}
	}

	return 0.f;
}



bool AUEtopiaCompetitiveCharacter::Die(float KillingDamage, FDamageEvent const& DamageEvent, AActor* DamageCauser)
{

	Health = FMath::Min(0.0f, Health);

	//AController* const KilledPlayer = (Controller != NULL) ? Controller : Cast<AController>(GetOwner());
	//GetWorld()->GetAuthGameMode<AMyGameMode>()->Killed(Killer, KilledPlayer, this, DamageType);

	GetCharacterMovement()->ForceReplicationUpdate();

	GetCharacterMovement()->StopMovementImmediately();
	GetCharacterMovement()->DisableMovement();
	GetCharacterMovement()->SetComponentTickEnabled(false);

	// Death anim
	//float DeathAnimDuration = PlayAnimMontage(DeathAnim);

	AMyPlayerController* victim = Cast<AMyPlayerController>(GetController());
	//AMyProjectile* projectile = Cast<AMyProjectile>(DamageCauser);

	// TODO - deal with this.

	//UMyGameInstance* TheGameInstance = Cast<UMyGameInstance>(GetWorld()->GetGameInstance());
	//TheGameInstance->RecordKill(projectile->ownerPlayerID, victim->PlayerState->PlayerId);

	return true;
}

bool AUEtopiaCompetitiveCharacter::IsAlive() const
{
	return Health > 0;
}

bool AUEtopiaCompetitiveCharacter::CanFire() const
{
	return IsAlive();
}


void AUEtopiaCompetitiveCharacter::OnRep_OnAppearanceChange()
{
	// This is running client side.
	UE_LOG(LogTemp, Log, TEXT("[UETOPIA]AUEtopiaCompetitiveCharacter::OnRep_OnAppearanceChange"));

	EquipAppearance();
}

void AUEtopiaCompetitiveCharacter::EquipAppearance()
{
	UE_LOG(LogTemp, Log, TEXT("[UETOPIA] [AUEtopiaCompetitiveCharacter] [EquipAppearance]  "));

	if (character_options.IsValidIndex(MyAppearance.mesh))
	{
		UE_LOG(LogTemp, Log, TEXT("[UETOPIA] [AUEtopiaCompetitiveCharacter] [EquipAppearance] Valid Mesh Index  "));
		GetMesh()->SetSkeletalMesh(character_options[MyAppearance.mesh].mesh);
		
	}

}