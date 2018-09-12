// Fill out your copyright notice in the Description page of Project Settings.

#include "FPSObjectiveActor.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "FPSCharacter.h"
#include "Components/SkeletalMeshComponent.h"

// Sets default values
AFPSObjectiveActor::AFPSObjectiveActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	//���actor�����ʵ��
	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	MeshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);//����������Ҫ��ײЧ��
	RootComponent = MeshComp; //����Ԫ����Ϊ��Ԫ��

	SphereComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	SphereComp->SetCollisionEnabled(ECollisionEnabled::QueryOnly);//����ʵ��ֻ����ײ��ѯЧ��
	SphereComp->SetCollisionResponseToAllChannels(ECR_Ignore);//����ʵ�����������û����ײ��Ӧ
	SphereComp->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);//����ʵ�������ײ����ʱ�з�Ӧ

	SphereComp->SetupAttachment(MeshComp);
}

// Called when the game starts or when spawned
void AFPSObjectiveActor::BeginPlay()
{
	Super::BeginPlay();

	PlayEffects();
}

//��ײЧ������
void AFPSObjectiveActor::PlayEffects()
{
	UGameplayStatics::SpawnEmitterAtLocation(this, PickUpFX, GetActorLocation());
}

// Called every frame
void AFPSObjectiveActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

//��дactor�����ص�����
void AFPSObjectiveActor::NotifyActorBeginOverlap(AActor * OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);

	PlayEffects();

	AFPSCharacter*MyCharacter = Cast<AFPSCharacter>(OtherActor);

	//������ҷ����ص�����־λ��ֵtrue���ݻ�����
	if (MyCharacter)
	{
		MyCharacter->bIsCarryingSubjective = true;

		////���������������ʧ
		//Destroy();

		//���������ı�mesh����
		TArray<UStaticMeshComponent*> Components;
		this->GetComponents<UStaticMeshComponent>(Components);
		UStaticMeshComponent* targetComp = Components[0];
		targetComp->SetMaterial(0, M_EmptyObjectiveMaterial);

		//�ı���������
		TArray<USkeletalMeshComponent*> CharacterComponents;
		MyCharacter->GetComponents<USkeletalMeshComponent>(CharacterComponents);
		USkeletalMeshComponent* targetCharacterComp = CharacterComponents[2];
		targetCharacterComp->SetMaterial(0, M_SecondWeaponMaterial);
	}
}

