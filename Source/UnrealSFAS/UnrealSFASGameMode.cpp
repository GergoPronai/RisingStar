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
}


// UpgradeOptions AUnrealSFASGameMode::GetUpgradesOptions()
// {
// 	std::string upgrade1, upgrade2, upgrade3;
// 	int upgradeIndex1, upgradeIndex2, upgradeIndex3;
//
// 	upgradeIndex1 = rand() % 0 + upgrades.size() - 1;
// 	upgrade1 = upgrades[upgradeIndex1];
//
// 	do
// 	{
// 		upgradeIndex2 = rand() % 0 + upgrades.size() - 1;
// 	}while(upgradeIndex2 == upgradeIndex1);
// 	upgrade2 = upgrades[upgradeIndex2];
// 	
// 	do
// 	{
// 		upgradeIndex3 = rand() % 0 + upgrades.size() - 1;
// 	}while (upgradeIndex3 == upgradeIndex1 || upgradeIndex3 == upgradeIndex2);
// 	upgrade3 = upgrades[upgradeIndex3];
// 	
// 	UpgradeOptions upgradesToReturn = {upgrade1, upgrade2, upgrade3};
// 	return upgradesToReturn;
// }

FireballModifier AUnrealSFASGameMode::FireballGetModifier()
{
	return fireballModifier;
}


float AUnrealSFASGameMode::FireballGetCooldown()
{
	return fireballCooldown;
}

float AUnrealSFASGameMode::GetFireballDamage()
{
	return (fireballDamage + fireballModifier.damageModifier);
}


SlowerModifier AUnrealSFASGameMode::SlowerGetModifier()
{
	return slowerModifire;
}


float AUnrealSFASGameMode::SlowerGetCooldown()
{
	return slowerCooldown;
}

float AUnrealSFASGameMode::GetSlowerEffect()
{
	return (slowerAmount + slowerModifire.amountModifier);
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

