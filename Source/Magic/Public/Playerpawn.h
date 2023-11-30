// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputAction.h"
#include "Playerpawn.generated.h"

class UInputMappingContext;
class UInputAction;

UCLASS()
class MAGIC_API APlayerpawn : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayerpawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = "Camera")
	class USpringArmComponent* springArmComp;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = "Camera")
	class UCameraComponent* cameraComp;

	UPROPERTY(VisibleAnywhere, Category = "Fire")
	class UStaticMeshComponent* weaponMeshComp;
	
	UPROPERTY(EditAnywhere)
	class UArrowComponent* myArrowComp;
	
	
	UPROPERTY()
	class UCharacterMovementComponent* charState;
	
	UPROPERTY(EditAnywhere, Category = "InputW")
	UInputMappingContext* WPlayerMappingContext;
	
	UPROPERTY(EditAnywhere, Category = "InputW")
	UInputAction* WMoveIA;
	UPROPERTY(EditAnywhere, Category = "InputW")
	UInputAction* WLookUpIA;
	UPROPERTY(EditAnywhere, Category = "InputW")
	UInputAction* WTurnIA;
	UPROPERTY(EditAnywhere, Category = "InputW")
	UInputAction* WJumpIA;
	UPROPERTY(EditAnywhere, Category = "InputW")
	UInputAction* WFireIA;
	UPROPERTY(EditAnywhere, Category = "InputW")
	UInputAction* WStamIA;
	UPROPERTY(EditAnywhere, Category = "InputW")
	UInputAction* RideIA;
	UPROPERTY(EditAnywhere, Category = "InputW")
	UInputAction* FMoveIA;
	UPROPERTY(EditAnywhere, Category = "InputW")
	UInputAction* WalkToRunIA;
	UPROPERTY(EditAnywhere, Category = "InputW")
	UInputAction* InteractionIA;
	

	UPROPERTY(EditAnywhere, Category = "Animation")
	UAnimMontage* attackAnimMontage;
	
public:
	void Move(const FInputActionValue& Value);
	void LookUp(const FInputActionValue& Value);
	void Turn(const FInputActionValue& Value);
	void InputJump(const FInputActionValue& Value);
	void InputFire(const FInputActionValue& Value);
	void Stam(const FInputActionValue& Value);
	void Ride(const FInputActionValue& Value);
	void Move3d(const FInputActionValue& Value);
	void WalkToRun(const FInputActionValue& Value);
	void Interaction(const FInputActionValue& Value);
	
	UFUNCTION()
	void Spawn();
	
public:
	UPROPERTY(EditAnywhere, Category = "Fire")
	float fireCoolTime;

	UPROPERTY(EditAnywhere, Category = "Fire")
	float stamcool;

	UPROPERTY(EditAnywhere, Category = "Fire")
	TSubclassOf<class APBullet> magazine;

	UPROPERTY(BlueprintReadWrite)
	int PTotalExp;
	
	UPROPERTY(BlueprintReadWrite)
	int EnemyExp;

	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category="insert")
	float interactionDistance;

	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category="insert")
	int64 money = 9999; // mmorpg에선 서버에 돈 데이터 적는다

	UFUNCTION(BlueprintCallable)
	void UpdateMoney(int64 val);
	
protected:
	void FireCoolTimer(float Duration, float deltaTime);

	class UMGGameInstance* MGInstance;
	
private:
	FVector moveDirection0;
	FVector moveDirection1;
	int mode;
	
	bool fireReady;
	float fireTimer;
	bool Isrun;
	
	
};
