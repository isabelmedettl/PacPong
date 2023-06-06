// Fill out your copyright notice in the Description page of Project Settings.


#include "Pac.h"

#include "Components/SphereComponent.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"


// Sets default values
APac::APac()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	RootComponent = MeshComponent;
	
	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	SphereComponent->SetupAttachment(RootComponent);
	
	MovementComponent = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("Movement"));
	//MovementComponent->bShouldBounce = true;
}


// Called when the game starts or when spawned
void APac::BeginPlay()
{
	Super::BeginPlay();

	MeshComponent->OnComponentHit.AddDynamic(this, &APac::OnPacHit);
	
}

// Called every frame
void APac::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void APac::OnPacHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	FVector NormalImpulse, const FHitResult& Hit)
{
	UE_LOG(LogTemp, Warning, TEXT("Pac HIT wall"));
	const FVector SurfaceNormal = Hit.ImpactNormal;
	const FVector DistanceToGoal = (Hit.ImpactPoint - GetActorLocation());

	const FVector DirectionVector = UKismetMathLibrary::GetDirectionUnitVector(GetActorLocation(), Hit.Location);
	const double ProjectionOnSurfNorm = -SurfaceNormal.Dot(DistanceToGoal);
		

	// reflection vector from hit point
	//FVector ReflectionVector = (2 * ProjectionOnSurfNorm * SurfaceNormal * DistanceToGoal .Size() - DistanceToGoal);
	//ReflectionVector = ReflectionVector.GetSafeNormal() * ReflectionVector.Size();
	FVector ReflectionVector = FMath::GetReflectionVector(DirectionVector, Hit.Normal) + GetActorLocation();
	//PacMovement->AddInputVector(ReflectionVector);
	//PacMovement->Velocity += ReflectionVector;
}

void APac::OnPacOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Warning, TEXT("Pac overlap wall"));

	if (SweepResult.bBlockingHit)
	{
		//const FVector HitPoint = SweepHitResult.ImpactPoint;
	
	
		// Calculate a location around collision
		//FVector AdjustedLocation = HitPoint +  SurfaceNormal * AvoidingOffset;
		const FVector SurfaceNormal = SweepResult.ImpactNormal;
		const FVector DistanceToGoal = (SweepResult.ImpactPoint - GetActorLocation());
		
		const double ProjectionOnSurfNorm = -SurfaceNormal.Dot(DistanceToGoal);
		

		// reflection vector from hit point
		FVector ReflectionVector = (2 * ProjectionOnSurfNorm * SurfaceNormal * DistanceToGoal .Size() - DistanceToGoal);
		ReflectionVector = ReflectionVector.GetSafeNormal() * ReflectionVector.Size();
		//PacMovement->AddInputVector(ReflectionVector);
	}
}


