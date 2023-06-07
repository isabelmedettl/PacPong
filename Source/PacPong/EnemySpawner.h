// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EnemySpawner.generated.h"

UCLASS()
class PACPONG_API AEnemySpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEnemySpawner();

	// metod för att spawna ett x antal fiender.
	// se till att inga av fienders punkter är innanför en annan fiendes bounds

	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// box som kollar hela banan

	//spawna en fiende nånstans

	
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
