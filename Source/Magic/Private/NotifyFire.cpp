// Fill out your copyright notice in the Description page of Project Settings.


#include "NotifyFire.h"

#include "Playerpawn.h"

void UNotifyFire::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration,
                              const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration, EventReference);
	APlayerpawn* TPS = Cast<APlayerpawn>(MeshComp->GetOwner());
	if(TPS!=nullptr)
	{
		TPS->Spawn();
	}
}

void UNotifyFire::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime,
	const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyTick(MeshComp, Animation, FrameDeltaTime, EventReference);
}

void UNotifyFire::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
	const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyEnd(MeshComp, Animation, EventReference);
}
