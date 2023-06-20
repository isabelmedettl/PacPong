// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "SavePacGame.generated.h"

/**
 * 
 */

USTRUCT()
struct FSavePlayer
{
	GENERATED_BODY()

	//FSavePlayer(FString Name, int64 Score) : PlayerName(Name), HighScore(Score){}

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
	
};
UCLASS()
class PACPONG_API USavePacGame : public USaveGame
{
	GENERATED_BODY()

public:


	
	//UPROPERTY()
	//TArray<FSavePlayer> SavedPlayers = TArray<FSavePlayer>();

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

	bool CheckIfValid(FString SaveName, int64 SaveScore);
	
};


