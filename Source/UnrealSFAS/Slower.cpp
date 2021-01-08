// Fill out your copyright notice in the Description page of Project Settings.


#include "Slower.h"

// Sets default values
ASlower::ASlower()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	movementSpeed = 500.0f;

	mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	mesh->SetupAttachment(RootComponent);
	mesh->SetSimulatePhysics(true);

	projectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));
	projectileMovement->MaxSpeed = movementSpeed;
	projectileMovement->InitialSpeed = movementSpeed;
	InitialLifeSpan = 10.0f;
}

// Called when the game starts or when spawned
void ASlower::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASlower::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

