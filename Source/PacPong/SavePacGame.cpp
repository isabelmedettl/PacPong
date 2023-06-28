// Fill out your copyright notice in the Description page of Project Settings.


#include "SavePacGame.h"

#include "Kismet/GameplayStatics.h"


void USavePacGame::SaveGame(FString SaveName, int64 SaveScore)
{	
	FSavedPlayer PlayerToSave = FSavedPlayer();
	PlayerToSave.PlayerName = SaveName;
	PlayerToSave.HighScore = SaveScore;
	if (SavedPlayers.Num() < 10)
	{
		SavedPlayers.Add(PlayerToSave);
		SavedPlayers.Sort();
		for (FSavedPlayer x : SavedPlayers)
		{
			GEngine->AddOnScreenDebugMessage(-1,200,FColor::Green,FString::Printf(TEXT("Printing all saved players, Saved name %s, Saved score %i"), *x.PlayerName, x.HighScore));
		}
	}
	else if (SavedPlayers.Contains(PlayerToSave))
	{
		SaveSavedPlayer(&PlayerToSave);
		GEngine->AddOnScreenDebugMessage(-1,200,FColor::Green,FString::Printf(TEXT("Saved already saved player, Saved name %s, Saved score %i"), *PlayerToSave.PlayerName, PlayerToSave.HighScore));
		for (FSavedPlayer x : SavedPlayers)
		{
			GEngine->AddOnScreenDebugMessage(-1,200,FColor::Green,FString::Printf(TEXT("Printing all saved players, Saved name %s, Saved score %i"), *x.PlayerName, x.HighScore));
		}

	}
	else if (CheckIfValidScore(PlayerToSave.HighScore))
	{
		SavedPlayers.Remove(SavedPlayers[SavedPlayers.Num()-1]);
		SavedPlayers.Add(PlayerToSave);
		SavedPlayers.Sort();
		GEngine->AddOnScreenDebugMessage(-1,200,FColor::Green,FString::Printf(TEXT("Saved saved new player, Saved name %s, Saved score %i"), *PlayerToSave.PlayerName, PlayerToSave.HighScore));
	}
	else
	{
		if (SaveName.IsEmpty()) GEngine->AddOnScreenDebugMessage(-1, 12.f, FColor::Red, TEXT("Error: Couldnt save ")); 
	}
	
}

void USavePacGame::LoadGame()
{
	
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
				SavedPlayers.Sort();
			}
		}
	}
}

bool USavePacGame::CheckIfValidScore(const int64 HighScoreToCheck)
{
	return SavedPlayers[SavedPlayers.Num()-1].HighScore < HighScoreToCheck;
}
