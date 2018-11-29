// Fill out your copyright notice in the Description page of Project Settings.

#include "MyGameMode.h"
#include "OpenMOBA.h"
//#include "MyPawn.h"
#include "MyPlayerState.h"
#include "MyGameState.h"
#include "MyGameSession.h"
#include "MyGameInstance.h"
#include "MyPlayerController.h"
#include "UEtopiaCompetitiveCharacter.h"
//#include "UEtopiaPlugCharacter.h"
#include "Blueprint/UserWidget.h"



AMyGameMode::AMyGameMode(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	// set default pawn class to our flying pawn
	//DefaultPawnClass = AUEtopiaPlugCharacter::StaticClass();
	//static ConstructorHelpers::FClassFinder<ACharacter> PlayerPawnBPClass(TEXT("/Game/MyUEtopiaPlugCharacter"));
	// Class'/Script/ProESports.UEtopiaCompetitiveCharacter'
	//static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	//Blueprint'/Game/Blueprints/Units/MobileUnit/Champions/Champion.Champion'
	/*
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Script/ProESports.UEtopiaCompetitiveCharacter"));
	
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
	else {
		UE_LOG(LogTemp, Log, TEXT("[UETOPIA] [AMyGameMode] PlayerPawnBPClass.Class = NUL"));
	}
	//DefaultPawnClass = PlayerPawnOb.Class;
	*/

	//
	
	// Attempting to load the BP classes in here directly, which crashes the server.

	/*
	
	// Blueprint'/Game/Blueprints/PlayerState/bp_MyPlayerState.bp_MyPlayerState'
	static ConstructorHelpers::FClassFinder<AMyGameState> GameStateBPClass(TEXT("/Game/Blueprints/PlayerState/bp_MyPlayerState.bp_MyPlayerState"));
	if (GameStateBPClass.Class != NULL)
	{
		UE_LOG(LogTemp, Log, TEXT("[UETOPIA] [AMyGameMode] [Contruct] Found BP Game State"));
		GameStateClass = GameStateBPClass.Class;
	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("[UETOPIA] [AMyGameMode] [Contruct] DID NOT find BP Game State"));
		GameStateClass = AMyGameState::StaticClass();
	}

	// Blueprint'/Game/Blueprints/PlayerState/bp_MyPlayerState.bp_MyPlayerState'
	static ConstructorHelpers::FClassFinder<AMyPlayerState> PlayerStateBPClass(TEXT("/Game/Blueprints/PlayerState/bp_MyPlayerState.bp_MyPlayerState"));
	if (PlayerStateBPClass.Class != NULL)
	{
		UE_LOG(LogTemp, Log, TEXT("[UETOPIA] [AMyGameMode] [Contruct] Found BP Player State"));
		PlayerStateClass = PlayerStateBPClass.Class;
	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("[UETOPIA] [AMyGameMode] [Contruct] DID NOT find BP Player State"));
		PlayerStateClass = AMyPlayerState::StaticClass();
	}

	// Blueprint'/Game/Blueprints/PlayerController/bp_MyPlayerController.bp_MyPlayerController'
	static ConstructorHelpers::FClassFinder<AMyPlayerController> PlayerControllerBPClass(TEXT("/Game/Blueprints/PlayerController/bp_MyPlayerController.bp_MyPlayerController"));
	if (PlayerControllerBPClass.Class != NULL)
	{
		UE_LOG(LogTemp, Log, TEXT("[UETOPIA] [AMyGameMode] [Contruct] Found BP Player Controller"));
		PlayerControllerClass = PlayerControllerBPClass.Class;
	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("[UETOPIA] [AMyGameMode] [Contruct] DID NOT find BP Player Controller"));
		PlayerControllerClass = AMyPlayerController::StaticClass();
	}
	*/
	GameStateClass = AMyGameState::StaticClass();
	PlayerStateClass = AMyPlayerState::StaticClass();
	PlayerControllerClass = AMyPlayerController::StaticClass();

	bUseSeamlessTravel = true;
	
}

void AMyGameMode::BeginPlay()
{
	Super::BeginPlay();

	UE_LOG(LogTemp, Log, TEXT("[UETOPIA] [AMyGameMode] BeginPlay"));

	//if (HUDWidgetClass != nullptr)
	//{
	//	CurrentWidget = CreateWidget<UUserWidget>(GetWorld(), HUDWidgetClass);
	//	if (CurrentWidget != nullptr)
	//	{
	//		CurrentWidget->AddToViewport();
	//	}
	//}

	// Tried to set the player name.  not working like this.  
	/*
	APlayerController* pc = NULL;
	for (FConstPlayerControllerIterator Iterator = GetWorld()->GetPlayerControllerIterator(); Iterator; ++Iterator)
	{
	pc = Iterator->Get();
	//AMyPlayerController* Mypc = Cast(pc);

	AUEtopiaCompetitiveCharacter* pawn = Cast<AUEtopiaCompetitiveCharacter>(pc->GetCharacter());
	pawn->Text->SetText(FText::FromString(pc->PlayerState->PlayerName));
	// TODO set color
	}
	*/



}

/** Returns game session class to use */
TSubclassOf<AGameSession> AMyGameMode::GetGameSessionClass() const
{
	return AMyGameSession::StaticClass();
	//return AMyGameSession::StaticClass();
}


FString AMyGameMode::InitNewPlayer(APlayerController* NewPlayerController, const FUniqueNetIdRepl& UniqueId, const FString& Options, const FString& Portal)
{

	UE_LOG(LogTemp, Log, TEXT("[UETOPIA] [AMyGameMode] InitNewPlayer"));

	FString ErrorMessage;

	check(NewPlayerController);

	//  we need to set the platformID in the player state so we can find this player again.
	AMyPlayerState* PlayerS = Cast<AMyPlayerState>(NewPlayerController->PlayerState);
	FString Name = UGameplayStatics::ParseOption(Options, TEXT("Name"));

	if (PlayerS)
	{


		UE_LOG(LogTemp, Log, TEXT("[UETOPIA] [AMyGameMode] InitNewPlayer Param1: %s"), *Name);

		UE_LOG(LogTemp, Log, TEXT("[UETOPIA] [AMyGameMode] [InitNewPlayer] - Found My player state"));
		PlayerS->playerKeyId = Name;
		UE_LOG(LogTemp, Log, TEXT("[UETOPIA] [AMyGameMode] [InitNewPlayer] - Set platformID"));
	}


	// TODO: this should only run on dedicated server
	if (IsRunningDedicatedServer())
	{
		UE_LOG(LogTemp, Log, TEXT("[UETOPIA] AMyGameMode::InitNewPlayer RUNNING ON DEDICATED SERVER!"));


		int32 playerId = PlayerS->PlayerId; // NewPlayerController->PlayerState->PlayerId;

		UE_LOG(LogTemp, Log, TEXT("[UETOPIA] [AMyGameMode] InitNewPlayer playerId: %d"), playerId);
		UE_LOG(LogTemp, Log, TEXT("[UETOPIA] [AMyGameMode] InitNewPlayer Options: %s"), *Options);

		/* At this point we want to be able to deny the Login, but we need to do it over http, which requires a delegate.
		// So we're just going to allow login, then kick them if the http request comes up negative
		// TODO find a better way to do this - it should probably be part of onlineSubsystem.
		*/
		UMyGameInstance* TheGameInstance = Cast<UMyGameInstance>(GetWorld()->GetGameInstance());
		AMyPlayerController* playerC = Cast<AMyPlayerController>(NewPlayerController);

		// WE need to move this...  We don't have the player access token yet.
		//TheGameInstance->ActivatePlayer(playerC, Name, playerId, UniqueId);

		// save the vars in the controller so we can run activate later.
		playerC->UniqueId = UniqueId;
		playerC->playerKeyId = Name;
		playerC->playerIDTemp = playerId;

		// Register the player with the session
		// The uniqueId changed incoming and it's breaking everything else downstream
		//Tring to reconstruct it, not working
		const TSharedPtr<const FUniqueNetId> UniqueIdTemp = UniqueId.GetUniqueNetId();

		//so just turning it off for now
		GameSession->RegisterPlayer(NewPlayerController, UniqueIdTemp, UGameplayStatics::HasOption(Options, TEXT("bIsFromInvite")));

		// Init player's name
		FString InName = UGameplayStatics::ParseOption(Options, TEXT("Name")).Left(20);
		if (InName.IsEmpty())
		{
			InName = FString::Printf(TEXT("%s%i"), *DefaultPlayerName.ToString(), NewPlayerController->PlayerState->PlayerId);
		}

		ChangeName(NewPlayerController, InName, false);

		
		// Find a starting spot
		// This should be handled in the BP - testing
		/*
		AActor* const StartSpot = FindPlayerStart(NewPlayerController, Portal);
		if (StartSpot != NULL)
		{
			// Set the player controller / camera in this new location
			FRotator InitialControllerRot = StartSpot->GetActorRotation();
			InitialControllerRot.Roll = 0.f;
			NewPlayerController->SetInitialLocationAndRotation(StartSpot->GetActorLocation(), InitialControllerRot);
			NewPlayerController->StartSpot = StartSpot;
		}
		else
		{
			ErrorMessage = FString::Printf(TEXT("Failed to find PlayerStart"));
		}
		*/

	}

	return ErrorMessage;
}

void AMyGameMode::Logout(AController* Exiting)
{
	// Handle users that disconnect from the server.
	UE_LOG(LogTemp, Log, TEXT("[UETOPIA] [AMyGameMode] [Logout] "));
	Super::Logout(Exiting);

	AMyPlayerState* ExitingPlayerState = Cast<AMyPlayerState>(Exiting->PlayerState);
	int ExitingPlayerId = ExitingPlayerState->PlayerId;

	UE_LOG(LogTemp, Log, TEXT("[UETOPIA] [AMyGameMode] [Logout] ExitingPlayerId: %i"), ExitingPlayerId);

	UMyGameInstance* TheGameInstance = Cast<UMyGameInstance>(GetWorld()->GetGameInstance());

	TheGameInstance->DeActivatePlayer(ExitingPlayerId);

}


void AMyGameMode::HandleSeamlessTravelPlayer(AController*& C)
{
	UE_LOG(LogTemp, Log, TEXT("[UETOPIA] [AMyGameMode] [HandleSeamlessTravelPlayer] "));
	// Send the player over to blueprints for OpenMoba init 

	APlayerController* playerC = Cast<APlayerController>(C);
	ReceiveEventOnPostLogin(playerC);

	// Also tell blueprints to save the player state
	AMyPlayerController* myPlayerC = Cast<AMyPlayerController>(C);
	myPlayerC->ReceiveRecievePlayerState();

	// Also tell the playerState to reload customTextures
	// Totally not working.
	//AMyPlayerState* playerState = Cast<AMyPlayerState>(myPlayerC->PlayerState);
	//UMyGameInstance* TheGameInstance = Cast<UMyGameInstance>(GetWorld()->GetGameInstance());
	//playerState->customTextures.Empty();
	//playerState->customTextures = TheGameInstance->customTextures;
	//playerState->OnRep_OnCustomTextureChange();

}