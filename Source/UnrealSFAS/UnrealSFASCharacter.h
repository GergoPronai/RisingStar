// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

#include "Chest.h"
#include "UnrealSFASGameMode.h"
#include "FireBall.h"
#include "Posion.h"
#include "Slower.h"
#include "Shooting.h"
#include "Blueprint/UserWidget.h"
#include "GameFramework/Character.h"
#include "UnrealSFASCharacter.generated.h"


UCLASS(config=Game)
class AUnrealSFASCharacter : public ACharacter
{
	GENERATED_BODY()

	AChest* chest;

	float fireballCooldown;
	bool onFireballCooldown = false;
	void FireballResetTimer();
	
	float slowerCooldown;
	bool onSlowerCooldown = false;
	void SlowerResetTimer();
	
	float fHealth = 100.0f;
	const float MAX_HEALTH = 100.0f;
	float tickingDamage = 5.0f;

	float tickingDamageFrequency = 0.5f;
	
	float fSlowEffect = 0.0f;

	bool isPosioned = false;
	bool onPosionCooldown = false;
	void PosionResetTimer();
	void PosionResetCooldown();
	
	UFUNCTION(BlueprintPure)
	int GetScore();
	
	UPROPERTY(EditDefaultsOnly)
		TSubclassOf<AShooting> shootingClass;

	UPROPERTY(EditAnywhere)
	int score;
	
	UPROPERTY(EditAnywhere)
		TSubclassOf<UUserWidget> ScoreHUDClass;

	UPROPERTY()
		UUserWidget* ScoreCount;
	
	// Used to make the spells avaliable after the cool down
	// Needs the name of the spell passed
	
	AUnrealSFASGameMode* gameModeRef;
	UPROPERTY(VisibleAnywhere)
	FTimerHandle timer;
	
	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;
	
	/** Projectile **/
	UPROPERTY(VisibleAnywhere)
	USceneComponent* projectileSpawnPoint;

	/** Spell References **/
	UPROPERTY(EditAnywhere)
	TSubclassOf<AFireBall> fireballClass;
	
	UPROPERTY(EditAnywhere)
	TSubclassOf<ASlower> slowerClass;

	UPROPERTY(EditAnywhere)
	TSubclassOf<APosion> posionClass;

public:
	/** Spell Cast **/
	void Shooting();
	void Spell1();
	void Spell2();
	void Spell3();

	void AIShooting(TSubclassOf<AShooting> _shootingClass, USceneComponent* _projectileSpawnPoint);
	
	void PosionDamage();

	UFUNCTION(BlueprintPure)
	float GetHealthPrecent();

	void PlayerTimer();

	
	// Get Widget Output
	UFUNCTION(BlueprintPure)
	int GetPoisonDamageAmount();
	UFUNCTION(BlueprintPure)
	int GetPoisonDamageCost();
	UFUNCTION(BlueprintPure)
	int GetPoisonDamageLevel();

	UFUNCTION(BlueprintPure)
	int GetPoisonFrequencyAmount();
	UFUNCTION(BlueprintPure)
	int GetPoisonFrequencyCost();
	UFUNCTION(BlueprintPure)
	int GetPoisonFrequencyLevel();

	UFUNCTION(BlueprintPure)
	int GetPoisonCooldownAmount();
	UFUNCTION(BlueprintPure)
	int GetPoisonCooldownCost();
	UFUNCTION(BlueprintPure)
	int GetPoisonCooldownLevel();

	UFUNCTION(BlueprintPure)
	int GetSlowAmount();
	UFUNCTION(BlueprintPure)
	int GetSlowAmountCost();
	UFUNCTION(BlueprintPure)
	int GetSlowAmountLevel();

	UFUNCTION(BlueprintPure)
	int GetSlowCooldownAmount();
	UFUNCTION(BlueprintPure)
	int GetSlowCooldownCost();
	UFUNCTION(BlueprintPure)
	int GetSlowCooldownLevel();

	UFUNCTION(BlueprintPure)
	int GetFireballDamageAmount();
	UFUNCTION(BlueprintPure)
	int GetFireballDamageCost();
	UFUNCTION(BlueprintPure)
	int GetFireballDamageLevel();

	UFUNCTION(BlueprintPure)
	int GetFireballCooldownAmount();
	UFUNCTION(BlueprintPure)
	int GetFireballCooldownCost();
	UFUNCTION(BlueprintPure)
	int GetFireballCooldownLevel();

	UFUNCTION(BlueprintCallable)
	void PoisonDamageUpgrade();
	UFUNCTION(BlueprintCallable)
	void PoisonFrequencyUpgrade();
	UFUNCTION(BlueprintCallable)
	void PoisonCooldownUpgrade();

	UFUNCTION(BlueprintCallable)
	void SlowAmountUpgrade();
	UFUNCTION(BlueprintCallable)
	void SlowCooldownUpgrade();

	UFUNCTION(BlueprintCallable)
	void FireballDamageUpgrade();
	UFUNCTION(BlueprintCallable)
	void FireballCooldownUpgrade();
	
	UFUNCTION(BlueprintCallable)
	void CloseChest();
	
	AUnrealSFASCharacter();

	virtual void Tick(float DeltaTime) override;
	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseTurnRate;

	/** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseLookUpRate;

protected:
	virtual void BeginPlay() override;

	/** Resets HMD orientation in VR. */
	void OnResetVR();

	/** Called for forwards/backward input */
	void MoveForward(float Value);

	/** Called for side to side input */
	void MoveRight(float Value);

	/** 
	 * Called via input to turn at a given rate. 
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void TurnAtRate(float Rate);

	/**
	 * Called via input to turn look up/down at a given rate. 
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void LookUpAtRate(float Rate);

	/** Handler for when a touch input begins. */
	void TouchStarted(ETouchIndex::Type FingerIndex, FVector Location);

	/** Handler for when a touch input stops. */
	void TouchStopped(ETouchIndex::Type FingerIndex, FVector Location);

	void Interact();
	
	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	// End of APawn interface

public:
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;
};

