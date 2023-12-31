// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "Engine/GameInstance.h"
#include "MGGameInstance.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct ForChar : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category = "PData")
	int ExpToNextLevel;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category = "PData")
	int TotalExp;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category = "PData")
	int MaxHP;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category = "PData")
	int Attack;
};


UCLASS()
class MAGIC_API UMGGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	UMGGameInstance();
	virtual void Init() override;

public:
	ForChar* GetCharData(int level);

	UPROPERTY(BlueprintReadWrite)
	int EnemyDeath;

	UPROPERTY(BlueprintReadWrite)
	int Playerlevel = 1;

	UPROPERTY(BlueprintReadWrite)
	int PlayerAttack;

	UPROPERTY(BlueprintReadWrite)
	float stamina = 100;

	UPROPERTY(BlueprintReadWrite)
	int HP;

	UPROPERTY(BlueprintReadWrite)
	int Maxp;

	UPROPERTY(BlueprintReadWrite)
	int NeedExp;

	UPROPERTY(BlueprintReadWrite)
	int CurExp;

	UPROPERTY(BlueprintReadWrite)
	bool Is1stReady;

	UPROPERTY(BlueprintReadWrite)
	bool Is2ndReady;

	UPROPERTY(BlueprintReadWrite)
	int jewel;
	
private:
	UPROPERTY()
	class UDataTable* ForCharTable;
};
