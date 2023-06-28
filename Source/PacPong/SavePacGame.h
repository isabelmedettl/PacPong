// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "SavePacGame.generated.h"

/**
 * 
 */

USTRUCT()
struct FSavedPlayer
{
	GENERATED_BODY()
	
	FSavedPlayer()
	{
		PlayerName = " ";
		HighScore = 0;
	}

	/** Identifies player name??*/
	UPROPERTY(VisibleAnywhere, Category = Basic)
	FString PlayerName;

	UPROPERTY(VisibleAnywhere, Category = Basic)
	int64 HighScore;

	/** Identifies for which actor this belongs to*/
	UPROPERTY(VisibleAnywhere, Category = Basic)
	FName ActorName;

	/** Contains all savegame-marked variables of actor*/
	UPROPERTY()
	TArray<uint8> ByteData;
	
	FORCEINLINE bool operator<(const FSavedPlayer& Other) const
	{
		return HighScore < Other.HighScore;
	}

	FORCEINLINE bool operator==(const FSavedPlayer& Other) const
	{
		return PlayerName.Equals(Other.PlayerName) && HighScore == Other.HighScore;
	}
	
};
UCLASS()
class PACPONG_API USavePacGame : public USaveGame
{
	GENERATED_BODY()

public:

	UPROPERTY(VisibleAnywhere)
	TArray<FSavedPlayer> SavedPlayers = TArray<FSavedPlayer>();

	UPROPERTY(VisibleAnywhere)
	TArray<int64> SavedHighScores = TArray<int64>();
	
	UPROPERTY(VisibleAnywhere)
	TArray<FString> SavedPlayerNames = TArray<FString>();
	
	UPROPERTY(VisibleAnywhere, Category = Basic)
	FString SaveSlotName;

	UPROPERTY(VisibleAnywhere, Category = Basic)
	uint32 UserIndex;

	UPROPERTY(VisibleAnywhere, Category = Basic)
	int64 HighestScore;
	
	void SaveGame(FString SaveName, int64 SaveScore);

	void LoadGame(int64 SaveHighScore);

	void SaveSavedPlayer(FSavedPlayer* PlayerToSave);

	bool CheckIfValidScore(const int64 HighScoreToCheck);
	
};


