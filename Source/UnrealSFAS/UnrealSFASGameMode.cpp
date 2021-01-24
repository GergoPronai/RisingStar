// Copyright Epic Games, Inc. All Rights Reserved.

#include "UnrealSFASGameMode.h"
#include "UnrealSFASCharacter.h"
#include "UObject/ConstructorHelpers.h"

AUnrealSFASGameMode::AUnrealSFASGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}

	poisonDamage.amount = 10;
	poisonDamage.cost = 5;
	poisonDamage.level = 1;
	
	poisonFrequency.amount = 10;
	poisonFrequency.cost = 5;
	poisonFrequency.level = 1;

	poisonCooldown.amount = 10;
	poisonCooldown.cost = 5;
	poisonCooldown.level = 1;
	
	SlowAmount.amount = 10;
	SlowAmount.cost = 5;
	SlowAmount.level = 1;
	
	SlowCooldown.amount = 10;
	SlowCooldown.cost = 5;
	SlowCooldown.level = 1;
	
	FireballDamage.amount = 10;
	FireballDamage.cost = 5;
	FireballDamage.level = 1;

	FireballCooldown.amount = 10;
	FireballCooldown.cost = 5;
	FireballCooldown.level = 1;
}

float AUnrealSFASGameMode::FireballGetCooldown()
{
	return fireballCooldown;
}

float AUnrealSFASGameMode::GetFireballDamage()
{
	return fireballDamage;
}

float AUnrealSFASGameMode::SlowerGetCooldown()
{
	return slowerCooldown;
}

float AUnrealSFASGameMode::GetSlowerEffect()
{
	return slowerAmount;
}

float AUnrealSFASGameMode::GetShootingDamage()
{
	return shootingDamage;
}

float AUnrealSFASGameMode::GetPosionDamage()
{
	return posionDamage;
}

float AUnrealSFASGameMode::GetPosionCooldown()
{
	return posionCooldown;
}

float AUnrealSFASGameMode::GetPosionDamageFrequency()
{
	return posionDamageFrequency;
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
