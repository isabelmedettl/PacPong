// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameOverUserWidget.generated.h"



/**
 * 
 */

class UButton;
class UTextBlock;
class UEditableText;
class APaddle;
class APac;

UCLASS()
class PACPONG_API UGameOverUserWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	UPROPERTY(meta = (BindWidget))
	UTextBlock* HighScoreText;
	
	UPROPERTY(meta = (BindWidget))
	UTextBlock* EnterButtonText;

	UPROPERTY(meta = (BindWidget))
	UButton* EnterButton;

	UPROPERTY(meta = (BindWidget))
	UEditableText* EditableText;

	UPROPERTY(VisibleAnywhere)
	APaddle* PlayerPaddle;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	APac* Pac;

protected:
	virtual void NativeOnInitialized() override;

	void RefreshHighScore();
};
