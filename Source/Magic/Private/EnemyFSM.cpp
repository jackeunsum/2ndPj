// Fill out your copyright notice in the Description page of Project Settings.

#include "Playerpawn.h"
#include "Enemy.h"
#include "Kismet/GameplayStatics.h"
#include "EnemyFSM.h"

// Sets default values
AEnemyFSM::AEnemyFSM()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AEnemyFSM::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AEnemyFSM::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
}

