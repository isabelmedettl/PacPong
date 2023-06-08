// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PickUpManager.generated.h"

class APac;
class UBoxComponent;
class APickUp;

UCLASS()
class PACPONG_API APickUpManager : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	APickUpManager();

	UPROPERTY(EditAnywhere)
	UBoxComponent* ManagementZone;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int NumberOfBasicPickUpsLeft = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int NumberOfResets = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int DistanceBetweenPickUps = 90;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int RowsOfPickUps = 11;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int ColumnsOfPickUps = 19;

	UPROPERTY(EditAnywhere)
	int SpawnHeight = 45;

	UPROPERTY(EditAnywhere)
	TSubclassOf<APickUp> BasicPickupClass;

	UPROPERTY(EditAnywhere)
	TSubclassOf<APickUp> PowerUpPickupClass;

	UPROPERTY(EditAnywhere)
	TSubclassOf<APac> PacClass;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	TArray<APickUp*> BasicPickups = TArray<APickUp*>();

	void SpeedUpGame();

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	void ResetPickUps();

	UFUNCTION(BlueprintImplementableEvent)
	void ResetEvent();
};
