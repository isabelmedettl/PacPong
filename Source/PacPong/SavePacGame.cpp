// Fill out your copyright notice in the Description page of Project Settings.


#include "SavePacGame.h"

#include "Kismet/GameplayStatics.h"

void USavePacGame::SaveGame(FString SaveName, int64 SaveScore)
{
	if (SaveName.IsEmpty()) GEngine->AddOnScreenDebugMessage(-1, 12.f, FColor::Red, TEXT("Error: No name")); 

	
}

void USavePacGame::LoadGame(int64 HighScore)
{
	
}

