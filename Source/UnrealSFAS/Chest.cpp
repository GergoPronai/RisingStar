// Fill out your copyright notice in the Description page of Project Settings.


#include "Chest.h"

#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"

AChest::AChest()
{
	//UE_LOG(LogTemp, Error, TEXT("ChestLoaded"));
	isOpened = false;
	numberOfWeapons = 3; // Index 0 to 3
	
}

void AChest::BeginPlay()
{
	Super::BeginPlay();
}

void AChest::OpenStore()
{
	Store = CreateWidget<UUserWidget>(GetWorld(), StoreHUDClass);
	if (Store != nullptr)
	{
		Store->AddToViewport();
		UGameplayStatics::SetGamePaused(GetWorld(), true);
	}
}

void AChest::CloseStore()
{
	UGameplayStatics::SetGamePaused(GetWorld(), false);
	Destroy();
}

void AChest::Interact()
{
	if(!isOpened)
	{
		UE_LOG(LogTemp, Warning, TEXT("Open"));
		OpenStore();
		isOpened = true;
	}
}

