// Fill out your copyright notice in the Description page of Project Settings.


#include "Pickup.h"
#include "RunnerCharacter.h"
#include "EndlessRunnerGameMode.h"
#include "Components/BoxComponent.h"

// Sets default values
APickup::APickup()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent"));
	SetRootComponent(SceneComponent);

	OuterCylinder = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("OuterCylinder"));
	OuterCylinder->SetupAttachment(SceneComponent);

	InnerMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("InnerMesh"));
	InnerMesh->SetupAttachment(OuterCylinder);

	PickupCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("PickupCollider"));
	PickupCollider->SetupAttachment(SceneComponent);
	
}

// Called when the game starts or when spawned
void APickup::BeginPlay()
{
	Super::BeginPlay();

	EndlessRunnerGameMode = Cast<AEndlessRunnerGameMode>(GetWorld()->GetAuthGameMode());
	PickupCollider->OnComponentBeginOverlap.AddDynamic(this, &APickup::OnCollision);
	
}

// Called every frame
void APickup::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AddActorLocalRotation(FRotator(0.0f, rotationSpeed*DeltaTime, 0.0f));
	
}

void APickup::OnCollision(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& Hit)
{
	ARunnerCharacter* Character = Cast<ARunnerCharacter>(OtherActor);
	if(Character)
	{
		EndlessRunnerGameMode->ScoreUpdate();
		DestroyPickup();
	}
}

void APickup::DestroyPickup()
{
	this->Destroy();
}

