// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyAIController.h"


void AEnemyAIController::BeginPlay()
{
	Super::BeginPlay();
	PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
}

void AEnemyAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	SetFocus(PlayerPawn);
	MoveToActor(PlayerPawn, 20.0f);
}

void AEnemyAIController::DealDamage(float damage)
{
	fHealth -= damage;
}
