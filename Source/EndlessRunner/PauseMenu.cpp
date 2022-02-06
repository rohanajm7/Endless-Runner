// Fill out your copyright notice in the Description page of Project Settings.


#include "PauseMenu.h"

#include "EndlessRunnerGameMode.h"
#include "Components/Button.h"
#include "Kismet/KismetSystemLibrary.h"

void UPauseMenu::NativeConstruct()
{
	Super::NativeConstruct();
	if(ResumeButton)
	{
		ResumeButton->OnClicked.AddDynamic(this, &UPauseMenu::OnResumeClicked);
	}
	if(RestartButton)
	{
		RestartButton->OnClicked.AddDynamic(this, &UPauseMenu::OnRestartClicked);
	}
}

void UPauseMenu::OnResumeClicked()
{
	Cast<AEndlessRunnerGameMode>(GetWorld()->GetAuthGameMode())->ResumeEndlessRunner();
}

void UPauseMenu::OnRestartClicked()
{
	UWorld* World = GetWorld();
	if(World)
	{
		UKismetSystemLibrary::ExecuteConsoleCommand(World, TEXT("RestartLevel"));
	}
}

