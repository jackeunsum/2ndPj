// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ToNextLevel.generated.h"

UCLASS()
class MAGIC_API AToNextLevel : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AToNextLevel();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere)
	class UBoxComponent* colComp;

	UPROPERTY(VisibleAnywhere)
	class UStaticMeshComponent* meshComp;

	UPROPERTY(VisibleAnywhere)
	class UNiagaraComponent* niagaraComp;
	
	UPROPERTY(EditAnywhere, Category = "Level")
	FName levelToLoad;

	UFUNCTION()
	void OverLevel(UPrimitiveComponent* OverlappedComponent,class AActor* OtherActor,class UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSeep, const FHitResult &SweepResult);
};
