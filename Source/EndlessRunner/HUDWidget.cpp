// Fill out your copyright notice in the Description page of Project Settings.


#include "HUDWidget.h"

#include "Components/TextBlock.h"

void UHUDWidget::InitializeHUD(AEndlessRunnerGameMode* EndlessRunnerGameMode)
{
	if(EndlessRunnerGameMode)
	{
		CoinCount->SetText(FText::AsNumber(0));
		EndlessRunnerGameMode->OnScoreChanged.AddDynamic(this, &UHUDWidget::UpdateScoreOnHud);
	}
}

void UHUDWidget::UpdateScoreOnHud(int score)
{
	CoinCount->SetText(FText::AsNumber(score));
}
