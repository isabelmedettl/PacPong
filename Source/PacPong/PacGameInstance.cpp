// Fill out your copyright notice in the Description page of Project Settings.


#include "PacGameInstance.h"

#include "SavePacGame.h"
#include "Kismet/GameplayStatics.h"

void UPacGameInstance::Init()
{
	Super::Init();

	SaveLoad();
}

void UPacGameInstance::SaveLoad()
{
	if (UGameplayStatics::DoesSaveGameExist("deafult", 0))
	{
		SavedGame = Cast<USavePacGame>(UGameplayStatics::LoadGameFromSlot("deafult", 0));
		if (SavedGame)
		{
			SavedPlayers = SavedGame->SavedPlayers;
		}
	}
	else if (!UGameplayStatics::DoesSaveGameExist("deafult", 0))
	{
		SavedGame= Cast<USavePacGame>(UGameplayStatics::CreateSaveGameObject(USavePacGame::StaticClass()));
		if( IsValid(SavedGame) )
		{
			UGameplayStatics::SaveGameToSlot(SavedGame, TEXT("deafult"), 0);
			GEngine->AddOnScreenDebugMessage(-1, 12.f, FColor::Red, TEXT("SAvedSlot deafult 0") );
		}
	}
	else { if( GEngine ) GEngine->AddOnScreenDebugMessage(-1, 12.f, FColor::Red, TEXT("Error: Unable to save...")); }
}
