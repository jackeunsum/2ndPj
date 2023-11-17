// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy.h"
#include "EBullet.h"
#include "Playerpawn.h"
#include "Components/ArrowComponent.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "EnemyFS.h"



// Sets default values
AEnemy::AEnemy()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	/*
	myCapsuleComp = CreateDefaultSubobject<UCapsuleComponent>(TEXT("MyCapsuleComponent"));
	SetRootComponent(myCapsuleComp);
	myCapsuleComp->SetCollisionProfileName(TEXT("Enemy"));
	//const FVector boxSize = FVector(32.0f, 32.0f, 50.0f);
	//myBoxComp->SetBoxExtent(boxSize);

	mySkeletalMeshComp = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMeshComp"));
	mySkeletalMeshComp->SetupAttachment(myCapsuleComp);

	//const FVector relativePos = FVector(0, 0, -50.f);
	//myMeshComp->SetRelativeLocation(relativePos);

	myArrowComp = CreateDefaultSubobject<UArrowComponent>(TEXT("FirePosition"));
	myArrowComp->SetupAttachment(mySkeletalMeshComp);
	*/
	
	//총알 발사 변수 초기화
	fireCooltime = 2.0f;
	fireTimerTime = 0; 
	
	//타겟은 일단 없음
	target = nullptr;
	HP = 5000;

	fsm = CreateDefaultSubobject<UEnemyFS>(TEXT("FSM"));
}

// Called when the game starts or when spawned
void AEnemy::BeginPlay()
{
	Super::BeginPlay();
	
}

/*
void AEnemy::Fire()
{
	GetWorld()->SpawnActor<AEBullet>(magazine, myArrowComp->GetComponentLocation(), myArrowComp->GetComponentRotation());
}
*/

void AEnemy::FireCoolTimer(float cooltime, float deltaTime)
{
	if (fireTimerTime < cooltime)
	{
		fireTimerTime += deltaTime;
	}
	else
		{
		fireTimerTime = 0;
		//Fire();
		}
}

void AEnemy::FindPlayer()
{
	
}

// Called every frame
void AEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (target != nullptr) // if (target)
		{
		const FVector _newDir = target->GetActorLocation() - GetActorLocation();
		
		FRotator PlayerRot = UKismetMathLibrary::FindLookAtRotation(this->GetActorLocation(), target->GetActorLocation());
		SetActorRotation(PlayerRot);
		}
}

void AEnemy::OnEnemyOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSeep, const FHitResult& SweepResult)
{
	APlayerpawn* player = Cast<APlayerpawn>(OtherActor);
	if(player != nullptr)
	{
		// 딱히 없음
	}
}
