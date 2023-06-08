// Fill out your copyright notice in the Description page of Project Settings.


#include "SavePacGame.h"

#include "Kismet/GameplayStatics.h"

USavePacGame::USavePacGame()
{
	SaveSlotName = TEXT("Player1");
}

void USavePacGame::SaveGame()
{
	USavePacGame* SaveGameInstance = Cast<USavePacGame>(UGameplayStatics::CreateSaveGameObject(USavePacGame::StaticClass()));
	if (SaveGameInstance)
	{
		// Set data on the savegame object.
		SaveGameInstance->SavedPlayer.PlayerName = TEXT("PlayerOne");

		if (UGameplayStatics::DoesSaveGameExist(SaveSlotName, UserIndex))
		{
			
		}
		// Save the data immediately.
		if (UGameplayStatics::SaveGameToSlot(SaveGameInstance, SaveSlotName, UserIndex))
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, FString::Printf(TEXT("GameSaved")));
		}
	}
}

