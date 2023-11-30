// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Itez
/**
 * 
 */
UCLASS()
class MAGIC_API UItemshop : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category = "Shop")
	class ANPC* ownerNPC;
};
