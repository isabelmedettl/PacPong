// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy.h"

#include "Pac.h"
#include "Components/SphereComponent.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
AEnemy::AEnemy()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	RootComponent = MeshComponent;
	
	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	SphereComponent->SetupAttachment(RootComponent);

}

void AEnemy::OnEnemyOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	PacPawn = Cast<APac>(OtherActor);
	if (!PacPawn) return;
	if (bKillable)
	{
		CurrentHealth = 0;
		CheckHealth();
	}
	else
	{
		PacPawn->TookDamage(Damage);  
	}
}

// Called when the game starts or when spawned
void AEnemy::BeginPlay()
{
	Super::BeginPlay();
	
	UpperBoundPatrolLocation = GetActorLocation();
	SetPatrollingPoints();
	CurrentTargetLocation = LowerBoundPatrolLocation;
	
	CurrentHealth = InitialHealth;

	bKillable = false;
}

void AEnemy::SetPatrollingPoints()
{
	LowerBoundPatrolLocation.Y = UpperBoundPatrolLocation.Y + BoundRadius;
	LowerBoundPatrolLocation.X = UpperBoundPatrolLocation.X;
	LowerBoundPatrolLocation.Z = UpperBoundPatrolLocation.Z;
}

void AEnemy::CheckHealth()
{
	if (CurrentHealth<=0)
	{
		DoDeath();
	}
}

void AEnemy::Patrol()
{
	if (CurrentTargetLocation.Y <= LowerBoundPatrolLocation.Y && (FVector::Distance(LowerBoundPatrolLocation, GetActorLocation()) <= 3.f ))
	{
		CurrentTargetLocation = UpperBoundPatrolLocation;
	}
	if (CurrentTargetLocation.Y >= UpperBoundPatrolLocation.Y && FVector::Distance(UpperBoundPatrolLocation, GetActorLocation()) <= 3.f )
	{
		CurrentTargetLocation = LowerBoundPatrolLocation;
	}
}



void AEnemy::DoDeath()
{
	OnDeathEvent();
	//GetWorld()->GetGameState();
	//Destroy();
}

// Called every frame
void AEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	Patrol();

	//const FRotator NewRotation = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), CurrentTargetLocation);
	//SetActorRotation(FRotator(0, NewRotation.Yaw -90, 0));
	
	Direction = CurrentTargetLocation - GetActorLocation();
	Direction.Normalize();

	const float MoveDistance = Speed * DeltaTime;;
	const FVector NewLocation = GetActorLocation() + Direction * MoveDistance;
	SetActorLocation(NewLocation);
}

