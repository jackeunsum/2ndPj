// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "NPC.generated.h"

UCLASS()
class MAGIC_API ANPC : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ANPC();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
	class UCameraComponent* cameraComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interaction")
	class UBoxComponent* triggerBox;

	UFUNCTION()
	void OverlapBeginTB(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSeep, const FHitResult &SweepResult);

	UPROPERTY(EditAnywhere, Category = "Interaction")
	TSubclassOf<class UItemshop> WidgetRef; // 위젯 레퍼런스로 가져온다

	UPROPERTY()
	class UItemshop* itemShopWidget;
};
