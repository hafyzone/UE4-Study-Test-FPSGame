// Fill out your copyright notice in the Description page of Project Settings.

#include "FPSExtractionZone.h"
#include "Components/BoxComponent.h"
#include "FPSCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Components/DecalComponent.h"
#include "FPSGameMode.h"

// Sets default values
AFPSExtractionZone::AFPSExtractionZone()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//创建关卡位置box并设置碰撞相关参数和大小
	OverlapComp = CreateDefaultSubobject<UBoxComponent>(TEXT("OverlapComp"));
	OverlapComp->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	OverlapComp->SetCollisionResponseToAllChannels(ECR_Ignore);
	OverlapComp->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	OverlapComp->SetBoxExtent(FVector(200.0f));
	RootComponent = OverlapComp;

	////设置不显示（默认不显示）
	//OverlapComp->SetHiddenInGame(true);

	//DecalComp = CreateDefaultSubobject<UDecalComponent>(TEXT("DecalComp"));
	//DecalComp->DecalSize = FVector(200.0f);
	//DecalComp->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AFPSExtractionZone::BeginPlay()
{
	Super::BeginPlay();

}

//碰撞效果函数
void AFPSExtractionZone::BoxPlayEffects()
{
	UE_LOG(LogTemp, Log, TEXT("have a collision!"));
}

// Called every frame
void AFPSExtractionZone::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//添加关卡标志物品浮动效果
	FVector NewLocation = GetActorLocation();
	float DeltaHeight = (FMath::Sin(RunningTime + DeltaTime) - FMath::Sin(RunningTime));
	NewLocation.Z += DeltaHeight * 30.0f;      //把高度以20的系数进行缩放
	RunningTime += DeltaTime;
	SetActorLocation(NewLocation);
}

//重写关卡口区域的重叠事件
void AFPSExtractionZone::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);

	AFPSCharacter*MyPawn = Cast<AFPSCharacter>(OtherActor);

	//判断玩家并判断是否携带物品
	if (MyPawn&&MyPawn->bIsCarryingSubjective)
	{
		AFPSGameMode*GM = Cast<AFPSGameMode>(GetWorld()->GetAuthGameMode());

		if (GM)
		{
			GM->CompleteMission(MyPawn);//调用完成任务函数

			BoxPlayEffects();//重叠效果

			Destroy();//重叠后摧毁物体
		}
	}
}