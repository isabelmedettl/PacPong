// Fill out your copyright notice in the Description page of Project Settings.


#include "SavePacGame.h"

#include "Kismet/GameplayStatics.h"


void USavePacGame::SaveGame(FString SaveName, int64 SaveScore)
{
	if (SaveName.IsEmpty()) GEngine->AddOnScreenDebugMessage(-1, 12.f, FColor::Red, TEXT("Error: No name")); 

	//FSavePlayer PlayerToSave = FSavePlayer(SaveName, SaveScore);
	if (SavedPlayerNames.Num() == 0)
	{
		//SavedPlayers.Add(PlayerToSave);
		SavedPlayerNames.Add(SaveName);
		SavedHighScores.Add(SaveScore);
	}
	else if (CheckIfValid(SaveName, SaveScore))
	{
		if (SavedPlayerNames.Contains(SaveName) )
		{
			
			/*
			for (FSavePlayer SP : SavedPlayers)
			{
				if (SP.PlayerName.Equals(SaveName))
				{
					if (SP.HighScore < SaveScore)
					{
						SP.HighScore = SaveScore;
					}
				}
			}
			*/
			int index = SavedPlayerNames.IndexOfByKey(SaveName);
			if (SavedHighScores[index] < SaveScore)
			{
				SavedHighScores[index] = SaveScore;
				
			}
		}
		else
		{
			SavedPlayerNames.Add(SaveName);
			SavedHighScores.Add(SaveScore);
		}
	}
	else
	{
		if (SaveName.IsEmpty()) GEngine->AddOnScreenDebugMessage(-1, 12.f, FColor::Red, TEXT("Error: Couldnt save ")); 
	}
}

void USavePacGame::LoadGame(int64 HighScore)
{
	
}

bool USavePacGame::CheckIfValid(FString SaveName, int64 SaveScore)
{
	if (SavedPlayerNames.Num() >= 10)
	{
		int index = SavedPlayerNames.IndexOfByKey(SaveName);
		if (SavedHighScores[index] <= SaveScore)
		{
			SavedPlayerNames.Remove(SaveName);
			return true;
		}
		return false;
	}
	return true;
}
