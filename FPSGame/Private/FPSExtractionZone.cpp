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

	//�����ؿ�λ��box��������ײ��ز����ʹ�С
	OverlapComp = CreateDefaultSubobject<UBoxComponent>(TEXT("OverlapComp"));
	OverlapComp->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	OverlapComp->SetCollisionResponseToAllChannels(ECR_Ignore);
	OverlapComp->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	OverlapComp->SetBoxExtent(FVector(200.0f));
	RootComponent = OverlapComp;

	////���ò���ʾ��Ĭ�ϲ���ʾ��
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

//��ײЧ������
void AFPSExtractionZone::BoxPlayEffects()
{
	UE_LOG(LogTemp, Log, TEXT("have a collision!"));
}

// Called every frame
void AFPSExtractionZone::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//��ӹؿ���־��Ʒ����Ч��
	FVector NewLocation = GetActorLocation();
	float DeltaHeight = (FMath::Sin(RunningTime + DeltaTime) - FMath::Sin(RunningTime));
	NewLocation.Z += DeltaHeight * 30.0f;      //�Ѹ߶���20��ϵ����������
	RunningTime += DeltaTime;
	SetActorLocation(NewLocation);
}

//��д�ؿ���������ص��¼�
void AFPSExtractionZone::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);

	AFPSCharacter*MyPawn = Cast<AFPSCharacter>(OtherActor);

	//�ж���Ҳ��ж��Ƿ�Я����Ʒ
	if (MyPawn&&MyPawn->bIsCarryingSubjective)
	{
		AFPSGameMode*GM = Cast<AFPSGameMode>(GetWorld()->GetAuthGameMode());

		if (GM)
		{
			GM->CompleteMission(MyPawn);//�������������

			BoxPlayEffects();//�ص�Ч��

			Destroy();//�ص���ݻ�����
		}
	}
}