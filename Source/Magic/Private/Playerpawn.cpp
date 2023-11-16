// Fill out your copyright notice in the Description page of Project Settings.
#include "Magic/Public/Playerpawn.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "MGGameInstance.h"
#include "PBullet.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Materials/MaterialExpressionStrata.h"

// Sets default values
APlayerpawn::APlayerpawn()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	springArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComp"));
	springArmComp->SetupAttachment(RootComponent);
	springArmComp->SetRelativeLocationAndRotation(FVector(0, 0, 50), FRotator(-20, 0, 0));
	springArmComp->TargetArmLength = 400;
	springArmComp->bUsePawnControlRotation = true;
	
	cameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComp"));
	cameraComp->SetupAttachment(springArmComp);
	cameraComp->bUsePawnControlRotation = false;
	
	weaponMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WeaponMesh"));
	weaponMeshComp->SetupAttachment(GetMesh());
	
	charState = GetCharacterMovement();
	charState->bOrientRotationToMovement = true;
	charState->RotationRate = FRotator(0.f,180.0f,0.0f);
	charState->MaxWalkSpeed = 300.0f;
	charState->GravityScale = 1.7;
	bUseControllerRotationYaw = false;
	
	mode = 0; // mode = 0이면 걷기, 1이면 날기
	stamina = 100;
	stamcool = 119.0f;

	fireCoolTime = 0.4f;
	fireTimer = 0;
	fireReady = true;
}

// Called when the game starts or when spawned
void APlayerpawn::BeginPlay()
{
	Super::BeginPlay();
	if (APlayerController* PlayerController = Cast<APlayerController>(GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem
			= ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(WPlayerMappingContext, 0);
		}
	}
	
	MGInstance = Cast<UMGGameInstance>(GetWorld()->GetGameInstance());
	Maxp = MGInstance->GetCharData(1)->MaxHP;
	HP = Maxp;
	MGInstance->PlayerAttack = MGInstance->GetCharData(1)->Attack;
	TotalExp = 0;
	EnemyExp = 50; // 임시
	
}

// Called every frame
void APlayerpawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	if(mode == 0)
	{
		charState->GravityScale = 1.7;
		charState->AirControl = 0.05f;
		charState->FallingLateralFriction = 0;
		moveDirection0 = FTransform(GetControlRotation()).TransformVector(moveDirection0);
		AddMovementInput(moveDirection0);
		moveDirection0 = FVector::ZeroVector;
	}
	else if(mode == 1)
	{
		charState->GravityScale = 0.001f;
		charState->AirControl = 0.3f;
		charState->FallingLateralFriction = 0.5f;
		
		moveDirection1 = FTransform(GetControlRotation()).TransformVector(moveDirection1);
		AddMovementInput(moveDirection1);
		moveDirection1 = FVector::ZeroVector;
		if(charState->IsFalling() == false)
		{
			mode = 0;
			GEngine->AddOnScreenDebugMessage(-1, 0.5f, FColor::Yellow, TEXT("Now Walking"));
		}
	}

	if(!fireReady)
	{
		FireCoolTimer(fireCoolTime, DeltaTime);
	}
	
	if(stamina < 100)
	{
		stamina += 0.01;
		GEngine->AddOnScreenDebugMessage(-1, 0.1f, FColor::Yellow, FString::Printf(TEXT("Stamina: %f"),stamina));
		
	}
	else if(stamina >= 100)
	{
		stamina = 100.0f;
	}

	TotalExp = MGInstance->EnemyDeath * (EnemyExp);

	NeedExp = MGInstance->GetCharData(MGInstance->Playerlevel)->ExpToNextLevel;
	if(MGInstance->Playerlevel == 1)
	{
		CurExp = TotalExp;
	}
	else
	{
		CurExp = TotalExp - MGInstance->GetCharData(MGInstance->Playerlevel-1)->TotalExp;
	}

	//GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Yellow, FString::Printf(TEXT("EXP: %d"),TotalExp));
	
	if(MGInstance->GetCharData(MGInstance->Playerlevel)->TotalExp <= TotalExp )
	{
		if(MGInstance->Playerlevel<5)
		MGInstance->Playerlevel++;
		MGInstance->PlayerAttack = MGInstance->GetCharData(MGInstance->Playerlevel)->Attack;
		Maxp = MGInstance->GetCharData(MGInstance->Playerlevel)->MaxHP;
		HP = Maxp; // 레벨업 시 피 회복
		
		GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Green, FString::Printf(TEXT("Level Up! Current Level: %d"),MGInstance->Playerlevel));
	}
}

// Called to bind functionality to input
void APlayerpawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(WMoveIA, ETriggerEvent::Triggered, this, &APlayerpawn::Move);
		EnhancedInputComponent->BindAction(WFireIA, ETriggerEvent::Triggered, this, &APlayerpawn::InputFire);
		EnhancedInputComponent->BindAction(WJumpIA, ETriggerEvent::Triggered, this, &APlayerpawn::InputJump);
		EnhancedInputComponent->BindAction(WTurnIA, ETriggerEvent::Triggered, this, &APlayerpawn::Turn);
		EnhancedInputComponent->BindAction(WLookUpIA, ETriggerEvent::Triggered, this, &APlayerpawn::LookUp);
		EnhancedInputComponent->BindAction(WStamIA, ETriggerEvent::Triggered, this, &APlayerpawn::Stam);
		EnhancedInputComponent->BindAction(RideIA, ETriggerEvent::Triggered, this, &APlayerpawn::Ride);
		EnhancedInputComponent->BindAction(FMoveIA, ETriggerEvent::Triggered, this, &APlayerpawn::Move3d);
		EnhancedInputComponent->BindAction(WalkToRunIA, ETriggerEvent::Triggered, this, &APlayerpawn::WalkToRun);
	}
}

void APlayerpawn::Move(const FInputActionValue& Value)
{
	const FVector _currentValue = Value.Get<FVector>();
	
	if (Controller)
	{
		if(mode == 0)
		{
			moveDirection0.Y = _currentValue.X;
			moveDirection0.X = _currentValue.Y;
		}
	}
}

void APlayerpawn::LookUp(const FInputActionValue& Value)
{
	const float _currentValue = Value.Get<float>();
	AddControllerPitchInput(_currentValue);
}

void APlayerpawn::Turn(const FInputActionValue& Value)
{
	const float _currentValue = Value.Get<float>();
	AddControllerYawInput(_currentValue);
}

void APlayerpawn::InputJump(const FInputActionValue& Value)
{
	if(mode == 0)
	{
		Jump();
	}
}

void APlayerpawn::InputFire(const FInputActionValue& Value)
{
	if(fireReady)
	{
		//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("Ready"));
		FTransform firePosition = weaponMeshComp -> GetSocketTransform(TEXT("FirePosition"));
		//firePosition.Rotator() = cameraComp->GetComponentRotation();
		GetWorld()->SpawnActor<APBullet>(magazine,firePosition);
		//SpawnBullet();
		fireReady = false;
		//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("Finish"));
		GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Yellow, FString::Printf(TEXT("EXP: %d"),CurExp));
		
	}
	
}

void APlayerpawn::Stam(const FInputActionValue& Value)
{
	if(mode==0 && stamina >= 10 )
	{
		FVector direction = GetActorForwardVector();
		SetActorLocation(GetActorLocation()+direction*300);
		
		stamina -= 10;
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, FString::Printf(TEXT("Stamina: %d"),stamina));
	}
}

void APlayerpawn::Ride(const FInputActionValue& Value)
{
	if(mode == 0)
	{
		mode = 1;
		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, TEXT("mode is riding"));
	}
	else if(mode == 1)
	{
		mode = 0;
		charState->FallingLateralFriction = 0.5f;
		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, TEXT("mode is walking"));
	}
}

void APlayerpawn::Move3d(const FInputActionValue& Value)
{
	const FVector _currentValue = Value.Get<FVector>();
	if(mode == 1)
	{
		if (Controller)
		{
			moveDirection1.Y = _currentValue.X;
			moveDirection1.X = _currentValue.Y;

			FVector NewLocation = GetActorLocation();
			NewLocation.Z += _currentValue.Z * 5;
			SetActorLocation(NewLocation);
		}
	}
}

void APlayerpawn::WalkToRun(const FInputActionValue& Value)
{
	if(mode == 0 )
	{
		if(charState->MaxWalkSpeed >= 700.0f)
		{
			charState->MaxWalkSpeed = 300.0f;
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("walk"));
		}
		else
		{
			charState->MaxWalkSpeed = 700.0f;
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("run"));
		}
	}
}

void APlayerpawn::SpawnBullet()
{
	
}

void APlayerpawn::FireCoolTimer(float Duration, float deltaTime)
{
	if(fireTimer < Duration)
	{
		fireTimer += deltaTime;
	}
	else
	{
		fireTimer = 0;
		fireReady = true;
	}
}
