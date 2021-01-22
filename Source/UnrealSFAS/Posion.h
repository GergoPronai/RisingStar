// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "UnrealSFASGameMode.h"
#include "GameFramework/Actor.h"
#include "GameFramework/ProjectileMovementComponent.h"

#include "Posion.generated.h"

UCLASS()
class UNREALSFAS_API APosion : public AActor
{
	GENERATED_BODY()
	
		UPROPERTY(VisibleAnywhere)
		AUnrealSFASGameMode* gameModeRef;

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
	APosion();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UFUNCTION()
	void OnHit(AActor* SelfActor, AActor* OtherActor, FVector NormalImpulse, const FHitResult& Hit);
};
