// Fill out your copyright notice in the Description page of Project Settings.

#pragma once



#include "CoreMinimal.h"
#include "Master_Interactable.h"
#include "Chest.generated.h"


/**
 * 
 */
UCLASS()

class UNREALSFAS_API AChest : public AMaster_Interactable
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

	
public:
	AChest();
	void SpawnWeapon();
	virtual void Interact() override;
	
private:
	enum class Weapons { Shotgun, Katana, Pistol, AK };
	Weapons weaponEquiped;
	bool isOpened;
	int numberOfWeapons;
};
