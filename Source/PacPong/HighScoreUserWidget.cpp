// Fill out your copyright notice in the Description page of Project Settings.


#include "HighScoreUserWidget.h"

// Fill out your copyright notice in the Description page of Project Settings.


#include "HighScoreUserWidget.h"

#include "Pac.h"
#include "PacGameInstance.h"
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

	UpdateScoreBoard();
}


void UHighScoreUserWidget::UpdateScoreBoard()
{
	UPacGameInstance* GameInstance = Cast<UPacGameInstance>(GetGameInstance());
	if (GameInstance && GameInstance->SavedGame)
	{
		int32 Counter = 0;
		
		for (FSavedPlayer SavedPlayer : GameInstance->SavedGame->SavedPlayers)
		{
			NameTextBlocks[Counter]->SetVisibility(ESlateVisibility::Visible);
			ScoreTextBlocks[Counter]->SetVisibility(ESlateVisibility::Visible); 
			NameTextBlocks[Counter]->SetText(FText::FromString(SavedPlayer.PlayerName));
			ScoreTextBlocks[Counter]->SetText(FText::AsNumber(SavedPlayer.HighScore));
			Counter++;
		}
	}
}
