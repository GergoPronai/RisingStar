// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "AtributesGameInstance.generated.h"

/**
 * 
 */

struct Upgrades
{
	int amount = 10;
	int cost = 5;
	int level = 1;
};

UCLASS()
class UNREALSFAS_API UAtributesGameInstance : public UGameInstance
{
	GENERATED_BODY()
		// FireballEffects
		
	int score;
	
	Upgrades poisonDamage;
	Upgrades poisonFrequency;
	Upgrades poisonCooldown;

	Upgrades slowAmount;
	Upgrades slowCooldown;

	Upgrades fireballDamage;
	Upgrades fireballCooldown;

public:
	void SetData(int preLoadScore, Upgrades preLoadPoisonDamage, Upgrades preLoadPoisonFrequency, Upgrades preLoadPoisonCooldown,
	Upgrades preLoadSlowAmount,	Upgrades preLoadSlowCooldown, Upgrades preLoadFireballDamage, Upgrades preLoadFireballCooldown);

	int GetScore();
	
	void AddScore();
	
	Upgrades GetPoisonDamage();
	Upgrades GetPoisonFrequency();
	Upgrades GetPoisonCooldown();

	Upgrades GetSlowAmount();
	Upgrades GetSlowCooldown();

	Upgrades GetFireballDamage();
	Upgrades GetFireballCooldown();
};
