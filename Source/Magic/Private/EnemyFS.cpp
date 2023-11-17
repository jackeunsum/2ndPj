// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyFS.h"

#include "Enemy.h"
#include "Playerpawn.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UEnemyFS::UEnemyFS()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UEnemyFS::BeginPlay()
{
	Super::BeginPlay();

	// ...
	auto actor = UGameplayStatics::GetActorOfClass(GetWorld(),APlayerpawn::StaticClass());
	target = Cast<APlayerpawn>(actor);
	me = Cast<AEnemy>(GetOwner());
}


// Called every frame
void UEnemyFS::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	switch(mState)
	{
	case EEnemyState::Idle:
		IdleState();
		break;
	case EEnemyState::Move:
		MoveState();
		break;
	case EEnemyState::Attack:
		AttackState();
		break;
	case EEnemyState::Damage:
		DamageState();
		break;
	case EEnemyState::Die:
		DieState();
		break;
	}
	// ...
}

void UEnemyFS::IdleState()
{
	FVector dir = target->GetActorLocation() - me -> GetActorLocation();
	if(dir.Size()<=daegiRange)
	{
		mState = EEnemyState::Move;
	}
	currentTime = 0;
}

void UEnemyFS::MoveState()
{
	FVector destination = target->GetActorLocation();
	FVector dir = destination - me -> GetActorLocation();
	me -> AddMovementInput(dir.GetSafeNormal());
	if(dir.Size()>daegiRange)
	{
		mState = EEnemyState::Idle;
	}
	
	if(dir.Size()<=attackRange)
	{
		mState = EEnemyState::Attack;
	}
}

void UEnemyFS::AttackState()
{
	currentTime += GetWorld()->DeltaTimeSeconds;
	if(currentTime > attackDelayTime)
	{
		GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Red, TEXT("Enemy attacking"));
		currentTime = 0;
	}
	float distance = FVector::Distance(target->GetActorLocation(),me->GetActorLocation());
	if(distance > attackRange)
	{
		mState = EEnemyState::Move;
	}
}

void UEnemyFS::DamageState()
{
	
}

void UEnemyFS::DieState()
{
	
}

void UEnemyFS::OnDamageProcess()
{
	
}

