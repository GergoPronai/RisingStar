// Fill out your copyright notice in the Description page of Project Settings.

#pragma once



#include "CoreMinimal.h"
#include "Master_Interactable.h"
#include "Blueprint/UserWidget.h"
#include "Chest.generated.h"


/**
 * 
 */
UCLASS()

class UNREALSFAS_API AChest : public AMaster_Interactable
{
	GENERATED_BODY()


	UPROPERTY(EditAnywhere)
	TSubclassOf<UUserWidget> StoreHUDClass;
	
	UPROPERTY()
	UUserWidget* Store;

	
protected:
	virtual void BeginPlay() override;

	
public:
	AChest();
	void OpenStore();
	
	UFUNCTION(BlueprintCallable)
	void CloseStore();
	
	virtual void Interact() override;
	
private:
	enum class Weapons { Shotgun, Katana, Pistol, AK };
	Weapons weaponEquiped;
	bool isOpened;
	int numberOfWeapons;
	void Pause();
};
