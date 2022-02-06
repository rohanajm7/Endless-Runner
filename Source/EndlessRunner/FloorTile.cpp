// Fill out your copyright notice in the Description page of Project Settings.


#include "FloorTile.h"
#include "Components/ArrowComponent.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Obstacle.h"
#include "EndlessRunnerGameMode.h"
#include "RunnerCharacter.h"

// Sets default values
AFloorTile::AFloorTile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent"));
	SetRootComponent(SceneComponent);

	FloorMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("FloorMesh"));
	FloorMesh->SetupAttachment(SceneComponent);

	AttachPoint = CreateDefaultSubobject<UArrowComponent>(TEXT("AttachPoint"));
	AttachPoint->SetupAttachment(SceneComponent);

	LeftObstacle = CreateDefaultSubobject<UArrowComponent>(TEXT("LeftObstacle"));
	LeftObstacle->SetupAttachment(SceneComponent);

	MiddleObstacle = CreateDefaultSubobject<UArrowComponent>(TEXT("MiddleObstacle"));
	MiddleObstacle->SetupAttachment(SceneComponent);

	RightObstacle = CreateDefaultSubobject<UArrowComponent>(TEXT("RightObstacle"));
	RightObstacle->SetupAttachment(SceneComponent);
	
	FloorTileTrigger = CreateDefaultSubobject<UBoxComponent>(TEXT("FloorTileTrigger"));
	FloorTileTrigger->SetupAttachment(SceneComponent);
}

// Called when the game starts or when spawned
void AFloorTile::BeginPlay()
{
	Super::BeginPlay();

	EndlessRunnerGameMode = Cast<AEndlessRunnerGameMode>(GetWorld()->GetAuthGameMode());
	
	FloorTileTrigger->OnComponentBeginOverlap.AddDynamic(this, &AFloorTile::OnCollision);
	
}

// Called every frame
void AFloorTile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
}

// This function gets triggered when our player collides with the collision box in our tiles
// The major thing that this function does is to spawn new tiles and destroy old ones.
void AFloorTile::OnCollision(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& Hit)
{
	
	ARunnerCharacter* RunnerCharacter = Cast<ARunnerCharacter>(OtherActor);
	if (RunnerCharacter)
	{
		EndlessRunnerGameMode->AddFloorTile();
		
		GetWorldTimerManager().SetTimer(TimerHandle, this, &AFloorTile::DestroyFloorTile, 1.0f, false, 2.0f);
		
	}
}

// Destroys Tiles
void AFloorTile::DestroyFloorTile()
{
	GetWorldTimerManager().ClearTimer(TimerHandle);
	
	this->Destroy();
}

