// Fill out your copyright notice in the Description page of Project Settings.

#include "MGGameInstance.h"

void UMGGameInstance::Init()
{
	Super::Init();
	UE_LOG(LogTemp,Warning,TEXT("level 20 Max HP: %d"),GetCharData(2)->MaxHP)
}

UMGGameInstance::UMGGameInstance()
{
	FString CharDataPath = TEXT("/Game/Data/ForMagic.ForMagic");
	static ConstructorHelpers::FObjectFinder<UDataTable> CharDT(*CharDataPath);
	ForCharTable = CharDT.Object;
	//PlayerAttack = GetCharData(1)->Attack;
}

ForChar* UMGGameInstance::GetCharData(int level)
{
	return ForCharTable->FindRow<ForChar>(*FString::FromInt(level),TEXT(""));
}


