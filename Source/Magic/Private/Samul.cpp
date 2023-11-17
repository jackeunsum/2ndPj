// Fill out your copyright notice in the Description page of Project Settings.


#include "Samul.h"

#include "PBullet.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"

// 마법으로 부수기 위한 사물이다

// Sets default values
ASamul::ASamul()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	myBoxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollidor"));
	SetRootComponent(myBoxComp);
	//myBoxComp->SetCollisionProfileName(TEXT("Samul"));
	//const FVector boxSize = FVector(32.0f, 32.0f, 50.0f);
	//myBoxComp->SetBoxExtent(boxSize);

	myStaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComp"));
	myStaticMeshComp->SetupAttachment(myBoxComp);
	
}

// Called when the game starts or when spawned
void ASamul::BeginPlay()
{
	Super::BeginPlay();
	
	//myBoxComp -> OnComponentBeginOverlap.AddDynamic(this,&ASamul::OnBulletSamulOverlap);

}

// Called every frame
void ASamul::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASamul::OnBulletSamulOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSeep, const FHitResult& SweepResult)
{
	APBullet* bullet = Cast<APBullet>(OtherActor);
	if (bullet)
	{
		GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Yellow, "bullet valid");
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Yellow, "bullet invalid");
	}
	GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Yellow, "Overlap occured");
	//OtherActor->Destroy();
	//Destroy();
}

