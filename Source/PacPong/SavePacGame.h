// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "SavePacGame.generated.h"

/**
 * 
 */
UCLASS()
class PACPONG_API USavePacGame : public USaveGame
{
	GENERATED_BODY()

public:

	USavePacGame();
	
	UPROPERTY(VisibleAnywhere, Category = Basic)
	FString PlayerName;

	UPROPERTY(VisibleAnywhere, Category = Basic)
	int64 HighScore;
	
	void SaveGame();
	
	void LoadGame();
	
};
