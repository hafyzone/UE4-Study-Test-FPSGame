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

	//添加actor网格和实体
	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	MeshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);//设置网格不需要碰撞效果
	RootComponent = MeshComp; //网格元素设为根元素

	SphereComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	SphereComp->SetCollisionEnabled(ECollisionEnabled::QueryOnly);//设置实体只有碰撞查询效果
	SphereComp->SetCollisionResponseToAllChannels(ECR_Ignore);//设置实体对所有物体没有碰撞反应
	SphereComp->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);//设置实体对人碰撞覆盖时有反应

	SphereComp->SetupAttachment(MeshComp);
}

// Called when the game starts or when spawned
void AFPSObjectiveActor::BeginPlay()
{
	Super::BeginPlay();

	PlayEffects();
}

//碰撞效果函数
void AFPSObjectiveActor::PlayEffects()
{
	UGameplayStatics::SpawnEmitterAtLocation(this, PickUpFX, GetActorLocation());
}

// Called every frame
void AFPSObjectiveActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

//重写actor发生重叠函数
void AFPSObjectiveActor::NotifyActorBeginOverlap(AActor * OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);

	PlayEffects();

	AFPSCharacter*MyCharacter = Cast<AFPSCharacter>(OtherActor);

	//若是玩家发生重叠，标志位赋值true，摧毁物体
	if (MyCharacter)
	{
		MyCharacter->bIsCarryingSubjective = true;

		////捡起物体后物体消失
		//Destroy();

		//捡起物体后改变mesh材料
		TArray<UStaticMeshComponent*> Components;
		this->GetComponents<UStaticMeshComponent>(Components);
		UStaticMeshComponent* targetComp = Components[0];
		targetComp->SetMaterial(0, M_EmptyObjectiveMaterial);

		//改变人物属性
		TArray<USkeletalMeshComponent*> CharacterComponents;
		MyCharacter->GetComponents<USkeletalMeshComponent>(CharacterComponents);
		USkeletalMeshComponent* targetCharacterComp = CharacterComponents[2];
		targetCharacterComp->SetMaterial(0, M_SecondWeaponMaterial);
	}
}

