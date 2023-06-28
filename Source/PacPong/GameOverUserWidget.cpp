// Fill out your copyright notice in the Description page of Project Settings.


#include "GameOverUserWidget.h"

#include "Pac.h"
#include "Paddle.h"
#include "SavePacGame.h"
#include "Components/Button.h"
#include "Components/EditableText.h"
#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"

void UGameOverUserWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	HighScoreText->SetVisibility(ESlateVisibility::Hidden);
	EnterButtonText->SetVisibility(ESlateVisibility::Hidden);
	EnterButton->SetVisibility(ESlateVisibility::Hidden);
	EditableText->SetVisibility(ESlateVisibility::Hidden);

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
				if (Pac  && Pac->SavedGame /* && Pac->SavedGame->CheckIfValidScore(Pac->HighScore)*/)
				{
					RefreshHighScore();
				}   
			}
			
		}
	}
}

void UGameOverUserWidget::RefreshHighScore()
{
	// skapa de widgest som behövs för att få namnet
	//HighScoreText = NewObject<UTextBlock>(this, UTextBlock::StaticClass());
	if (HighScoreText)
	{
		HighScoreText->SetVisibility(ESlateVisibility::Visible);
		HighScoreText->SetText(FText::FromString("You've earned a place on the high score board!"));
	}

	if (EnterButtonText)
	{
		EnterButtonText->SetVisibility(ESlateVisibility::Visible);
		EnterButtonText->SetText(FText::FromString("Save name"));
	}
	EnterButton->SetVisibility(ESlateVisibility::Visible);
	EditableText->SetVisibility(ESlateVisibility::Visible);
	
	// Spara namnet i fältet och highscore till det namnet i save
}
