// Fill out your copyright notice in the Description page of Project Settings.


#include "AtributesGameInstance.h"

void UAtributesGameInstance::SetData(int preLoadScore, Upgrades preLoadPoisonDamage, Upgrades preLoadPoisonFrequency, Upgrades preLoadPoisonCooldown,
	Upgrades preLoadSlowAmount, Upgrades preLoadSlowCooldown, Upgrades preLoadFireballDamage, Upgrades preLoadFireballCooldown)
{
	score = preLoadScore;

	poisonDamage = preLoadPoisonDamage;
	poisonFrequency = preLoadPoisonFrequency;
	poisonCooldown = preLoadPoisonCooldown;

	slowAmount = preLoadSlowAmount;
	slowCooldown = preLoadSlowCooldown;

	fireballDamage = preLoadFireballDamage;
	fireballCooldown = preLoadFireballCooldown;
}

int UAtributesGameInstance::GetScore()
{
	return score;
}


Upgrades UAtributesGameInstance::GetPoisonDamage()
{
	return poisonDamage;
}

Upgrades UAtributesGameInstance::GetPoisonFrequency()
{
	return poisonFrequency;
}

Upgrades UAtributesGameInstance::GetPoisonCooldown()
{
	return poisonCooldown;
}

Upgrades UAtributesGameInstance::GetSlowAmount()
{
	return slowAmount;
}

Upgrades UAtributesGameInstance::GetSlowCooldown()
{
	return slowCooldown;
}

Upgrades UAtributesGameInstance::GetFireballDamage()
{
	return fireballDamage;
}

Upgrades UAtributesGameInstance::GetFireballCooldown()
{
	return fireballCooldown;
}
