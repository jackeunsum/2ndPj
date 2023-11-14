// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Enemy.generated.h"

UCLASS()
class MAGIC_API AEnemy : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEnemy();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void Move(FVector dir, float deltaSec);

	void Fire();

	void FireCoolTimer(float cooltime, float deltaTime);

	void FindPlayer();
	AActor* target;
	
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
	class UCapsuleComponent* myCapsuleComp;
	UPROPERTY(EditAnywhere)
	class USkeletalMeshComponent* mySkeletalMeshComp;
	UPROPERTY(EditAnywhere)
	class UArrowComponent* myArrowComp;
	
	UPROPERTY(EditAnywhere)
	TSubclassOf<class AEBullet> magazine;
	
	UPROPERTY(EditAnywhere)
	float fireCooltime;

private:
	float fireTimerTime;
};
