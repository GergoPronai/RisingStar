// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include <vector>
#include<string>

#include "FireBall.h"

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "UnrealSFASGameMode.generated.h"


struct FireballModifier
{
	float damageModifier = 1.0f;
	float cooldownModifier = 1.0f;
	float penetrationModifier = 1.0f;
};

struct UpgradeOptions
{
	std::string upgradeOption1;
	std::string upgradeOption2;
	std::string upgradeOption3;
};

UCLASS(minimalapi)
class AUnrealSFASGameMode : public AGameModeBase
{
	GENERATED_BODY()
private:

	// Effects
	float fireballDamage = 10.0f;
	float fireballCooldown = 2.5f;
	float fireballPenertartion = 0.0f;

	bool isFireballUnlocked = false;
	
	std::vector<std::string> upgrades =
	{
		"Fireball Unlock",
		"Fireball Damage",
		"Fireball Cooldown",
		"Slow Unlock"
		"Slow Duration",
		"Slow Cooldown",
	};
	FireballModifier fireballModifier;
public:
	AUnrealSFASGameMode();
	UpgradeOptions GetUpgradesOptions();
	void SetUpgrade();
	FireballModifier GetModifier();

	float GetCooldown();
	
};



