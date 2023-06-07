// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Enemy.generated.h"

class USphereComponent;
class APac;
UCLASS()
class PACPONG_API AEnemy : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEnemy();

	UFUNCTION()
	void OnEnemyOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

	UPROPERTY(EditAnywhere)
	USphereComponent* SphereComponent;

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* MeshComponent;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


private:
	UPROPERTY()
	APawn* PacPawn;

	FVector Direction;
	FVector CurrentTargetLocation;

	FVector UpperBoundPatrolLocation;
	FVector LowerBoundPatrolLocation;

	UPROPERTY(EditAnywhere, meta=(AllowPrivateAccess = true))
	float BoundRadius;

	UPROPERTY(EditAnywhere, meta=(AllowPrivateAccess = true))
	double Speed;

	//bälja 2 random punkter på vertikal axel och sätta de vektorerna
	void SetPatrollingPoints();

	//Gå mellan punkter och byta beroende på om man nått den första eller inte
	void Patrol();

	// Räkna ut en sfär med boundes
	void CalculateBounds();
	
	//kolla om en punkt är inom bounds
	bool IsWithinBounds();

	

	bool bIdle;
	bool bKillable;
	

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
