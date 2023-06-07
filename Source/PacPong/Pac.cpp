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
}


// Called when the game starts or when spawned
void APac::BeginPlay()
{
	Super::BeginPlay();

	//MeshComponent->OnComponentBeginOverlap.AddDynamic(this, &APac::OnPacOverlapBegin);
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
	// Get the hit point and surface normal
	/*
	const FVector HitPoint = Hit.ImpactPoint;
	const FVector SurfaceNormal = Hit.ImpactNormal;
	
	// Calculate a location around collision
	FVector AdjustedLocation = HitPoint +  SurfaceNormal * 20.f;

	

	// Projection of DroneToGoal on SurfaceNormal
	const double ProjectionOnSurfNorm = -SurfaceNormal.Dot(MovementComponent->Velocity);

	// reflection vector from hit point
	FVector ReflectionVector = (2 * ProjectionOnSurfNorm * SurfaceNormal * MovementComponent->Velocity.Size() * 10.f - MovementComponent->Velocity);
	ReflectionVector = ReflectionVector.GetSafeNormal() * ReflectionVector.Size(); 
	MovementComponent->Velocity += ReflectionVector;

	AdjustedLocation += ReflectionVector;
	DrawDebugSphere(GetWorld(), AdjustedLocation, 30.f, 30, FColor::Black, false,0.2f);

	
	FVector Normal = FVector::VectorPlaneProject(Normal, MovementComponent->GetPlaneConstraintNormal()).GetSafeNormal();
	const FVector SurfaceNormal = Hit.ImpactNormal;
	//UE_LOG(LogTemp, Warning, TEXT("VelIMP %f, %f, %f "), SurfaceNormal.X,SurfaceNormal.Y, SurfaceNormal.Z);
	const double ProjectionOnSurfNorm = -SurfaceNormal.Dot(MovementComponent->Velocity);
	//FVector ReflectionVector = (2 * ProjectionOnSurfNorm * SurfaceNormal * MovementComponent->Velocity.Size() * 10.f - MovementComponent->Velocity);
	//UE_LOG(LogTemp, Warning, TEXT("Vel %f, %f, %f "), MovementComponent->Velocity.X, MovementComponent->Velocity.Y, MovementComponent->Velocity.Z);
	FVector ReflectionVector = UKismetMathLibrary::GetReflectionVector(UKismetMathLibrary::GetDirectionUnitVector(GetActorLocation(), Hit.Location), Normal);
	ReflectionVector = ReflectionVector.GetSafeNormal() * ReflectionVector.Size();
	MovementComponent->AddInputVector(ReflectionVector);
	*/
	//MeshComponent->AddForce(ReflectionVector);
	float AvoidingOffset = 50.f;;
	
	// Get the hit point and surface normal
	const FVector HitPoint = Hit.ImpactPoint;
	const FVector SurfaceNormal = Hit.ImpactNormal;
	
	// Calculate a location around collision
	FVector AdjustedLocation = HitPoint +  SurfaceNormal * AvoidingOffset;

	// Distance vector between drone and hitpoint aka hypotenusan
	const FVector DroneToGoal = (HitPoint - GetActorLocation());

	// Projection of DroneToGoal on SurfaceNormal
	const double ProjectionOnSurfNorm = -SurfaceNormal.Dot(DroneToGoal);
	

	// reflection vector from hit point
	FVector ReflectionVector = (2 * ProjectionOnSurfNorm * SurfaceNormal * DroneToGoal.Size() - DroneToGoal);
	ReflectionVector = ReflectionVector.GetSafeNormal() * FMath::Clamp(ReflectionVector.Size(), 0, AvoidingOffset); 
	AdjustedLocation += ReflectionVector;
	
	
	FVector MovementDirection = AdjustedLocation -GetActorLocation();
	MovementDirection.Normalize();
	//const float Distance = FVector::Distance(CurrentTargetLocation, GetActorLocation());
	MovementComponent->AddInputVector(MovementDirection);

	//MovementComponent->Velocity += MovementDirection;
	DrawDebugSphere(GetWorld(),AdjustedLocation, 30.f, 30, FColor::Black, false,0.2f);
	
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


