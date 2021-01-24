// Fill out your copyright notice in the Description page of Project Settings.


#include "Trigger.h"

ATrigger::ATrigger()
{
	OnActorBeginOverlap.AddDynamic(this, &ATrigger::OnOverlapBegin);
}

void ATrigger::BeginPlay()
{
	Super::BeginPlay();
	gameModeRef = (AUnrealSFASGameMode*)GetWorld()->GetAuthGameMode();
}


void ATrigger::OnOverlapBegin(class AActor* OverlappedActor, class AActor* OtherActor)
{
	gameModeRef->LoadLevel();
}