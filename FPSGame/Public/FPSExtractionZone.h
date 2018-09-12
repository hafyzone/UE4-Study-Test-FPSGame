// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FPSExtractionZone.generated.h"


class UBoxComponent;

UCLASS()
class FPSGAME_API AFPSExtractionZone : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AFPSExtractionZone();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, Category = "Components")
		UBoxComponent*OverlapComp;

	//暴露弹射两个参数给蓝图
	UPROPERTY(EditInstanceOnly, Category = "LaunchPad")
		float LaunchStrength;

	UPROPERTY(EditInstanceOnly, Category = "LaunchPad")
		float LaunchPitchAngle;

	//声明关卡区域碰撞效果函数
	void BoxPlayEffects();

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//重写actor重写函数
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

	//定义事件变量
	float RunningTime;
};
