// Fill out your copyright notice in the Description page of Project Settings.


#include "Paddle.h"

#include "Components/BoxComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"


// Sets default values
APaddle::APaddle()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	LeftBoxCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("LeftBoxCollider"));
	LeftBoxCollider->SetupAttachment(RootComponent);

	LeftMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LeftMesh"));
	LeftMesh->SetupAttachment(LeftBoxCollider);

	RightBoxCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("RightBoxCollider"));
	RightBoxCollider->SetupAttachment(RootComponent);

	RightMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RightMesh"));
	RightMesh->SetupAttachment(RightBoxCollider);
}

// Called when the game starts or when spawned
void APaddle::BeginPlay()
{
	Super::BeginPlay();

	LeftBoxCollider->OnComponentHit.AddDynamic(this, &APaddle::OnCollisionHit);
	RightBoxCollider->OnComponentHit.AddDynamic(this, &APaddle::OnCollisionHit);

	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(InputMappingContext, 0);
		}
	}
}

void APaddle::OnCollisionHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	FVector NormalImpulse, const FHitResult& Hit)
{
	UE_LOG(LogTemp, Warning, TEXT("HIT"));
}

// Called every frame
void APaddle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void APaddle::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(LeftMoveAction, ETriggerEvent::Triggered, this, &APaddle::LeftMove);
		EnhancedInputComponent->BindAction(RightMoveAction, ETriggerEvent::Triggered, this, &APaddle::RightMove);
	}
}

void APaddle::LeftMove(const FInputActionValue& Value)
{
	float Movement = Value.Get<float>() * PaddleSpeed;
	if(Movement)
	{
		LeftBoxCollider->MoveComponent(FVector(0, Movement, 0), FQuat::Identity,true);
	}
}

void APaddle::RightMove(const FInputActionValue& Value)
{
	float Movement = Value.Get<float>() * PaddleSpeed;
	if(Movement)
	{
		RightBoxCollider->MoveComponent(FVector(0, Movement, 0), FQuat::Identity,true);
	}
}