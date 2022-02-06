// Fill out your copyright notice in the Description page of Project Settings.


#include "GameOver.h"

#include "EndlessRunnerGameMode.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"

void UGameOver::NativeConstruct()
{
	Super::NativeConstruct();
	if (TryAgainButton)
	{
		TryAgainButton->OnClicked.AddDynamic(this, &UGameOver::OnTryAgainClicked);
	}
	if (MainMenuButton)
	{
		MainMenuButton->OnClicked.AddDynamic(this, &UGameOver::OnMainMenuClicked);
	}
	
}

void UGameOver::InitializeHUD(AEndlessRunnerGameMode* EndlessRunnerGameMode)
{
	EndlessRunnerGameMode->OnScoreChanged.AddDynamic(this, &UGameOver::UpdateScoreOnHud);
}

void UGameOver::UpdateScoreOnHud(int score)
{
	ScoreText->SetText(FText::AsNumber(score));
}

void UGameOver::OnTryAgainClicked()
{
	UWorld* World = GetWorld();
	if(World)
	{
		UKismetSystemLibrary::ExecuteConsoleCommand(World, TEXT("RestartLevel"));
	}
}

void UGameOver::OnMainMenuClicked()
{
	UGameplayStatics::OpenLevel(GetWorld(), TEXT("MainMenuLevel"));
}
