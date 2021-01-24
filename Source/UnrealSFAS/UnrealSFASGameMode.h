// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include <vector>
#include <string>
#include "CoreMinimal.h"

#include "AtributesGameInstance.h"
#include "GameFramework/GameModeBase.h"
#include "UnrealSFASGameMode.generated.h"


UCLASS(minimalapi)
class AUnrealSFASGameMode : public AGameModeBase
{
	GENERATED_BODY()
private:

	UAtributesGameInstance* gameInstance;
	
	float fireballDamage = 50.0f;
	float fireballCooldown = 2.5f;
	bool isFireballUnlocked = false;

	// SlowerEffects
	float slowerCooldown = 3.5f;
	float slowerAmount = 350.0f;
	float slowerDuration = 2.0f;
	bool isSlowerUnlocked = false;

	float posionDamage = 5.0f;
	float posionLast = 2.5f;
	float posionDamageFrequency = 0.5f;
	float posionCooldown = 4.5f;

	float shootingDamage = 10.0f;

	int score;
	
	Upgrades poisonDamage;
	Upgrades poisonFrequency;
	Upgrades poisonCooldown;

	Upgrades SlowAmount;
	Upgrades SlowCooldown;

	Upgrades FireballDamage;
	Upgrades FireballCooldown;


public:
	AUnrealSFASGameMode();
	virtual void BeginPlay() override;
	void LoadLevel();
	
	void SetUpgrade();
	float FireballGetCooldown();
	float GetFireballDamage();
	
	float SlowerGetCooldown();
	float GetSlowerEffect();
	float GetShootingDamage();

	float GetPosionDamage();
	float GetPosionDamageFrequency();
	float GetPosionCooldown();
	
	int GetScore();
	void AddScore();

	int GetPoisonDamageAmount();
	int GetPoisonDamageCost();
	int GetPoisonDamageLevel();

	int GetPoisonFrequencyAmount();
	int GetPoisonFrequencyCost();
	int GetPoisonFrequencyLevel();

	int GetPoisonCooldownAmount();
	int GetPoisonCooldownCost();
	int GetPoisonCooldownLevel();

	int GetSlowAmount();
	int GetSlowAmountCost();
	int GetSlowAmountLevel();

	int GetSlowCooldownAmount();
	int GetSlowCooldownCost();
	int GetSlowCooldownLevel();

	int GetFireballDamageAmount();
	int GetFireballDamageCost();
	int GetFireballDamageLevel();

	int GetFireballCooldownAmount();
	int GetFireballCooldownCost();
	int GetFireballCooldownLevel();

	void PoisonDamageUpgrade();
	void PoisonFrequencyUpgrade();
	void PoisonCooldownUpgrade();

	void SlowAmountUpgrade();
	void SlowCooldownUpgrade();

	void FireballDamageUpgrade();
	void FireballCooldownUpgrade();
};
