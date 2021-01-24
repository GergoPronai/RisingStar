// Copyright Epic Games, Inc. All Rights Reserved.

#include "UnrealSFASGameMode.h"
#include "UnrealSFASCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "UObject/ConstructorHelpers.h"

AUnrealSFASGameMode::AUnrealSFASGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}

void AUnrealSFASGameMode::BeginPlay()
{
	Super::BeginPlay();
	gameInstance = Cast<UAtributesGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	
	UE_LOG(LogTemp, Warning, TEXT("!?"));
	score = gameInstance->GetScore();

	poisonDamage = gameInstance->GetPoisonDamage();
	poisonFrequency = gameInstance->GetPoisonFrequency();
	poisonCooldown = gameInstance->GetPoisonCooldown();

	SlowAmount = gameInstance->GetSlowAmount();
	SlowCooldown = gameInstance->GetSlowCooldown();

	FireballDamage = gameInstance->GetFireballDamage();
	FireballCooldown = gameInstance->GetFireballCooldown();
}

void AUnrealSFASGameMode::LoadLevel()
{
	gameInstance->SetData(score, poisonDamage, poisonFrequency, poisonCooldown,
		SlowAmount, SlowCooldown, FireballDamage, FireballCooldown);
	UGameplayStatics::OpenLevel(GetWorld(), "MazeBase");
}


float AUnrealSFASGameMode::FireballGetCooldown()
{
	return (fireballCooldown - (fireballCooldown * FireballCooldown.amount / 100));
}

float AUnrealSFASGameMode::GetFireballDamage()
{
	return (fireballDamage + (fireballDamage * FireballDamage.amount / 100));
}

float AUnrealSFASGameMode::SlowerGetCooldown()
{
	return (slowerCooldown - (slowerCooldown * SlowCooldown.amount / 100));
}

float AUnrealSFASGameMode::GetSlowerEffect()
{
	return (slowerAmount + (slowerAmount * SlowAmount.amount / 100));
}

float AUnrealSFASGameMode::GetShootingDamage()
{
	return shootingDamage;
}

float AUnrealSFASGameMode::GetPosionDamage()
{
	return (posionDamage + (posionDamage * poisonDamage.amount / 100));
}

float AUnrealSFASGameMode::GetPosionCooldown()
{
	return (posionCooldown - (posionCooldown * poisonCooldown.amount / 100));
}

float AUnrealSFASGameMode::GetPosionDamageFrequency()
{
	return (posionDamageFrequency - (posionDamageFrequency * poisonFrequency.amount / 100));
}

void AUnrealSFASGameMode::AddScore()
{
	score += 10;
}

int AUnrealSFASGameMode::GetScore()
{
	return score;
}

int AUnrealSFASGameMode::GetPoisonDamageAmount()
{
	return poisonDamage.amount;
}

int AUnrealSFASGameMode::GetPoisonDamageCost()
{
	return poisonDamage.cost;
}

int AUnrealSFASGameMode::GetPoisonDamageLevel()
{
	return poisonDamage.level;
}

int AUnrealSFASGameMode::GetPoisonFrequencyAmount()
{
	return poisonFrequency.amount;
}

int AUnrealSFASGameMode::GetPoisonFrequencyCost()
{
	return poisonFrequency.cost;
}

int AUnrealSFASGameMode::GetPoisonFrequencyLevel()
{
	return poisonFrequency.level;
}

int AUnrealSFASGameMode::GetPoisonCooldownAmount()
{
	return poisonCooldown.amount;
}

int AUnrealSFASGameMode::GetPoisonCooldownCost()
{
	return poisonCooldown.cost;
}

int AUnrealSFASGameMode::GetPoisonCooldownLevel()
{
	return poisonCooldown.level;
}

int AUnrealSFASGameMode::GetSlowAmount()
{
	return SlowAmount.amount;
}

int AUnrealSFASGameMode::GetSlowAmountCost()
{
	return SlowAmount.cost;
}

int AUnrealSFASGameMode::GetSlowAmountLevel()
{
	return SlowAmount.level;
}

int AUnrealSFASGameMode::GetSlowCooldownAmount()
{
	return SlowCooldown.amount;
}

int AUnrealSFASGameMode::GetSlowCooldownCost()
{
	return SlowCooldown.cost;
}

int AUnrealSFASGameMode::GetSlowCooldownLevel()
{
	return SlowCooldown.level;
}

int AUnrealSFASGameMode::GetFireballDamageAmount()
{
	return FireballDamage.amount;
}

int AUnrealSFASGameMode::GetFireballDamageCost()
{
	return FireballDamage.cost;
}

int AUnrealSFASGameMode::GetFireballDamageLevel()
{
	return FireballDamage.level;
}

int AUnrealSFASGameMode::GetFireballCooldownAmount()
{
	return FireballCooldown.amount;
}

int AUnrealSFASGameMode::GetFireballCooldownCost()
{
	return FireballCooldown.cost;
}

int AUnrealSFASGameMode::GetFireballCooldownLevel()
{
	return FireballCooldown.level;
}

void AUnrealSFASGameMode::PoisonDamageUpgrade()
{
	if(score >= poisonDamage.cost)
	{
		score -= poisonDamage.cost;
		poisonDamage.amount += 10;
		poisonDamage.cost += 5;
		poisonDamage.level += 1;
	}
}

void AUnrealSFASGameMode::PoisonFrequencyUpgrade()
{
	if (score >= poisonFrequency.cost)
	{		
		score -= poisonFrequency.cost;
		poisonFrequency.amount += 10;
		poisonFrequency.cost += 5;
		poisonFrequency.level += 1;
	}
}

void AUnrealSFASGameMode::PoisonCooldownUpgrade()
{
	if (score >= poisonCooldown.cost)
	{
		score -= poisonCooldown.cost;
		poisonCooldown.amount += 10;
		poisonCooldown.cost += 5;
		poisonCooldown.level += 1;
	}
}

void AUnrealSFASGameMode::SlowAmountUpgrade()
{
	if (score >= SlowAmount.cost)
	{
		score -= SlowAmount.cost;
		SlowAmount.amount += 10;
		SlowAmount.cost += 5;
		SlowAmount.level += 1;
	}
}

void AUnrealSFASGameMode::SlowCooldownUpgrade()
{
	if (score >= SlowCooldown.cost)
	{
		score -= SlowCooldown.cost;
		SlowCooldown.amount += 10;
		SlowCooldown.cost += 5;
		SlowCooldown.level += 1;
	}
}

void AUnrealSFASGameMode::FireballDamageUpgrade()
{
	if (score >= FireballDamage.cost)
	{
		score -= FireballDamage.cost;
		FireballDamage.amount += 10;
		FireballDamage.cost += 5;
		FireballDamage.level += 1;
	}
}

void AUnrealSFASGameMode::FireballCooldownUpgrade()
{
	if (score >= FireballCooldown.cost)
	{
		score -= FireballCooldown.cost;
		FireballCooldown.amount += 10;
		FireballCooldown.cost += 5;
		FireballCooldown.level += 1;
	}
}
