// Fill out your copyright notice in the Description page of Project Settings.


#include "PickUpManager.h"
#include "PickUp.h"
#include "Components/BoxComponent.h"


// Sets default values
APickUpManager::APickUpManager()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	ManagementZone = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
	RootComponent = ManagementZone;
	NumberOfResets++;
}

// Called when the game starts or when spawned
void APickUpManager::BeginPlay()
{
	Super::BeginPlay();

	int StartX = -(ColumnsOfPickUps - 1)/2;
	int EndX = (ColumnsOfPickUps + 1)/2;
	int StartY = -(RowsOfPickUps - 1)/2;
	int EndY = (RowsOfPickUps + 1)/2;

	for(int x = StartX; x < EndX; x++)
	{
		for(int y = StartY; y < EndY; y++)
		{
			APickUp* PickUp = GetWorld()->SpawnActor<APickUp>(BasicPickupClass, FVector(x * DistanceBetweenPickUps, y * DistanceBetweenPickUps, SpawnHeight), FRotator::ZeroRotator);
			if(PickUp)
			{
				BasicPickups.Add(PickUp);
				NumberOfBasicPickUpsLeft++;
				PickUp->Manager = this;
			}
		}
	}
	
}

// Called every frame
void APickUpManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void APickUpManager::ResetPickUps()
{
	for (APickUp* PickUp : BasicPickups)
	{
		PickUp->MeshComponent->SetCollisionProfileName(TEXT("OverlapAllDynamic"));
		PickUp->MeshComponent->ToggleVisibility();
	}
}

