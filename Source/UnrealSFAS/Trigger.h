// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "UnrealSFASGameMode.h"
#include "Engine/TriggerBox.h"
#include "Trigger.generated.h"

/**
 * 
 */
UCLASS()
class UNREALSFAS_API ATrigger : public ATriggerBox
{
	GENERATED_BODY()
	UFUNCTION()
	void OnOverlapBegin(class AActor* OverlappedActor, class AActor* OtherActor);
	AUnrealSFASGameMode* gameModeRef;
protected:
	virtual void BeginPlay() override;
public:
	ATrigger();
};
