// Fill out your copyright notice in the Description page of Project Settings.


#include "ToNextLevel.h"

#include "NiagaraComponent.h"
#include "Playerpawn.h"
#include "Components/BoxComponent.h"

// Sets default values
AToNextLevel::AToNextLevel()
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
void AToNextLevel::BeginPlay()
{
	Super::BeginPlay();

	colComp->OnComponentBeginOverlap.AddDynamic(this,&AToNextLevel::OverLevel);
}

void AToNextLevel::OverLevel(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSeep, const FHitResult& SweepResult)
{
	APlayerpawn* player = Cast<APlayerpawn>(OtherActor);
	GEngine->AddOnScreenDebugMessage(-1,3.0f,FColor::Red,TEXT("Overlap"));
	
	if(OtherActor && levelToLoad != "")
	{
		
	}
}

// Called every frame
void AToNextLevel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

