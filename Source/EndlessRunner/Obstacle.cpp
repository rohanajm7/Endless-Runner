// Fill out your copyright notice in the Description page of Project Settings.


#include "Obstacle.h"
#include "FloorTile.h"
#include "RunnerCharacter.h"
#include "Components/BoxComponent.h"

// Sets default values
AObstacle::AObstacle()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent"));
	SetRootComponent(SceneComponent);

	ObstacleCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("ObstacleCollider"));
	ObstacleCollider->SetupAttachment(SceneComponent);
	
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMesh->SetupAttachment(SceneComponent);

}

// Called when the game starts or when spawned
void AObstacle::BeginPlay()
{
	Super::BeginPlay();
	SetLifeSpan(50);

	ObstacleCollider->OnComponentBeginOverlap.AddDynamic(this, &AObstacle::OnCollision);
}

// Called every frame
void AObstacle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
}

void AObstacle::OnCollision(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& Hit)
{
	ARunnerCharacter* Character = Cast<ARunnerCharacter>(OtherActor);
	if (Character)
	{
		Character->Death();
	}
}

