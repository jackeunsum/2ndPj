// Fill out your copyright notice in the Description page of Project Settings.


#include "ForDestroy.h"

#include "NiagaraComponent.h"
#include "PBullet.h"
#include "Chaos/GeometryParticlesfwd.h"
#include "Components/BoxComponent.h"

// Sets default values
AForDestroy::AForDestroy()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	colComp = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComp"));
	SetRootComponent(colComp);

	meshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	meshComp -> SetupAttachment(colComp);

	niagaraComp = CreateDefaultSubobject<UNiagaraComponent>(TEXT("FxComp"));
	niagaraComp -> SetupAttachment(colComp);
}

// Called when the game starts or when spawned
void AForDestroy::BeginPlay()
{
	Super::BeginPlay();

	colComp->OnComponentBeginOverlap.AddDynamic(this,&AForDestroy::BaksalOverlap);
}

void AForDestroy::BaksalOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSeep, const FHitResult& SweepResult)
{
	APBullet* bullet = Cast<APBullet>(OtherActor);
	GEngine->AddOnScreenDebugMessage(-1,3.0f,FColor::Red,TEXT("Destroy Overlap"));

}

// Called every frame
void AForDestroy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


