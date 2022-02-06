// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "EndlessRunnerGameMode.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnScoreChanged, int, ScoreCount);

UCLASS()
class AEndlessRunnerGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AEndlessRunnerGameMode();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MasterTile")
	TSubclassOf<class AFloorTile> FloorTile_BP;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "SpawnTransform")
	FVector SpawnLocation = FVector(0.0f, 0.0f, -100.0f);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "SpawnTransform")
	FRotator SpawnRotation = FRotator(0.0f);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Obstacles")
	TArray<TSubclassOf<class AObstacle>> Obstacles;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PickupItems")
	TSubclassOf<class APickup> PickupItem;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Display")
	TSubclassOf<class UUserWidget> BP_HUD;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Display")
	TSubclassOf<class UUserWidget> BP_PauseMenuHUD;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Display")
	TSubclassOf<class UUserWidget> BP_GameOverHUD;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Display")
	TSubclassOf<class UUserWidget> BP_MainMenuHUD;
	
	UPROPERTY(VisibleInstanceOnly)
	class UHUDWidget* GameHUD;

	UPROPERTY(VisibleInstanceOnly)
	class UPauseMenu* PauseMenuHUD;

	UPROPERTY(VisibleInstanceOnly)
	class UGameOver* GameOverHUD;

	UPROPERTY(VisibleInstanceOnly)
	class UGameOver* MainMenuHUD;

	UPROPERTY()
	AObstacle* CurrentObstacle;

	UPROPERTY()
	int TotalObstacles;

	UPROPERTY()
	int score = 0;

	UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = "Delegates/Events")
	FOnScoreChanged OnScoreChanged;

	UPROPERTY()
	APlayerController* PlayerController;
	
	virtual void BeginPlay() override;

	UFUNCTION()
	void AddFloorTile();

	UFUNCTION()
	void SpawnObstacles(AFloorTile* floortile);

	UFUNCTION()
	void SpawnDecider(int LaneDecider, int randomObstacleNumber, AFloorTile* floortile, int LaneNumber);

	UFUNCTION()
	void ScoreUpdate();

	UFUNCTION()
	void PauseEndlessRunner();

	UFUNCTION()
	void ResumeEndlessRunner();
	
	UFUNCTION()
	void GameOver();
	
};



