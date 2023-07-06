// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HighScoreUserWidget.generated.h"

class USavePacGame;
class UButton;
class UTextBlock;
class UEditableText;
class APaddle;
class APac;
class UWrapBox;
/**
 * 
 */


UCLASS()
class PACPONG_API UHighScoreUserWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	//UPROPERTY(meta = (BindWidget))
	//UWrapBox* HighScorePanel;
	
	UPROPERTY(meta = (BindWidget))
	UTextBlock* PName1;
	
	UPROPERTY(meta = (BindWidget))
	UTextBlock* PName2;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* PName3;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* PName4;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* PName5;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* PName6;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* PName7;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* PName8;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* PName9;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* PName10;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* PScore_1;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* PScore_2;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* PScore_3;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* PScore_4;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* PScore_5;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* PScore_6;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* PScore_7;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* PScore_8;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* PScore_9;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* PScore_10;

	UPROPERTY(VisibleAnywhere)
	APaddle* PlayerPaddle;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	APac* Pac;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TArray<UTextBlock*> NameTextBlocks = TArray<UTextBlock*>();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TArray<UTextBlock*> ScoreTextBlocks = TArray<UTextBlock*>();
	

	UPROPERTY(VisibleAnywhere)
	USavePacGame* SavedGame;

	
protected:
	virtual void NativeOnInitialized() override;

	UFUNCTION(BlueprintCallable)
	void UpdateScoreBoard();

};
