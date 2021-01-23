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
	if(LineOfSightTo(PlayerPawn) && IsInFront(PlayerPawn))
	{
		// AI starts shooting at the enemy
		//UE_LOG(LogTemp, Warning, TEXT("AI Shooting"));
		//character->Shooting();
	}
}

bool AEnemyAIController::IsInFront(AActor* ActorToCheck)
{
	AIPawn = GetPawn();
	FVector AIForwardVector = AIPawn->GetActorForwardVector();
	FVector PlayerPositionVector = ActorToCheck->GetActorLocation();
	FVector AIPositionVector = AIPawn->GetActorLocation();
	FVector AIToPlayerVector = PlayerPositionVector - AIPositionVector;
	AIToPlayerVector.Normalize();

	float directionDotProduct = FVector::DotProduct(AIToPlayerVector, AIForwardVector);
	if (directionDotProduct > 0.0f) return true;
	else							return false;
}
