// Fill out your copyright notice in the Description page of Project Settings.


#include "HighScoreUserWidget.h"

#include "Pac.h"
#include "Paddle.h"
#include "SavePacGame.h"
#include "Components/TextBlock.h"
#include "Components/WrapBox.h"
#include "Kismet/GameplayStatics.h"

void UHighScoreUserWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	
	NameTextBlocks.Add(PName1);
	NameTextBlocks.Add(PName2);
	NameTextBlocks.Add(PName3);
	NameTextBlocks.Add(PName4);
	NameTextBlocks.Add(PName5);
	NameTextBlocks.Add(PName6);
	NameTextBlocks.Add(PName7);
	NameTextBlocks.Add(PName8);
	NameTextBlocks.Add(PName9);
	NameTextBlocks.Add(PName10);
	ScoreTextBlocks.Add(PScore_1);
	ScoreTextBlocks.Add(PScore_2);
	ScoreTextBlocks.Add(PScore_3);
	ScoreTextBlocks.Add(PScore_4);
	ScoreTextBlocks.Add(PScore_5);
	ScoreTextBlocks.Add(PScore_6);  
	ScoreTextBlocks.Add(PScore_7);  
	ScoreTextBlocks.Add(PScore_8);
	ScoreTextBlocks.Add(PScore_9);
	ScoreTextBlocks.Add(PScore_10);

	for (UTextBlock* TextBlock : NameTextBlocks)
	{
		TextBlock->SetVisibility(ESlateVisibility::Hidden);
	}

	for (UTextBlock* TextBlock : ScoreTextBlocks)           
	{                                                      
		TextBlock->SetVisibility(ESlateVisibility::Hidden);
	}
	
	PlayerPaddle = Cast<APaddle>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	if (PlayerPaddle)
	{
		TArray<AActor*> ActorsToFind;
		if(UWorld* World = GetWorld())
		{
			UGameplayStatics::GetAllActorsOfClass(GetWorld(), APac::StaticClass(), ActorsToFind);
			for (AActor* PacActor: ActorsToFind)
			{
				Pac = Cast<APac>(PacActor);
				if (Pac  && Pac->SavedGame)
				{
					RefreshScoreBoard();
				}   
			}
		}
	}
}

void UHighScoreUserWidget::RefreshScoreBoard()
{
	int32 Counter = 0;
	for (FSavedPlayer SavedPlayer : Pac->SavedPlayers)
	{
		NameTextBlocks[Counter]->SetText(FText::FromString(SavedPlayer.PlayerName));
		ScoreTextBlocks[Counter]->SetText(FText::AsNumber(SavedPlayer.HighScore));
		NameTextBlocks[Counter]->SetVisibility(ESlateVisibility::Visible);
		ScoreTextBlocks[Counter]->SetVisibility(ESlateVisibility::Visible); 
		Counter++;
	}
}
