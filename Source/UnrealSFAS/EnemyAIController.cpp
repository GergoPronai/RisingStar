// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyAIController.h"

#include "Kismet/GameplayStatics.h"
AEnemyAIController::AEnemyAIController()
{
	
}

void AEnemyAIController::BeginPlay()
{
	Super::BeginPlay();
	PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
}

void AEnemyAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	SetFocus(PlayerPawn);
	if(LineOfSightTo(PlayerPawn) && IsInFront(PlayerPawn))
	{
		if(isShooting == false)
		{
			GetWorld()->GetTimerManager().SetTimer(timer, this, &AEnemyAIController::ResetTimer, fireRate, false);
			AUnrealSFASCharacter* character = Cast<AUnrealSFASCharacter>(GetPawn());
			character->Shooting();
			isShooting = true;
		}
	}
	else
	{
		MoveToActor(PlayerPawn, 20.0f);
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

void AEnemyAIController::ResetTimer()
{
	isShooting = false;
}
