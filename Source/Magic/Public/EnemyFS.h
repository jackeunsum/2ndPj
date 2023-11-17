// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "EnemyFS.generated.h"


UENUM(BlueprintType)
enum class EEnemyState : uint8
{
	Idle,
	Move,
	Attack,
	Damage,
	Die
};


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MAGIC_API UEnemyFS : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UEnemyFS();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category = FSM)
	EEnemyState mState = EEnemyState::Idle;

	void IdleState();
	void MoveState();
	void AttackState();
	void DamageState();
	void DieState();

	UPROPERTY(EditDefaultsOnly, Category = FSM)
	float idleDelayTime = 2;
	float currentTime = 0;

	UPROPERTY(VisibleAnywhere, Category = FSM)
	class APlayerpawn* target;
	
	UPROPERTY()
	class AEnemy* me;
	
	//이 범위 안이면 공격한다
	UPROPERTY(EditAnywhere, Category=FSM)
	float attackRange = 200.0f;

	UPROPERTY(EditAnywhere, Category=FSM)
	float daegiRange = 550.0f;
	
	//일정 시간 한번 공격한다
	UPROPERTY(EditAnywhere, Category = FSM)
	float attackDelayTime = 2.0f;

	void OnDamageProcess();
};
