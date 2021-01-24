// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"


#include "EnemyAIController.h"
#include "UnrealSFASCharacter.h"
#include "GameFramework/Actor.h"
#include "EnemySpawner.generated.h"

UCLASS()
class UNREALSFAS_API AEnemySpawner : public AActor
{
	GENERATED_BODY()
	float spawnTimer = 5.0f;

	UPROPERTY(EditAnywhere)
	TSubclassOf<AUnrealSFASCharacter> enemyClass;

	UPROPERTY(EditAnywhere)
	TSubclassOf<AEnemyAIController> enemyController;

	
	UPROPERTY(VisibleAnywhere)
	FTimerHandle timer;
	
public:	
	// Sets default values for this actor's properties
	AEnemySpawner();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void SpawnEnemy();
};
