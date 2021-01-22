// Fill out your copyright notice in the Description page of Project Settings.


#include "Shooting.h"

#include "UnrealSFASCharacter.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AShooting::AShooting()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	mesh->SetupAttachment(RootComponent);
	mesh->SetSimulatePhysics(true);

	projectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));
	projectileMovement->MaxSpeed = moveSpeed;
	projectileMovement->InitialSpeed = moveSpeed;
	mesh->SetNotifyRigidBodyCollision(true);
}

// Called when the game starts or when spawned
void AShooting::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogTemp, Warning, TEXT("Started"));
	gameModeRef = (AUnrealSFASGameMode*)GetWorld()->GetAuthGameMode();
	OnActorHit.AddDynamic(this, &AShooting::OnHit);
}

// Called every frame
void AShooting::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	FVector deltaLocation = FVector(moveSpeed * GetWorld()->DeltaTimeSeconds, 0.0f, 0.0f);
	AddActorLocalOffset(deltaLocation);
}

void AShooting::OnHit(AActor* SelfActor, AActor* OtherActor, FVector NormalImpulse, const FHitResult& Hit)
{
	UE_LOG(LogTemp, Warning, TEXT("GotCalled"));
	if (OtherActor->GetClass()->IsChildOf(AUnrealSFASCharacter::StaticClass()))
	{
		UE_LOG(LogTemp, Warning, TEXT("Hit"));
		AActor* projectileOwner = GetOwner();
		UGameplayStatics::ApplyDamage(
			OtherActor,
			gameModeRef->GetShootingDamage(),
			projectileOwner->GetInstigatorController(),
			this,
			UDamageType::StaticClass()
		);
	}
	Destroy();
}
