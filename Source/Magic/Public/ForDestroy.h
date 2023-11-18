// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ForDestroy.generated.h"

UCLASS()
class MAGIC_API AForDestroy : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AForDestroy();

	UPROPERTY(VisibleAnywhere)
	class UBoxComponent* colComp;

	UPROPERTY(VisibleAnywhere)
	class UStaticMeshComponent* meshComp;

	UPROPERTY(VisibleAnywhere)
	class UNiagaraComponent* niagaraComp;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void BaksalOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSeep, const FHitResult &SweepResult);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
