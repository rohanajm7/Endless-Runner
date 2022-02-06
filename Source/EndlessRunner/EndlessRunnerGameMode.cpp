// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "EndlessRunnerGameMode.h"
#include "FloorTile.h"
#include "GameOver.h"
#include "Obstacle.h"
#include "Pickup.h"
#include "HUDWidget.h"
#include "PauseMenu.h"
#include "RunnerCharacter.h"
#include "Blueprint/UserWidget.h"
#include "Components/ArrowComponent.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"

AEndlessRunnerGameMode::AEndlessRunnerGameMode()
{
	
}

void AEndlessRunnerGameMode::BeginPlay()
{
	PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);

	//HUD widget for score display
	GameHUD = Cast<UHUDWidget>(CreateWidget(GetWorld(), BP_HUD));
	check(GameHUD);
	GameHUD->InitializeHUD(this);
	GameHUD->AddToViewport();


	//Creates initial floor tiles
	for(int i = 0; i <= 10; i++)
	{	
		AddFloorTile();	
	}

	//Pause menu HUD
	PauseMenuHUD = Cast<UPauseMenu>(CreateWidget(GetWorld(), BP_PauseMenuHUD));
	check(PauseMenuHUD);

	//GameOverHUD
	GameOverHUD = Cast<UGameOver>(CreateWidget(GetWorld(), BP_GameOverHUD));
	check(GameOverHUD);
	GameOverHUD->InitializeHUD(this);
}

void AEndlessRunnerGameMode::AddFloorTile()
{
	FActorSpawnParameters SpawnParameters;
	
	AFloorTile* Tile = Cast<AFloorTile>(GetWorld()->SpawnActor(FloorTile_BP, &SpawnLocation, &SpawnRotation, SpawnParameters));

	if(Tile)
	{
		SpawnLocation = Tile->AttachPoint->GetComponentLocation();
		if(&Obstacles)
		{
			SpawnObstacles(Tile);
		}
		
	}
	
}

void AEndlessRunnerGameMode::SpawnObstacles(AFloorTile* floortile)
{
	int randomObstacleNumber = FMath::RandRange(0, 2);
	int LeftLaneDecider = FMath::RandRange(0, 1);
	int MiddleLaneDecider = FMath::RandRange(0, 1);
	int RightLaneDecider = FMath::RandRange(0, 1);

	SpawnDecider(LeftLaneDecider, randomObstacleNumber, floortile, 0);
	SpawnDecider(MiddleLaneDecider, randomObstacleNumber, floortile, 1);
	SpawnDecider(RightLaneDecider, randomObstacleNumber, floortile, 2);

	
}

//this decides whether to spawn a coin or an obstacle
void AEndlessRunnerGameMode::SpawnDecider(int LaneDecider, int randomObstacleNumber, AFloorTile* floortile, int LaneNumber)
{
	FActorSpawnParameters SpawnParameters;
	const FVector Locations[3] = {floortile->LeftObstacle->GetComponentLocation(),
		floortile->MiddleObstacle->GetComponentLocation(), floortile->RightObstacle->GetComponentLocation()};
	
	if(LaneDecider == 1)
	{
		CurrentObstacle = Cast<AObstacle>(GetWorld()->SpawnActor(Obstacles[randomObstacleNumber],
			&Locations[LaneNumber], &SpawnRotation, SpawnParameters));
	}else
	{
		APickup* Pickup = Cast<APickup>(GetWorld()->SpawnActor(PickupItem,
			&Locations[LaneNumber], &SpawnRotation, SpawnParameters));
	}
	
}

//scoring system
void AEndlessRunnerGameMode::ScoreUpdate()
{
	score++;
	OnScoreChanged.Broadcast(score);
}

void AEndlessRunnerGameMode::PauseEndlessRunner()
{
	PauseMenuHUD->AddToViewport();
	if (PlayerController)
	{
		PlayerController->bShowMouseCursor = true;
		PlayerController->bEnableClickEvents = true;
		PlayerController->bEnableMouseOverEvents = true;
		PlayerController->SetPause(true);
	}
}

void AEndlessRunnerGameMode::ResumeEndlessRunner()
{
	if (PlayerController)
	{
		PlayerController->bShowMouseCursor = false;
		PlayerController->bEnableClickEvents = false;	
		PlayerController->bEnableMouseOverEvents = false;
		PlayerController->SetPause(false);
	}
	PauseMenuHUD->RemoveFromParent();
}

void AEndlessRunnerGameMode::GameOver()
{
	if (PlayerController)
	{	
		PlayerController->bShowMouseCursor = true;
		PlayerController->bEnableClickEvents = true;
		PlayerController->bEnableMouseOverEvents = true;
		PlayerController->SetPause(true);
	}
	if(GameOverHUD)
	{
		GameOverHUD->AddToViewport();
		OnScoreChanged.Broadcast(score);
	}
}

