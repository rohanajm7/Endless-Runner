// Fill out your copyright notice in the Description page of Project Settings.


#include "RunnerCharacter.h"

#include "EndlessRunnerGameMode.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
ARunnerCharacter::ARunnerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Created Camera boom object
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	/*CameraBoom->bUsePawnControlRotation = true;*/  //Since we need our camera boom to look in the direction of pawn all the time
	CameraBoom->SetupAttachment(GetRootComponent());

	//Created Camera object and attached it to boom
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(CameraBoom);

	CharacterSpeed = 5000.0f;

}

// Called when the game starts or when spawned
void ARunnerCharacter::BeginPlay()
{
	Super::BeginPlay();
	PlayerSpawnLocation = this->GetActorLocation();
	EndlessRunnerGameMode = Cast<AEndlessRunnerGameMode>(GetWorld()->GetAuthGameMode());
}

// Called every frame
void ARunnerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// GetActorForwardVector gets the forward vector from the character in world space(magnitude = 1)
	FVector Forward = GetActorForwardVector();

	// Adds Movement along the given direction. The scaled value is set as 1.0f by default which works here.
	AddMovementInput(Forward * CharacterSpeed * DeltaTime);
}

// Called to bind functionality to input
void ARunnerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAction("Jump", EInputEvent::IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", EInputEvent::IE_Released, this, &ACharacter::StopJumping);
	PlayerInputComponent->BindAction("MoveLeft", EInputEvent::IE_Pressed, this, &ARunnerCharacter::MoveLeft);
	PlayerInputComponent->BindAction("MoveRight", EInputEvent::IE_Pressed, this, &ARunnerCharacter::MoveRight);
	PlayerInputComponent->BindAction("PauseGame", EInputEvent::IE_Pressed, this, &ARunnerCharacter::PauseGame);
}

// This function is responsible to move the player in left direction
void ARunnerCharacter::MoveLeft()
{
	// We take the relative location of the player, sub 300 units, clamp the location, set the relative location
	FVector CurrentLocation = GetCapsuleComponent()->GetRelativeLocation();
	PlayerSpawnLocation.X  = FMath::Lerp(PlayerSpawnLocation.X, PlayerSpawnLocation.X - 300.0f, 1);
	PlayerSpawnLocation.X = FMath::Clamp(PlayerSpawnLocation.X, ClampMin, ClampMax);
	CurrentLocation.X = PlayerSpawnLocation.X;
	SetActorRelativeLocation(CurrentLocation);
}

// This function is responsible to move the player in right direction
void ARunnerCharacter::MoveRight()
{
	// We take the relative location of the player, add 300 units, clamp the location, set the relative location
	FVector CurrentLocation = GetCapsuleComponent()->GetRelativeLocation();
	PlayerSpawnLocation.X  = FMath::Lerp(PlayerSpawnLocation.X, PlayerSpawnLocation.X + 300.0f, 1);
	PlayerSpawnLocation.X = FMath::Clamp(PlayerSpawnLocation.X, ClampMin, ClampMax);
	CurrentLocation.X = PlayerSpawnLocation.X;
	SetActorRelativeLocation(CurrentLocation);
}

void ARunnerCharacter::Death()
{
	GetMesh()->SetSimulatePhysics(true);
	GetCharacterMovement()->DisableMovement();
	GetWorldTimerManager().SetTimer(Handle, this, &ARunnerCharacter::RunnerCharacter_GameOver, 1.0f, false, 2.0f);
	
}

void ARunnerCharacter::PauseGame()
{
	EndlessRunnerGameMode->PauseEndlessRunner();
}

void ARunnerCharacter::RunnerCharacter_GameOver()
{
	GetWorldTimerManager().ClearTimer(Handle);
	EndlessRunnerGameMode->GameOver();
}

