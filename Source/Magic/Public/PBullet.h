// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PBullet.generated.h"

UENUM()
enum class EBulletType : uint8
{
	E_Water UMETA(DisplayName = "Water"),
	E_Fire UMETA(DisplayName = "Fire"),
	E_Earth UMETA(DisplayName = "Earth"),
	E_Air UMETA(DisplayName = "Air")
};

UCLASS()
class MAGIC_API APBullet : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APBullet();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	class UMGGameInstance* MGInstance;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere, Category = "Movement")
	class UProjectileMovementComponent* movementComp;

	UPROPERTY(VisibleAnywhere, Category = "Col")
	class USphereComponent* collisionComp;

	UPROPERTY(VisibleAnywhere, Category = "Mesh")
	class UStaticMeshComponent* meshComp;

public:
	UFUNCTION()
	void OnBulletOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSeep, const FHitResult &SweepResult);
	
	UPROPERTY(EditAnywhere)
	float Soksung;

	UPROPERTY(EditAnywhere)
	EBulletType BType;
};
