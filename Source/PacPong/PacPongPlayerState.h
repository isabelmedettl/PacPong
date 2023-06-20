// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "PacPongPlayerState.generated.h"

class USavePacGame;
/**
 * 
 */
UCLASS()
class PACPONG_API APacPongPlayerState : public APlayerState
{
	GENERATED_BODY()


protected:
	UPROPERTY(EditDefaultsOnly, Category="Scores")
	int32 Scores;
	
	UPROPERTY(BlueprintReadOnly)
	float HighScorePersonal;


public:
	UFUNCTION(BlueprintCallable)
	bool UpdateHighScore(int64 NewScore);

	UFUNCTION(BlueprintCallable, Category="Scores")
	int64 GetPacScore() const;

	UFUNCTION(BlueprintCallable, Category="Scores")
	void AddScore(int64 NewScore);

	UFUNCTION(BlueprintCallable, Category="Scores")
	bool RemoveScore(int64 NewScore);

	UFUNCTION()
	virtual void SavePlayerState(USavePacGame* PacSaveObject);

	UFUNCTION()
	virtual void LoadPlayerState(USavePacGame* PacSaveObject);

	
	
};