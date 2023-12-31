// Fill out your copyright notice in the Description page of Project Settings.


#include "NPC.h"

#include "Playerpawn.h"
#include "Blueprint/UserWidget.h"
#include "Camera/CameraComponent.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Itemshop.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
ANPC::ANPC()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	cameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	cameraComp -> SetupAttachment(RootComponent);
	triggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Trigger"));
	triggerBox -> SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ANPC::BeginPlay()
{
	Super::BeginPlay();
	triggerBox -> OnComponentBeginOverlap.AddDynamic(this,&ANPC::OverlapBeginTB);
}

// Called every frame
void ANPC::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ANPC::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ANPC::OverlapBeginTB(UPrimitiveComponent* OverlappedComponent,class AActor* OtherActor,class UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSeep, const FHitResult& SweepResult)
{
	//GEngine->AddOnScreenDebugMessage(-1,3.0f,FColor::Red,TEXT("HoHo"));
	//APlayerpawn* play = Cast<APlayerpawn>(OtherActor);
	//play->GetCharacterMovement()->MaxWalkSpeed = 0;
	//play->GetCharacterMovement()->MinAnalogWalkSpeed = 0;
	if(WidgetRef)
	{
		itemShopWidget = CreateWidget<UItemshop>(GetWorld(),WidgetRef);
		if(itemShopWidget)
		{
			itemShopWidget->ownerNPC = this;
			itemShopWidget -> AddToViewport();
		}
	}

	APlayerController* player = UGameplayStatics::GetPlayerController(this,0);	
	player -> SetViewTargetWithBlend(this,0.7f);
	player -> SetInputMode(FInputModeUIOnly());
	player -> SetShowMouseCursor(true);
}

