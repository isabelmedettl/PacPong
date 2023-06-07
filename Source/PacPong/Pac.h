// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Pac.generated.h"


class UFloatingPawnMovement;
class USphereComponent;

UCLASS()
class PACPONG_API APac : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	APac();

	UPROPERTY(EditAnywhere)
	USphereComponent* SphereComponent;

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* MeshComponent;

	UFUNCTION()
	void OnPacHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	UFUNCTION()
	void OnPacOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	//UProjectileMovementComponent* MovementComponent;
	UFloatingPawnMovement* MovementComponent;
	//UPawnMovementComponent* MovementComponent;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
