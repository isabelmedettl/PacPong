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

	UPROPERTY(VisibleAnywhere, Category = Basic)
	FString PlayerName;

	UPROPERTY(VisibleAnywhere, Category = Basic)
	int64 HighScore;
};
UCLASS()
class PACPONG_API USavePacGame : public USaveGame
{
	GENERATED_BODY()

public:
	
	UPROPERTY()
	FSavePlayer SavedPlayer;

	UPROPERTY(VisibleAnywhere, Category = Basic)
	FString SaveSlotName;

	UPROPERTY(VisibleAnywhere, Category = Basic)
	uint32 UserIndex;
	
	void SaveGame(FString SaveName, int64 SaveScore);
	
};
