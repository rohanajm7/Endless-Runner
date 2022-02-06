// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameOver.generated.h"


/**
 * 
 */
UCLASS()
class ENDLESSRUNNER_API UGameOver : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UButton* TryAgainButton;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UButton* MainMenuButton;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* ScoreText;

public:

	virtual void NativeConstruct() override;

	UFUNCTION(BlueprintCallable)
	void InitializeHUD(class AEndlessRunnerGameMode* EndlessRunnerGameMode);

	UFUNCTION(BlueprintCallable)
	void UpdateScoreOnHud(int score);

	UFUNCTION()
	void OnTryAgainClicked();

	UFUNCTION()
	void OnMainMenuClicked();
	
};
