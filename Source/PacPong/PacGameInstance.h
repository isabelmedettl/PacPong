// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "PacGameInstance.generated.h"

class USavePacGame;
struct FSavedPlayer;

/**
 * 
 */
UCLASS()
class PACPONG_API UPacGameInstance : public UGameInstance
{
	GENERATED_BODY()


public:
	virtual void Init() override;

	UFUNCTION(BlueprintCallable)
	void SaveLoad();
	
	UPROPERTY(VisibleAnywhere)
	USavePacGame* SavedGame;

	UPROPERTY(VisibleAnywhere)
	TArray<FSavedPlayer> SavedPlayers = TArray<FSavedPlayer>();
	
};
