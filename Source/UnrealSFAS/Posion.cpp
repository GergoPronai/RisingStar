// Fill out your copyright notice in the Description page of Project Settings.


#include "Posion.h"

#include "UnrealSFASCharacter.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
APosion::APosion()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	movementSpeed = 1000.0f;

	mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	mesh->SetupAttachment(RootComponent);
	mesh->SetSimulatePhysics(true);

	projectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));
	projectileMovement->MaxSpeed = movementSpeed;
	projectileMovement->InitialSpeed = movementSpeed;
	InitialLifeSpan = 10.0f;

	mesh->SetNotifyRigidBodyCollision(true);
}

// Called when the game starts or when spawned
void APosion::BeginPlay()
{
	Super::BeginPlay();
	gameModeRef = (AUnrealSFASGameMode*)GetWorld()->GetAuthGameMode();
	OnActorHit.AddDynamic(this, &APosion::OnHit);
}

// Called every frame
void APosion::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APosion::OnHit(AActor* SelfActor, AActor* OtherActor, FVector NormalImpulse, const FHitResult& Hit)
{
	AActor* projectileOwner = GetOwner();
	if (OtherActor->GetClass()->IsChildOf(AUnrealSFASCharacter::StaticClass()))
	{
		if (OtherActor != projectileOwner)
		{
			UE_LOG(LogTemp, Warning, TEXT("Hit"));
			UGameplayStatics::ApplyDamage(
				OtherActor,
				gameModeRef->GetFireballDamage(),
				projectileOwner->GetInstigatorController(),
				this,
				UDamageType::StaticClass()
			);
		}
	}
	
	if (OtherActor != projectileOwner)
	{
		Destroy();
	}
}
