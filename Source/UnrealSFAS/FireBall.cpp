// Fill out your copyright notice in the Description page of Project Settings.


#include "FireBall.h"

// Sets default values
AFireBall::AFireBall()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	
    //damage *= modifier.damageModifier;
	//cooldown *= modifier.cooldownModifier;
	//penertartion *= modifier.penetrationModifier;
    
	movementSpeed = 1000.0f;

	mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	mesh->SetupAttachment(RootComponent);
	mesh->SetSimulatePhysics(true);

	projectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));
	projectileMovement->MaxSpeed = movementSpeed;
	projectileMovement->InitialSpeed = movementSpeed;
	InitialLifeSpan = 10.0f;
}

// Called when the game starts or when spawned
void AFireBall::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AFireBall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


