// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameFramework/ProjectileMovementComponent.h"

#include "Slower.generated.h"

UCLASS()
class UNREALSFAS_API ASlower : public AActor
{
	GENERATED_BODY()
		UPROPERTY(EditAnywhere)
		float movementSpeed;
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* mesh;
	UPROPERTY(VisibleAnywhere)
	UProjectileMovementComponent* projectileMovement;
	UPROPERTY()
	FVector moveAmount;
	
public:	
	// Sets default values for this actor's properties
	ASlower();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
