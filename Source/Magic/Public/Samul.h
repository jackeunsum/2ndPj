// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Samul.generated.h"

UCLASS()
class MAGIC_API ASamul : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASamul();

	UPROPERTY(EditAnywhere)
	class UBoxComponent* myBoxComp;
	UPROPERTY(EditAnywhere)
	class UStaticMeshComponent* myStaticMeshComp;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class AEBullet> magazine;

	void OnBulletOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex, bool bFromSeep, const FHitResult& SweepResult);

};
