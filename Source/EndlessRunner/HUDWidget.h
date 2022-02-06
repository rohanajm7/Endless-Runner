// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EndlessRunnerGameMode.h"
#include "Blueprint/UserWidget.h"
#include "HUDWidget.generated.h"

/**
 * 
 */
UCLASS()
class ENDLESSRUNNER_API UHUDWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* CoinCount;

public:
	UFUNCTION(BlueprintCallable)
	void InitializeHUD(AEndlessRunnerGameMode* EndlessRunnerGameMode);

	UFUNCTION(BlueprintCallable)
	void UpdateScoreOnHud(int score);
	
};
