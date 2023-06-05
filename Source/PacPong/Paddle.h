// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Paddle.generated.h"

class UInputMappingContext;
struct FInputActionValue;
class UBoxComponent;
class UInputAction;

UCLASS()
class PACPONG_API APaddle : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	APaddle();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float PaddleSpeed = 5;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UBoxComponent* LeftBoxCollider;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* LeftMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UBoxComponent* RightBoxCollider;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* RightMesh;

	UPROPERTY(EditAnywhere)
	UInputMappingContext* InputMappingContext;
	
	UPROPERTY(EditAnywhere)
	UInputAction* LeftMoveAction;

	UPROPERTY(EditAnywhere)
	UInputAction* RightMoveAction;

	UFUNCTION()
	void LeftMove(const FInputActionValue& Value);

	UFUNCTION()
	void RightMove(const FInputActionValue& Value);

	UFUNCTION()
	void OnCollisionHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};
