// Fill out your copyright notice in the Description page of Project Settings.


#include "Chest.h"

AChest::AChest()
{
	UE_LOG(LogTemp, Error, TEXT("ChestLoaded"));
	isOpened = false;
	numberOfWeapons = 3; // Index 0 to 3
	
}

void AChest::BeginPlay()
{
	Super::BeginPlay();
	
}

void AChest::SpawnWeapon()
{

	int weaponToSpawn = rand() % numberOfWeapons + 1;

	if (weaponToSpawn == 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("Shot Gun"));
		weaponEquiped = Weapons::Shotgun;
	}
	
	else if (weaponToSpawn == 1)
	{
		UE_LOG(LogTemp, Warning, TEXT("Katana Spawned"));
		weaponEquiped = Weapons::Katana;
	}
	
	else if (weaponToSpawn == 2)
	{
		UE_LOG(LogTemp, Warning, TEXT("Pistol Spawned"));
		weaponEquiped = Weapons::Pistol;
	}
	
	else if (weaponToSpawn == 3)
	{
		UE_LOG(LogTemp, Warning, TEXT("AK Spawned"));
		weaponEquiped = Weapons::AK;
	}
	
}


void AChest::Interact()
{
	if(!isOpened)
	{
		UE_LOG(LogTemp, Warning, TEXT("Open"));
		SpawnWeapon();
		isOpened = true;
	}
}
