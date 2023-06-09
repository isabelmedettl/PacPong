// Fill out your copyright notice in the Description page of Project Settings.


#include "PickUpManager.h"

#include "Pac.h"
#include "PickUp.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"


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
			APickUp* PickUp;
			if((x == StartX+2 || x == EndX-3) && (y == StartY+2 || y == EndY-3))
			{
				PickUp = GetWorld()->SpawnActor<APickUp>(PowerUpPickupClass, FVector(x * DistanceBetweenPickUps, y * DistanceBetweenPickUps, SpawnHeight), FRotator::ZeroRotator);
			}
			else
			{
				PickUp = GetWorld()->SpawnActor<APickUp>(BasicPickupClass, FVector(x * DistanceBetweenPickUps, y * DistanceBetweenPickUps, SpawnHeight), FRotator::ZeroRotator);
			}
			if(PickUp)
			{
				BasicPickups.Add(PickUp);
				NumberOfBasicPickUpsLeft++;
				PickUp->Manager = this;
			}
		}
	}
	
}


void APickUpManager::SpeedUpGame()
{
	AActor* Pac = Cast<APac>(UGameplayStatics::GetActorOfClass(GetWorld(), PacClass));
	if (Pac)
	{
		UE_LOG(LogTemp, Warning, TEXT("found pac"));
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
	ResetEvent();
}

