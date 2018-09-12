// Fill out your copyright notice in the Description page of Project Settings.

#include "LaunchPad.h"
#include "Components/BoxComponent.h"
#include "FPSCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Components/DecalComponent.h"
#include "FPSGameMode.h"

// Sets default values
ALaunchPad::ALaunchPad()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	//�����ؿ�λ��box��������ײ��ز����ʹ�С
	LaunchPadComp = CreateDefaultSubobject<UBoxComponent>(TEXT("LaunchPadComp"));
	LaunchPadComp->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	LaunchPadComp->SetCollisionResponseToAllChannels(ECR_Ignore);
	LaunchPadComp->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	LaunchPadComp->SetBoxExtent(FVector(20.0f, 20.0f, 10.0f));
	RootComponent = LaunchPadComp;

	//������ʾ��Ĭ�ϲ���ʾ��
	LaunchPadComp->SetHiddenInGame(false);
}

// Called when the game starts or when spawned
void ALaunchPad::BeginPlay()
{
	Super::BeginPlay();

}

//����Ч��
void ALaunchPad::LauchEffects()
{
	UGameplayStatics::SpawnEmitterAtLocation(this, LauchFX, GetActorLocation());
}

// Called every frame
void ALaunchPad::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

//�����ص���Ч��
void ALaunchPad::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);

	AFPSCharacter*MyPawn = Cast<AFPSCharacter>(OtherActor);

	//��Ծ�ǶȺ�������Ĭ��ֵ
	LaunchStrength = 1500;
	LaunchPitchAngle = 100.0f;

	FRotator LaunchDirection = GetActorRotation();
	LaunchDirection.Pitch += LaunchPitchAngle;
	FVector LaunthVelocity = LaunchDirection.Vector() * LaunchStrength;

	//������Ծ����(��Я��������Ʒ����Ч)
	if (MyPawn&&MyPawn->bIsCarryingSubjective)
	{
		MyPawn->LaunchCharacter(LaunthVelocity, true, true);
		LauchEffects();
	}
}


