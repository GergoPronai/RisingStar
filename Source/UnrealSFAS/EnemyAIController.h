// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Kismet/GameplayStatics.h"

#include "CoreMinimal.h"
#include "AIController.h"
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
protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	
public:
	void DealDamage(float damage);
};
