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

	//创建关卡位置box并设置碰撞相关参数和大小
	LaunchPadComp = CreateDefaultSubobject<UBoxComponent>(TEXT("LaunchPadComp"));
	LaunchPadComp->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	LaunchPadComp->SetCollisionResponseToAllChannels(ECR_Ignore);
	LaunchPadComp->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	LaunchPadComp->SetBoxExtent(FVector(20.0f, 20.0f, 10.0f));
	RootComponent = LaunchPadComp;

	//设置显示（默认不显示）
	LaunchPadComp->SetHiddenInGame(false);
}

// Called when the game starts or when spawned
void ALaunchPad::BeginPlay()
{
	Super::BeginPlay();

}

//弹跳效果
void ALaunchPad::LauchEffects()
{
	UGameplayStatics::SpawnEmitterAtLocation(this, LauchFX, GetActorLocation());
}

// Called every frame
void ALaunchPad::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

//发生重叠后效果
void ALaunchPad::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);

	AFPSCharacter*MyPawn = Cast<AFPSCharacter>(OtherActor);

	//跳跃角度和力量的默认值
	LaunchStrength = 1500;
	LaunchPitchAngle = 100.0f;

	FRotator LaunchDirection = GetActorRotation();
	LaunchDirection.Pitch += LaunchPitchAngle;
	FVector LaunthVelocity = LaunchDirection.Vector() * LaunchStrength;

	//调用跳跃函数(需携带必须物品才生效)
	if (MyPawn&&MyPawn->bIsCarryingSubjective)
	{
		MyPawn->LaunchCharacter(LaunthVelocity, true, true);
		LauchEffects();
	}
}


