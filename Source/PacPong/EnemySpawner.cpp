// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemySpawner.h"

#include "Components/BoxComponent.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
AEnemySpawner::AEnemySpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpawnBox = CreateDefaultSubobject<UBoxComponent>(TEXT("SphereComponent"));
	SpawnBox->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AEnemySpawner::BeginPlay()
{
	Super::BeginPlay();

	
}

void AEnemySpawner::SpawnEnemies()
{
	if (EnemiesToSpawn == 0) return;
	for (int i = 0; i < EnemiesToSpawn; i++)
	{
		
	}
}

FVector AEnemySpawner::CalculateSpawnLocation()
{
	FVector Location = UKismetMathLibrary::RandomUnitVector();
	return Location;
}

bool AEnemySpawner::IsToCloseToPreviousSpawnPoint(FVector LocationToCheck)
{
	return false;
}

// Called every frame
void AEnemySpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

