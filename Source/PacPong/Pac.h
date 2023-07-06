// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Pac.generated.h"

class UFloatingPawnMovement;
class USphereComponent;
class USavePacGame;
struct FSavedPlayer;

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

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bPowered = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int64 HighScore;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int64 CurrentScore;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Basic)
	FString PlayerName = "Isabel";

	UFUNCTION()
	void OnPacOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

	UFUNCTION(BlueprintImplementableEvent)
	void OnDeathEvent();

	UFUNCTION(BlueprintImplementableEvent)
	void OnDamage();

	//UFUNCTION(BlueprintCallable)
	void TookDamage(float Damage);

	UFUNCTION(BlueprintCallable)
	void Save();

	//UFUNCTION(BlueprintCallable)
	//void Load();

	UFUNCTION(BlueprintCallable)
	void SavePlayer();
	
	UPROPERTY(VisibleAnywhere)
	USavePacGame* SavedGame;

	UPROPERTY(VisibleAnywhere)
	TArray<FSavedPlayer> SavedPlayers = TArray<FSavedPlayer>();

	UFUNCTION(BlueprintCallable)
	void AddScore(int64 ScoreToAdd);
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void StartGame();

	
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UFloatingPawnMovement* MovementComponent;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<USavePacGame> SaveGameClass;

private:
	UPROPERTY(EditAnywhere, meta=(AllowPrivateAccess = true))
	int32 InitialHealth;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(AllowPrivateAccess = true))
	int32 CurrentHealth;

	UFUNCTION(BlueprintCallable, meta=(AllowPrivateAccess = true))
	void DoDeath();
public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};


