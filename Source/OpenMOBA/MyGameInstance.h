// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine/GameInstance.h"
#include "Http.h"
#include "Json.h"
#include "JsonUtilities.h"
#include "Online.h"
#include "Base64.h"
#include "math.h"
#include <string>
//#include "RamaSaveLibrary.h"
//#include "MyServerPortalActor.h"
#include "MyTypes.h"
#include "MyGameInstance.generated.h"


USTRUCT(BlueprintType)
struct FMyActivePlayer {

	GENERATED_USTRUCT_BODY()
		UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UETOPIA")
		int32 playerID;
	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UETOPIA")
	//	FString platformID;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UETOPIA")
		FString playerKeyId;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UETOPIA")
		FString playerTitle;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UETOPIA")
		bool authorized;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UETOPIA")
		int32 roundKills;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UETOPIA")
		int32 roundDeaths;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UETOPIA")
		TArray<FString> killed;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UETOPIA")
		TArray<FUserEvent> events;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UETOPIA")
		int32 rank;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UETOPIA")
		int32 experience;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UETOPIA")
		int32 score;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UETOPIA")
		int32 currencyCurrent;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UETOPIA")
		FString gamePlayerKeyId;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UETOPIA")
		FUniqueNetIdRepl UniqueId;

	AMyPlayerController* PlayerController;

	FTimerHandle GetPlayerInfoDelayHandle;
	FTimerDelegate GetPlayerInfoTimerDel;
};

USTRUCT(BlueprintType)
struct FMyActivePlayers {

	GENERATED_USTRUCT_BODY()
		UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UETOPIA")
		TArray<FMyActivePlayer> ActivePlayers;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UETOPIA")
		FString encryption;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UETOPIA")
		FString nonce;
};

// Matchmaker specific structs.  These are used with uetopia matchmaker functionality.
USTRUCT(BlueprintType)
struct FMyMatchPlayer {

	GENERATED_USTRUCT_BODY()
		UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UETOPIA")
		int32 playerID;
	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UETOPIA")
	//	FString platformID;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UETOPIA")
		FString userKeyId;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UETOPIA")
		FString userTitle;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UETOPIA")
		bool joined;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UETOPIA")
		int32 teamId;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UETOPIA")
		FString teamKeyId;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UETOPIA")
		FString teamTitle;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UETOPIA")
		bool win;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UETOPIA")
		TArray<FString> killed;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UETOPIA")
		int32 roundKills;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UETOPIA")
		int32 roundDeaths;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UETOPIA")
		bool currentRoundAlive;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UETOPIA")
		int32 rank;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UETOPIA")
		int32 score;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UETOPIA")
		int32 experience;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UETOPIA")
		FString gamePlayerKeyId;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UETOPIA")
		FUniqueNetIdRepl UniqueId;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UETOPIA")
		bool characterCustomized;

	AMyPlayerController* PlayerController;

	FTimerHandle GetPlayerInfoDelayHandle;
	FTimerDelegate GetPlayerInfoTimerDel;

};

USTRUCT(BlueprintType)
struct FMyMatchInfo {

	GENERATED_USTRUCT_BODY()
		UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UETOPIA")
		TArray<FMyMatchPlayer> players;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UETOPIA")
		int32 admissionFee;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UETOPIA")
		FString title;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UETOPIA")
		int32 api_version;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UETOPIA")
		bool authorization;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UETOPIA")
		FString encryption;
	// Keep track of which game mode this match should be using
	// The keyId is the unique identifier, and the title is the Subsystem reference
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UETOPIA")
		int32 gameModeKeyId;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UETOPIA")
		FString gameModeTitle;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UETOPIA")
		TArray<FString> sponsors;
};

USTRUCT(BlueprintType)
struct FMyTeamInfo {

	GENERATED_USTRUCT_BODY()
		UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UETOPIA")
		TArray<FMyMatchPlayer> players;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UETOPIA")
		FString title;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UETOPIA")
		int32 number;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UETOPIA")
		int32 roundWinCount;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UETOPIA")
		int32 averageRank;
};

USTRUCT(BlueprintType)
struct FMyTeamList {

	GENERATED_USTRUCT_BODY()
		UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UETOPIA")
		TArray<FMyTeamInfo> teams;
};

class AMyGameSession;

namespace MyGameInstanceState
{
	extern const FName None;
	extern const FName PendingInvite;
	extern const FName WelcomeScreen;
	extern const FName MainMenu;
	extern const FName MessageMenu;
	extern const FName Playing;
}


/**
*
*/
UCLASS()
class OPENMOBA_API UMyGameInstance : public UGameInstance
{
	GENERATED_UCLASS_BODY()


		// Populated through config file
		FString UEtopiaMode;
	FString APIURL;
	FString ServerAPIKey;  // Reusing these for matches as well, even though it's a match Key/Secret
	FString ServerAPISecret;  // Reusing these for matches as well, even though it's a match Key/Secret
	FString GameKey;
	
	// Populated through the get server info API call
	int32 incrementCurrency; // how much to increment for kills
	int32 serverCurrency; // how much does this server have to spend/use
	int32 minimumCurrencyRequired;
	FString ServerTitle;
	// Populated through the get match info API call
	int32 admissionFee;
	FString MatchTitle;
	bool UEtopiaCharactersEnabled; // Switch for running with or without characters

	// Populated through the online subsystem
	FString ServerSessionHostAddress;
	FString ServerSessionID;

	// Constructor declaration
	//UMyGameInstance(const FObjectInitializer& ObjectInitializer);

	//UMyGameInstance();


	// Moving this to a struct for easy JSON encode/decode
	//TArray<FMyActivePlayer> ActivePlayers;

	// Use this for Dedicated Server.
	FMyActivePlayers PlayerRecord;
	FMyServerLinks ServerLinks;

	// Use this for matchmaker/competitive
	UPROPERTY(BlueprintReadOnly)
	FMyMatchInfo MatchInfo;
	bool MatchStarted;
	int32 RoundWinsNeededToWinMatch;



	bool PerformHttpRequest(void(UMyGameInstance::*delegateCallback)(FHttpRequestPtr, FHttpResponsePtr, bool), FString APIURI, FString ArgumentString, FString AccessToken);
	bool PerformJsonHttpRequest(void(UMyGameInstance::*delegateCallback)(FHttpRequestPtr, FHttpResponsePtr, bool), FString APIURI, FString ArgumentString, FString AccessToken);

	/* Handles to manage timers */
	FTimerHandle ServerLinksTimerHandle;
	FTimerHandle RewardSpawnTimerHandle;
	FTimerHandle AttemptStartMatchTimerHandle;

public:

	UPROPERTY(BlueprintReadOnly)
		FMyTeamList TeamList;

	AMyGameSession* GetGameSession() const;
	virtual void Init() override;

	/**
	*	Find an online session
	*
	*	@param UserId user that initiated the request
	*	@param SessionName name of session this search will generate
	*	@param bIsLAN are we searching LAN matches
	*	@param bIsPresence are we searching presence sessions
	*/

	// TODO move this to playerController
	UFUNCTION(BlueprintCallable, Category = "UETOPIA")
		bool StartMatchmaking(ULocalPlayer* PlayerOwner, FString MatchType);

	UFUNCTION(BlueprintCallable, Category = "UETOPIA")
		bool CancelMatchmaking(ULocalPlayer* PlayerOwner);

	/**
	*	Find an online session
	*
	*	@param UserId user that initiated the request
	*	@param SessionName name of session this search will generate
	*	@param bIsLAN are we searching LAN matches
	*	@param bIsPresence are we searching presence sessions
	*/
	UFUNCTION(BlueprintCallable, Category = "UETOPIA")
		bool FindSessions(ULocalPlayer* PlayerOwner, bool bLANMatch);

	// we need one for the server too without a playerowner
	bool FindSessions(bool bLANMatch);

	/** Sends the game to the specified state. */
	void GotoState(FName NewState);

	/** Obtains the initial welcome state, which can be different based on platform */
	FName GetInitialState();

	/** Sends the game to the initial startup/frontend state  */
	void GotoInitialState();

	UFUNCTION(BlueprintCallable, Category = "UETOPIA")
		bool JoinSession(ULocalPlayer* LocalPlayer, int32 SessionIndexInSearchResults);

	bool JoinSession(ULocalPlayer* LocalPlayer, const FOnlineSessionSearchResult& SearchResult);

	/** Returns true if the game is in online mode */
	bool GetIsOnline() const { return bIsOnline; }

	/** Sets the online mode of the game */
	UFUNCTION(BlueprintCallable, Category = "UETOPIA")
		void SetIsOnline(bool bInIsOnline);

	/** Start the authentication flow */
	UFUNCTION(BlueprintCallable, Category = "UETOPIA")
		void BeginLogin(FString InType, FString InId, FString InToken);

	/** Shuts down the session, and frees any net driver */
	void CleanupSessionOnReturnToMenu();

	void RemoveExistingLocalPlayer(ULocalPlayer* ExistingPlayer);
	void RemoveSplitScreenPlayers();

	/* Get Server info is for Continuous servers.  Since we're using matchmaker on this demo, this is never called. */
	bool GetServerInfo();
	void GetServerInfoComplete(FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded);

	/* Get Match info is for Matchmaker. */
	bool GetMatchInfo();
	void GetMatchInfoComplete(FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded);

	void AttemptStartMatch();

	void GetServerLinks();
	//bool GetServerLinks();
	void GetServerLinksComplete(FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded);

	void AttemptSpawnReward();

	UPROPERTY(BlueprintReadOnly)
		TArray<FMySessionSearchResult> MySessionSearchResults;

	// Holds session search results
	TSharedPtr<class FOnlineSessionSearch> SessionSearch;

	/**
	* Travel to a session URL (as client) for a given session
	*
	* @param ControllerId controller initiating the session travel
	* @param SessionName name of session to travel to
	*
	* @return true if successful, false otherwise
	*/
	bool TravelToSession(int32 ControllerId, FName SessionName);

	bool RegisterNewSession(FString IncServerSessionHostAddress, FString IncServerSessionID);

	/** Returns true if the passed in local player is signed in and online */
	bool IsLocalPlayerOnline(ULocalPlayer* LocalPlayer);

	/** Returns true if owning player is online. Displays proper messaging if the user can't play */
	bool ValidatePlayerForOnlinePlay(ULocalPlayer* LocalPlayer);


	// Activate a player against the uetopia api
	// Depending on the UEtopiaMode, this has slightly different behavior
	// In dedicated mode, it finishes with ActivateRequestComplete
	// In competitive mode, it finishes with ActivateMatchPlayerRequestComplete
	UFUNCTION(BlueprintCallable, Category = "UETOPIA")
		bool ActivatePlayer(class AMyPlayerController* NewPlayerController, FString playerKeyId, int32 playerID, const FUniqueNetIdRepl& UniqueId);
	void ActivateRequestComplete(FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded);
	void ActivateMatchPlayerRequestComplete(FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded);

	bool DeActivatePlayer(int32 playerID);
	void DeActivateRequestComplete(FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded);

	bool OutgoingChat(int32 playerID, FText message);
	void OutgoingChatComplete(FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded);

	bool SubmitMatchResults();
	void SubmitMatchResultsComplete(FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded);

	// Submit MM Results must be the last thing that happens.
	// Once itis finished, the match API Key and Secret are invalidated, and no more requests will be honored.
	// Since we need to SaveGamePlayer data as well, we're going to put the Submit MM call on a timer.
	// 5 sec should be sufficient, but we'll use 10 to be safe.
	UFUNCTION()
	bool SubmitMatchMakerResults();
	void SubmitMatchMakerResultsComplete(FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded);

	FTimerHandle SubmitMMResultsDelayHandle;
	FTimerDelegate SubmitMMResultsTimerDel;

	// We want to kick players off the server so they can return to the lobby and start matchmaking again.
	// We'll do this on a timer as well so they can see the match results page for a few seconds first.
	UFUNCTION()
		bool KickPlayersFromServer();

	FTimerHandle KickPlayersDelayHandle;
	FTimerDelegate KickPlayersTimerDel;

	// prevent possible duplicate matchmaker submissions
	bool MatchMakerResultsSubmitted = false;

	UFUNCTION()
	bool GetGamePlayer(FString playerKeyId, bool bAttemptLock);
	void GetGamePlayerRequestComplete(FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded);

	UFUNCTION(BlueprintCallable, Category = "UETOPIA")
		bool SaveGamePlayer(FString playerKeyId, bool bAttemptUnLock);
	void SaveGamePlayerRequestComplete(FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded);

	void TransferPlayer(const FString& ServerKey, int32 playerID, bool checkOnly);
	void TransferPlayerRequestComplete(FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded);

	bool Purchase(FString playerKeyId, FString itemName, FString description, int32 amount);
	void PurchaseRequestComplete(FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded);

	bool Reward(FString playerKeyId, FString itemName, FString description, int32 amount);
	void RewardRequestComplete(FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded);

	void RequestBeginPlay();

	UFUNCTION(BlueprintCallable, Category = "UETOPIA")
		void LoadServerStateFromFile();

	// Get a player out of our custom array struct
	// PlayerID is the internal Unreal engine Integer ID
	FMyActivePlayer* getPlayerByPlayerId(int32 playerID);
	FMyActivePlayer* getPlayerByPlayerKey(FString playerKeyId);

	// Get Match player 
	FMyMatchPlayer* getMatchPlayerByPlayerId(int32 playerID);
	FMyMatchPlayer* getMatchPlayerByPlayerKey(FString playerKeyId);

	// Get a server out of our custom array struct
	FMyServerLink* getServerByKey(FString serverKey);

	// count the number of active players
	int32 getActivePlayerCount();

	// A Kill occurred.
	// Record it.
	UFUNCTION(BlueprintCallable, Category = "UETOPIA")
		bool RecordKill(int32 killerPlayerID, int32 victimPlayerID);

	// Get a serverLink our of our serverlinks array by targetServerKeyId
	UFUNCTION(BlueprintCallable, Category = "UETOPIA")
		FMyServerLink GetServerLinkByTargetServerKeyId(FString incomingTargetServerKeyId);

	int32 getSpawnRewardValue();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UETOPIA")
		int32 MinimumKillsBeforeResultsSubmit;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UETOPIA")
		int32 teamCount;

	UFUNCTION(BlueprintCallable, Category = "UETOPIA")
		bool RecordRoundWin(int32 winnerTeamID);

private:
	UPROPERTY(config)
		FString WelcomeScreenMap;

	UPROPERTY(config)
		FString MainMenuMap;

	FName CurrentState;
	FName PendingState;

	/** URL to travel to after pending network operations */
	FString TravelURL;

	FString _configPath = "";

	/** Whether the match is online or not */
	bool bIsOnline;

	/** If true, enable splitscreen when map starts loading */
	bool bPendingEnableSplitscreen;

	/** Whether the user has an active license to play the game */
	bool bIsLicensed;

	/** Last connection status that was passed into the HandleNetworkConnectionStatusChanged hander */
	EOnlineServerConnectionStatus::Type	CurrentConnectionStatus;

	/** Handle to various registered delegates */
	FDelegateHandle OnSearchSessionsCompleteDelegateHandle;
	//FDelegateHandle OnSearchResultsAvailableHandle;
	FDelegateHandle OnCreatePresenceSessionCompleteDelegateHandle;
	FDelegateHandle TravelLocalSessionFailureDelegateHandle;
	FDelegateHandle OnJoinSessionCompleteDelegateHandle;
	FDelegateHandle OnStartSessionCompleteDelegateHandle;
	FDelegateHandle OnEndSessionCompleteDelegateHandle;
	FDelegateHandle OnDestroySessionCompleteDelegateHandle;
	//FDelegateHandle OnMatchmakingCompleteDelegateHandle;

	/** Callback which is intended to be called upon finding sessions */
	void OnSearchSessionsComplete(bool bWasSuccessful);
	/** Callback which is intended to be called upon joining session */
	void OnJoinSessionComplete(EOnJoinSessionCompleteResult::Type Result);
	/** Called after all the local players are registered in a session we're joining */
	void FinishJoinSession(EOnJoinSessionCompleteResult::Type Result);
	/** Travel directly to the named session */
	void InternalTravelToSession(const FName& SessionName);



	/** Delegate for ending a session */
	FOnEndSessionCompleteDelegate OnEndSessionCompleteDelegate;

	void HandleSessionFailure(const FUniqueNetId& NetId, ESessionFailure::Type FailureType);

	void OnEndSessionComplete(FName SessionName, bool bWasSuccessful);

	void BeginWelcomeScreenState();
	void AddNetworkFailureHandlers();
	void RemoveNetworkFailureHandlers();

	/** Called when there is an error trying to travel to a local session */
	void TravelLocalSessionFailure(UWorld *World, ETravelFailure::Type FailureType, const FString& ErrorString);

	/** Show messaging and punt to welcome screen */
	void HandleSignInChangeMessaging();

	// OSS delegates to handle
	void HandleUserLoginChanged(int32 GameUserIndex, ELoginStatus::Type PreviousLoginStatus, ELoginStatus::Type LoginStatus, const FUniqueNetId& UserId);

	void HandleUserLoginComplete(int32 LocalUserNum, bool bWasSuccessful, const FUniqueNetId& UserId, const FString& Error);

	

	

	// We need to be aware of the HasBegunPlay function coming from gameState
	// Certain things will fail (like spawning actors), if the loadLevel has not completed.

	/*
	void SpawnServerPortals();
	TArray<AMyServerPortalActor*> ServerPortalActorReference;
	*/


	/** Whether the match is online or not */
	bool bRequestBeginPlayStarted;

	/** Variables to control the spawning of rewards */
	bool bSpawnRewardsEnabled;
	int32 SpawnRewardServerMinimumBalanceRequired;
	float SpawnRewardChance;
	int32 SpawnRewardValue;
	float SpawnRewardTimerSeconds;

	float SpawnRewardLocationXMin;
	float SpawnRewardLocationXMax;
	float SpawnRewardLocationYMin;
	float SpawnRewardLocationYMax;
	float SpawnRewardLocationZMin;
	float SpawnRewardLocationZMax;

	/** Variables to control the purchase of cubes */
	int32 CubeStoreCost;

public:
	// Custom texture url strings.
	// This is populated from the get match info complete function, and reads tournament sponsor textures as set on the backend.
	TArray<FString> customTextures;

	UFUNCTION(BlueprintCallable, Category = "UETOPIA")
	void CalculateNewTeamRank(int32 WinnerTeamIndex, int32 LoserTeamIndex);


protected:
	/** Delegate for creating a new session */
	//FOnCreateSessionCompleteDelegate OnCreateSessionCompleteDelegate;
	/**
	* Delegate fired when a session create request has completed
	*
	* @param SessionName the name of the session this callback is for
	* @param bWasSuccessful true if the async action completed without error, false if there was an error
	*/
	virtual void OnCreateSessionComplete(FName SessionName, bool bWasSuccessful);

	void CalculateNewRank(int32 WinnerPlayerIndex, int32 LoserPlayerIndex, bool penalizeLoser);

};
