// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UnrealSFASGameMode.h"
#include "FireBall.h"
#include "Slower.h"
#include "GameFramework/Character.h"
#include "UnrealSFASCharacter.generated.h"


UCLASS(config=Game)
class AUnrealSFASCharacter : public ACharacter
{
	GENERATED_BODY()
	float fireballCooldown;
	bool onFireballCooldown = false;
	void FireballResetTimer();
	
	float slowerCooldown;
	bool onSlowerCooldown = false;
	void SlowerResetTimer();
	float fHealth = 100.0f;
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
		
	/** Spell Cast **/
	void Spell1();
	void Spell2();
public:
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
	
protected:
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

