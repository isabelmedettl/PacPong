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

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* HighScoreText;
	
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* EnterButtonText;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UButton* EnterButton;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UEditableText* EditableText;

	UPROPERTY(VisibleAnywhere)
	APaddle* PlayerPaddle;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	APac* Pac;

protected:
	virtual void NativeOnInitialized() override;

	void RefreshHighScore();

	UFUNCTION(BlueprintGetter)
	UTextBlock* GetHighScoreText() const {return HighScoreText; }

	UFUNCTION(BlueprintGetter)
	UTextBlock* GetEnterButtonText() const {return EnterButtonText;}

	UFUNCTION(BlueprintGetter)
	UButton* GetEnterButton() const {return EnterButton;}

	UFUNCTION(BlueprintGetter)
	UEditableText* GetEditableText() const {return EditableText;}
};
