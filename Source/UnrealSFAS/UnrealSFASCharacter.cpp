// Copyright Epic Games, Inc. All Rights Reserved.

#include "UnrealSFASCharacter.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "Master_Interactable.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"

//////////////////////////////////////////////////////////////////////////
// AUnrealSFASCharacter

AUnrealSFASCharacter::AUnrealSFASCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
	
	// set our turn rates for input
	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;

	fireballCooldown = 0.0f;
	
	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f); // ...at this rotation rate
	GetCharacterMovement()->JumpZVelocity = 600.f;
	GetCharacterMovement()->AirControl = 0.2f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 300.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named MyCharacter (to avoid direct content references in C++)

	projectileSpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("Projectile Spawn Point"));
	projectileSpawnPoint->SetupAttachment(Mesh);
	projectileSpawnPoint->SetRelativeLocation(FVector(0.0f, 50.0f, 140.0f));
}


// Called when the game starts or when spawned
void AUnrealSFASCharacter::BeginPlay()
{
	Super::BeginPlay();
	gameModeRef = (AUnrealSFASGameMode*)GetWorld()->GetAuthGameMode();
	chest = (AChest*)GetWorld()->GetAuthGameMode();

	GetWorld()->GetTimerManager().SetTimer(timer, this, &AUnrealSFASCharacter::PlayerTimer, tickingDamageFrequency, true);
	
	ScoreCount = CreateWidget<UUserWidget>(GetWorld(), ScoreHUDClass);
	if (ScoreCount != nullptr && GetWorld()->GetName() == "MazeBase")
	{
		ScoreCount->AddToViewport();
	}
}

//////////////////////////////////////////////////////////////////////////
// Input
void AUnrealSFASCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// Set up gameplay key bindings
	check(PlayerInputComponent);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	PlayerInputComponent->BindAction("Interact", IE_Pressed, this, &AUnrealSFASCharacter::Interact);
	
	PlayerInputComponent->BindAxis("MoveForward", this, &AUnrealSFASCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AUnrealSFASCharacter::MoveRight);

	// We have 2 versions of the rotation bindings to handle different kinds of devices differently
	// "turn" handles devices that provide an absolute delta, such as a mouse.
	// "turnrate" is for devices that we choose to treat as a rate of change, such as an analog joystick
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("TurnRate", this, &AUnrealSFASCharacter::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("LookUpRate", this, &AUnrealSFASCharacter::LookUpAtRate);

	// handle touch devices
	PlayerInputComponent->BindTouch(IE_Pressed, this, &AUnrealSFASCharacter::TouchStarted);
	PlayerInputComponent->BindTouch(IE_Released, this, &AUnrealSFASCharacter::TouchStopped);

	// VR headset functionality
	PlayerInputComponent->BindAction("ResetVR", IE_Pressed, this, &AUnrealSFASCharacter::OnResetVR);

	// Spell use
	PlayerInputComponent->BindAction("Spell_1", IE_Pressed, this, &AUnrealSFASCharacter::Spell1);
	PlayerInputComponent->BindAction("Spell_2", IE_Pressed, this, &AUnrealSFASCharacter::Spell2);
	PlayerInputComponent->BindAction("Spell_3", IE_Pressed, this, &AUnrealSFASCharacter::Spell3);
	PlayerInputComponent->BindAction("Shooting", IE_Pressed, this, &AUnrealSFASCharacter::Shooting);
}


void AUnrealSFASCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AUnrealSFASCharacter::OnResetVR()
{
	UHeadMountedDisplayFunctionLibrary::ResetOrientationAndPosition();
}

void AUnrealSFASCharacter::TouchStarted(ETouchIndex::Type FingerIndex, FVector Location)
{
		Jump();
}

void AUnrealSFASCharacter::TouchStopped(ETouchIndex::Type FingerIndex, FVector Location)
{
		StopJumping();
}

void AUnrealSFASCharacter::Interact()
{
	FHitResult outHit;

	
	FVector start = GetFollowCamera()->GetComponentLocation();
	FVector end = start + GetFollowCamera()->GetForwardVector() * 500;

	if(GetWorld()->LineTraceSingleByChannel(outHit, start, end, ECC_Visibility))
	{
		AMaster_Interactable* object = Cast<AMaster_Interactable>(outHit.Actor);
		if(object)
		{
			object->Interact();
		}
	}
}


void AUnrealSFASCharacter::TurnAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void AUnrealSFASCharacter::LookUpAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

void AUnrealSFASCharacter::MoveForward(float Value)
{
	if ((Controller != NULL) && (Value != 0.0f))
	{
		// find out which way is forward
		
		if(isSlowed)
		{
			Value -= fSlowEffect;
			isSlowed = false;
		}
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}

void AUnrealSFASCharacter::MoveRight(float Value)
{
	if ( (Controller != NULL) && (Value != 0.0f) )
	{
		// find out which way is right
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);
	
		// get right vector 
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		// add movement in that direction
		AddMovementInput(Direction, Value);
	}
}

void AUnrealSFASCharacter::Shooting()
{
	if (shootingClass)
	{
		UE_LOG(LogTemp, Warning, TEXT("Shooting"));
		FVector spawnLocation = projectileSpawnPoint->GetComponentLocation();
		FRotator spawnRotation = projectileSpawnPoint->GetComponentRotation();
		AShooting* shooting = GetWorld()->SpawnActor<AShooting>(shootingClass, spawnLocation, spawnRotation);
		shooting->SetOwner(this);
	}
}




void AUnrealSFASCharacter::Spell1()
{
	UE_LOG(LogTemp, Warning, TEXT("Spell1"));
	if(fireballClass)
	{
		if(!onFireballCooldown)
		{
			FVector spawnLocation = projectileSpawnPoint->GetComponentLocation();
			FRotator spawnRotation = projectileSpawnPoint->GetComponentRotation();
			AFireBall* fireBall = GetWorld()->SpawnActor<AFireBall>(fireballClass, spawnLocation, spawnRotation);
			fireBall->SetOwner(this);
			onFireballCooldown = true;
			GetWorld()->GetTimerManager().SetTimer(timer, this, &AUnrealSFASCharacter::FireballResetTimer, gameModeRef->FireballGetCooldown(), false);
		}
	}
}

void AUnrealSFASCharacter::Spell2()
{
	UE_LOG(LogTemp, Warning, TEXT("Spell2"));
	if (slowerClass)
	{
		if (!onSlowerCooldown)
		{
			FVector spawnLocation = projectileSpawnPoint->GetComponentLocation();
			FRotator spawnRotation = projectileSpawnPoint->GetComponentRotation();
			ASlower* slower = GetWorld()->SpawnActor<ASlower>(slowerClass, spawnLocation, spawnRotation);
			slower->SetOwner(this);
			onSlowerCooldown = true;
			GetWorld()->GetTimerManager().SetTimer(timer, this, &AUnrealSFASCharacter::SlowerResetTimer, gameModeRef->SlowerGetCooldown(), false);
		}
	}
}

void AUnrealSFASCharacter::Spell3()
{
	UE_LOG(LogTemp, Warning, TEXT("Spell3"));
	if (posionClass)
	{
		if (!onPosionCooldown)
		{
			FVector spawnLocation = projectileSpawnPoint->GetComponentLocation();
			FRotator spawnRotation = projectileSpawnPoint->GetComponentRotation();
			APosion* posionBall = GetWorld()->SpawnActor<APosion>(posionClass, spawnLocation, spawnRotation);
			posionBall->SetOwner(this);
			onPosionCooldown = true;
			isPosioned = true;
			GetWorld()->GetTimerManager().SetTimer(timer, this, &AUnrealSFASCharacter::PosionResetCooldown, gameModeRef->GetPosionCooldown(), false);
		}
	}
}

void AUnrealSFASCharacter::FireballResetTimer()
{
		onFireballCooldown = false;
}

void AUnrealSFASCharacter::SlowerResetTimer()
{
	onSlowerCooldown = false;
}

void AUnrealSFASCharacter::PosionResetTimer()
{
	isPosioned = false;
}

void AUnrealSFASCharacter::PosionResetCooldown()
{
	onPosionCooldown = false;
}

float AUnrealSFASCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	if (DamageCauser->GetClass()->IsChildOf(AFireBall::StaticClass()) || DamageCauser->GetClass()->IsChildOf(AShooting::StaticClass()))
	{
		fHealth -= DamageAmount;
		if (fHealth <= 0.0f)
		{
			UE_LOG(LogTemp, Warning, TEXT("Dead"));
			gameModeRef->AddScore();
			Destroy();
		}
	}
	else if (DamageCauser->GetClass()->IsChildOf(ASlower::StaticClass()))
	{
		fSlowEffect = DamageAmount;
		isSlowed = true;
	}
	else if(DamageCauser->GetClass()->IsChildOf(APosion::StaticClass()))
	{
		GetWorld()->GetTimerManager().SetTimer(timer, this, &AUnrealSFASCharacter::PosionDamage, gameModeRef->GetPosionDamageFrequency(), true);
	}
	return DamageAmount;
}

int AUnrealSFASCharacter::GetScore()
{
	return gameModeRef->GetScore();
}

void AUnrealSFASCharacter::PosionDamage()
{
	UE_LOG(LogTemp, Warning, TEXT("Posion"));
	fHealth -= gameModeRef->GetPosionDamage();
	if(fHealth <= 0.0f)
	{
		UE_LOG(LogTemp, Warning, TEXT("Dead"));
		gameModeRef->AddScore();
		Destroy();
	}
}

float AUnrealSFASCharacter::GetHealthPrecent()
{
	return fHealth / MAX_HEALTH;
}

void AUnrealSFASCharacter::PlayerTimer()
{
	//fHealth -= tickingDamage;
}

void AUnrealSFASCharacter::CloseChest()
{
	chest->CloseStore();
}

int AUnrealSFASCharacter::GetPoisonDamageAmount()
{
	return gameModeRef->GetPoisonDamageAmount();
}

int AUnrealSFASCharacter::GetPoisonDamageCost()
{
	return gameModeRef->GetPoisonDamageCost();
}

int AUnrealSFASCharacter::GetPoisonDamageLevel()
{
	return gameModeRef->GetPoisonDamageLevel();
}

int AUnrealSFASCharacter::GetPoisonFrequencyAmount()
{
	return gameModeRef->GetPoisonFrequencyAmount();
}

int AUnrealSFASCharacter::GetPoisonFrequencyCost()
{
	return gameModeRef->GetPoisonFrequencyCost();
}

int AUnrealSFASCharacter::GetPoisonFrequencyLevel()
{
	return gameModeRef->GetPoisonFrequencyLevel();
}

int AUnrealSFASCharacter::GetPoisonCooldownAmount()
{
	return gameModeRef->GetPoisonCooldownAmount();
}

int AUnrealSFASCharacter::GetPoisonCooldownCost()
{
	return gameModeRef->GetPoisonCooldownCost();
}

int AUnrealSFASCharacter::GetPoisonCooldownLevel()
{
	return gameModeRef->GetPoisonCooldownLevel();
}

int AUnrealSFASCharacter::GetSlowAmount()
{
	return gameModeRef->GetSlowAmount();
}

int AUnrealSFASCharacter::GetSlowAmountCost()
{
	return gameModeRef->GetSlowAmountCost();
}

int AUnrealSFASCharacter::GetSlowAmountLevel()
{
	return gameModeRef->GetSlowAmountLevel();
}

int AUnrealSFASCharacter::GetSlowCooldownAmount()
{
	return gameModeRef->GetSlowCooldownAmount();
}

int AUnrealSFASCharacter::GetSlowCooldownCost()
{
	return gameModeRef->GetSlowCooldownCost();
}

int AUnrealSFASCharacter::GetSlowCooldownLevel()
{
	return gameModeRef->GetSlowCooldownLevel();
}

int AUnrealSFASCharacter::GetFireballDamageAmount()
{
	return gameModeRef->GetFireballDamageAmount();
}

int AUnrealSFASCharacter::GetFireballDamageCost()
{
	return gameModeRef->GetFireballDamageCost();
}

int AUnrealSFASCharacter::GetFireballDamageLevel()
{
	return gameModeRef->GetFireballDamageLevel();
}

int AUnrealSFASCharacter::GetFireballCooldownAmount()
{
	return gameModeRef->GetFireballCooldownAmount();
}

int AUnrealSFASCharacter::GetFireballCooldownCost()
{
	return gameModeRef->GetFireballCooldownCost();
}

int AUnrealSFASCharacter::GetFireballCooldownLevel()
{
	return gameModeRef->GetFireballCooldownLevel();
}

void AUnrealSFASCharacter::PoisonDamageUpgrade()
{
	gameModeRef->PoisonDamageUpgrade();
}

void AUnrealSFASCharacter::PoisonFrequencyUpgrade()
{
	gameModeRef->PoisonFrequencyUpgrade();
}

void AUnrealSFASCharacter::PoisonCooldownUpgrade()
{
	gameModeRef->PoisonCooldownUpgrade();
}

void AUnrealSFASCharacter::SlowAmountUpgrade()
{
	gameModeRef->SlowAmountUpgrade();
}

void AUnrealSFASCharacter::SlowCooldownUpgrade()
{
	gameModeRef->SlowCooldownUpgrade();
}

void AUnrealSFASCharacter::FireballDamageUpgrade()
{
	gameModeRef->FireballDamageUpgrade();
}

void AUnrealSFASCharacter::FireballCooldownUpgrade()
{
	gameModeRef->FireballCooldownUpgrade();
}

void AUnrealSFASCharacter::AIShooting(TSubclassOf<AShooting> _shootingClass, USceneComponent* _projectileSpawnPoint)
{
	UE_LOG(LogTemp, Warning, TEXT("Shooting"));
	FVector spawnLocation = _projectileSpawnPoint->GetComponentLocation();
	FRotator spawnRotation = _projectileSpawnPoint->GetComponentRotation();
	AShooting* shooting = GetWorld()->SpawnActor<AShooting>(_shootingClass, spawnLocation, spawnRotation);
	shooting->SetOwner(this);
}

void AUnrealSFASCharacter::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	
}
