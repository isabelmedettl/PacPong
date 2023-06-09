// Fill out your copyright notice in the Description page of Project Settings.


#include "Pac.h"

#include "Enemy.h"
#include "SavePacGame.h"
#include "Components/SphereComponent.h"
#include "EnvironmentQuery/EnvQueryTypes.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "GameFramework/SaveGame.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetSystemLibrary.h"


// Sets default values
APac::APac()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	RootComponent = MeshComponent;
	
	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	SphereComponent->SetupAttachment(RootComponent);
	
	MovementComponent = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("Movement"));
}


void APac::AddScore(int64 ScoreToAdd)
{
	CurrentScore = ScoreToAdd;
}

void APac::StartGame_Implementation()
{
}

// Called when the game starts or when spawned
void APac::BeginPlay()
{
	Super::BeginPlay();

	MeshComponent->OnComponentBeginOverlap.AddDynamic(this, &APac::OnPacOverlapBegin);

	Save();
}

void APac::DoDeath()
{
	OnDeathEvent();
	MeshComponent->SetSimulatePhysics(false);
	MovementComponent->Deactivate();
}

// Called every frame
void APac::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


void APac::OnPacOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{

	AEnemy* Enemy = Cast<AEnemy>(OtherActor);
	if (!Enemy) return;
	if (Enemy->bKillable)
	{
		CurrentHealth -= Enemy->Damage;
		if (CurrentHealth <= 0) DoDeath();
	}
}


void APac::TookDamage(float Damage)
{
	CurrentHealth -= Damage;
	if (CurrentHealth <= 0) DoDeath();
}

void APac::Save()
{
	if (UGameplayStatics::DoesSaveGameExist("deafult", 0))
	{
		SavedGame = Cast<USavePacGame>(UGameplayStatics::LoadGameFromSlot("deafult", 0));
		if (!SavedGame)
		{
			GEngine->AddOnScreenDebugMessage(-1, 12.f, FColor::Red, TEXT("No save game") );
		}
	}
	else if (!UGameplayStatics::DoesSaveGameExist("deafult", 0))
	{
		SavedGame= Cast<USavePacGame>(UGameplayStatics::CreateSaveGameObject(USavePacGame::StaticClass()));
		if( IsValid(SavedGame) )
		{
			UGameplayStatics::SaveGameToSlot(SavedGame, TEXT("deafult"), 0);
		}
	}
	else { if( GEngine ) GEngine->AddOnScreenDebugMessage(-1, 12.f, FColor::Red, TEXT("Error: Unable to save...")); }
}


void APac::SavePlayer()
{
	if (SavedGame)
	{
		SavedGame->SaveGame(PlayerName, CurrentScore);
		UGameplayStatics::SaveGameToSlot(SavedGame, TEXT("deafult"), 0);
	}
}



