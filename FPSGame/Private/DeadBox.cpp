// Fill out your copyright notice in the Description page of Project Settings.

#include "DeadBox.h"
#include "Components/BoxComponent.h"
#include "FPSGameMode.h"
#include "FPSCharacter.h"

// Sets default values
ADeadBox::ADeadBox()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	OverlapComp = CreateDefaultSubobject<UBoxComponent>(TEXT("OverlapComp"));
	OverlapComp->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	OverlapComp->SetCollisionResponseToAllChannels(ECR_Ignore);
	OverlapComp->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	RootComponent = OverlapComp;
}

// Called when the game starts or when spawned
void ADeadBox::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void ADeadBox::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

//�ص�����
void ADeadBox::NotifyActorBeginOverlap(AActor* OtherActor)
{
	AFPSCharacter*MyPawn = Cast<AFPSCharacter>(OtherActor);
	AFPSGameMode*GM = Cast<AFPSGameMode>(GetWorld()->GetAuthGameMode());
	if (GM)
	{
		GM->OnPawnDead(MyPawn);//����gamemode�������������
		UE_LOG(LogTemp, Log, TEXT("you are dead!"));
	}
}

