// Fill out your copyright notice in the Description page of Project Settings.


#include "SavePacGame.h"

#include "HighScoreUserWidget.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Kismet/GameplayStatics.h"


void USavePacGame::SaveGame(FString SaveName, int64 SaveScore)
{	
	FSavedPlayer PlayerToSave = FSavedPlayer();
	PlayerToSave.PlayerName = SaveName;
	PlayerToSave.HighScore = SaveScore;
	if (SavedPlayers.Num() < 10)
	{
		SavedPlayers.Add(PlayerToSave);
	}
	else if (SavedPlayers.Contains(PlayerToSave))
	{
		SaveSavedPlayer(&PlayerToSave);
		
	}
	else if (CheckIfValidScore(PlayerToSave.HighScore))
	{
		SavedPlayers.Remove(SavedPlayers[SavedPlayers.Num()-1]);
		SavedPlayers.Add(PlayerToSave);
	}
	else
	{
		if (SaveName.IsEmpty()) GEngine->AddOnScreenDebugMessage(-1, 12.f, FColor::Red, TEXT("Error: Couldnt save ")); 
	}
	SavedPlayers.Sort();
}

void USavePacGame::SaveSavedPlayer(FSavedPlayer* PlayerToSave)
{
	if (SavedPlayers.Num() >= 10)
	{
		const uint32 Index = SavedPlayers.Find(*PlayerToSave);
		if (Index != INDEX_NONE)
		{
			if (SavedPlayers[Index].HighScore <= PlayerToSave->HighScore)
			{
				SavedPlayers[Index].HighScore = PlayerToSave->HighScore;
			}
		}
	}
}

bool USavePacGame::CheckIfValidScore(const int64 HighScoreToCheck)
{
	if (SavedPlayers.Num() > 10)
	{
		return true;
	}
	return SavedPlayers[SavedPlayers.Num()-1].HighScore < HighScoreToCheck;
}
