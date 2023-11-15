// Fill out your copyright notice in the Description page of Project Settings.

#include "Magic/Public/PBullet.h"
#include "Enemy.h"
#include "MGGameInstance.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"

// Sets default values
APBullet::APBullet()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	collisionComp = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionComp"));
	collisionComp -> SetSphereRadius(10);

	meshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	meshComp->SetupAttachment(collisionComp);

	movementComp = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("MovementComp"));
	movementComp->SetUpdatedComponent(collisionComp);
	
	// 초기속도
	movementComp->InitialSpeed = 4000.f;
	// 최대속도
	movementComp->MaxSpeed = 6000.f;
	// 반동,
	movementComp->bShouldBounce = true;
	// 반동 크기
	movementComp->Bounciness = 0.1f;

	Soksung = 1000;
}

// Called when the game starts or when spawned
void APBullet::BeginPlay()
{
	Super::BeginPlay();
	
	FTimerHandle deathTimer;
	GetWorld()->GetTimerManager().SetTimer(deathTimer,FTimerDelegate::CreateLambda([this]()->void{Destroy();}), 2.0f,false);

	collisionComp -> OnComponentBeginOverlap.AddDynamic(this,&APBullet::OnBulletOverlap);

	MGInstance = Cast<UMGGameInstance>(GetWorld()->GetGameInstance());
}

// Called every frame
void APBullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APBullet::OnBulletOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSeep, const FHitResult& SweepResult)
{
	AEnemy* enemy = Cast<AEnemy>(OtherActor);
	if(enemy != nullptr)
	{
		if(enemy->HP>0)
		{
			enemy->HP -= Soksung;
			if(enemy->HP == 0)
			{
				OtherActor->Destroy();
				MGInstance->EnemyDeath ++;
				GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Yellow, FString::Printf(TEXT("Death: %d"),MGInstance->EnemyDeath));
			}
			GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Yellow, FString::Printf(TEXT("Enemy HP: %f"),enemy->HP));
		}
		else if(enemy->HP<=0)
		{
			//적 HP0일때 어케할지 고치고 싶으면 고쳐
			OtherActor->Destroy();
			MGInstance->EnemyDeath++;
			GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Red, FString::Printf(TEXT("Death: %d"),MGInstance->EnemyDeath));
		}
	}
}