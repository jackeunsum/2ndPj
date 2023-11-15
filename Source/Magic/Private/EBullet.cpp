// Fill out your copyright notice in the Description page of Project Settings.


#include "EBullet.h"
#include "Playerpawn.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AEBullet::AEBullet()
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
}

// Called when the game starts or when spawned
void AEBullet::BeginPlay()
{
	Super::BeginPlay();

	FTimerHandle deathTimer;
	//GetWorld()->GetTimerManager().SetTimer(deathTimer,FTimerDelegate::CreateLambda([this]()->void{Destroy();}), 2.0f,false);
	collisionComp -> OnComponentBeginOverlap.AddDynamic(this,&AEBullet::OnBulletOverlap);
}

// Called every frame
void AEBullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
}

void AEBullet::OnBulletOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSeep, const FHitResult& SweepResult)
{
	APlayerpawn* player = Cast<APlayerpawn>(OtherActor);
	if(player != nullptr)
	{
		if(player->HP>0)
		{
			player->HP -= 1000;
			GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Red,FString::Printf(TEXT("player HP: %d"),player->HP));
			if(player->HP == 0)
			{
				GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Red,TEXT("You die"));
				//UGameplayStatics::SetGamePaused(GetWorld(),true);
			}
		}
		else if(player->HP<=0)
		{
			GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Red, TEXT("You die"));
			//UGameplayStatics::SetGamePaused(GetWorld(),true);
		}
	}
}

