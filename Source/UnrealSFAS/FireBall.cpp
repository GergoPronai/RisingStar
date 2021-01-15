// Fill out your copyright notice in the Description page of Project Settings.


#include "FireBall.h"

#include "UnrealSFASCharacter.h"
#include "Kismet/GameplayStatics.h"


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

	mesh->SetNotifyRigidBodyCollision(true);
}

// Called when the game starts or when spawned
void AFireBall::BeginPlay()
{
	Super::BeginPlay();
	gameModeRef = (AUnrealSFASGameMode*)GetWorld()->GetAuthGameMode();
	OnActorHit.AddDynamic(this, &AFireBall::OnHit);
}

// Called every frame
void AFireBall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AFireBall::OnHit(AActor* SelfActor, AActor* OtherActor, FVector NormalImpulse, const FHitResult& Hit)
{
	if(OtherActor->GetClass()->IsChildOf(AUnrealSFASCharacter::StaticClass()))
	{
		UE_LOG(LogTemp, Warning, TEXT("Hit"));
		AActor* projectileOwner = GetOwner();
		UGameplayStatics::ApplyDamage(
			OtherActor,
			gameModeRef->GetFireballDamage(),
			projectileOwner->GetInstigatorController(),
			this,
			UDamageType::StaticClass()
		);
	}
	Destroy();
}
