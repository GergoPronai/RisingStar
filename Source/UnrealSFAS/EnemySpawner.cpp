// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemySpawner.h"


// Sets default values
AEnemySpawner::AEnemySpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AEnemySpawner::BeginPlay()
{
	Super::BeginPlay();
	GetWorld()->GetTimerManager().SetTimer(timer, this, &AEnemySpawner::SpawnEnemy, spawnTimer, true);
}

// Called every frame
void AEnemySpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AEnemySpawner::SpawnEnemy()
{
	FVector spawnLocation = GetActorLocation();
	FRotator spawnRotation = GetActorRotation();
	AUnrealSFASCharacter* enemy;
	enemy = GetWorld()->SpawnActor<AUnrealSFASCharacter>(enemyClass, spawnLocation, spawnRotation);
	if(enemy)
	{
		enemy->SpawnDefaultController();
	}
}