// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "UnrealSFASCharacter.h"


#include "EnemyAIController.generated.h"

/**
 * 
 */
UCLASS()
class UNREALSFAS_API AEnemyAIController : public AAIController
{
	GENERATED_BODY()
	float fHealth = 100.0f;
	APawn* PlayerPawn;
	APawn* AIPawn;

	UPROPERTY(VisibleAnywhere)
	USceneComponent* projectileSpawnPoint;
	
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AShooting> shootingClass;
	
	float fireRate = 1.5f;
	bool isShooting = false;

	UPROPERTY(VisibleAnywhere)
		FTimerHandle timer;
	void ResetTimer();
public:
	AEnemyAIController();
protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

private:
	bool IsInFront(AActor* ActorToCheck);
};
