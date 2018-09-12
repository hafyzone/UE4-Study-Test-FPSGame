// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LaunchPad.generated.h"

class UBoxComponent;
UCLASS()

class FPSGAME_API ALaunchPad : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALaunchPad();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, Category = "Components")
		UBoxComponent*LaunchPadComp;

	//暴露弹射两个参数给蓝图
	UPROPERTY(EditInstanceOnly, Category = "LaunchPad")
		float LaunchStrength;

	UPROPERTY(EditInstanceOnly, Category = "LaunchPad")
		float LaunchPitchAngle;

	//声明碰撞弹跳效果函数
	void LauchEffects();

	UPROPERTY(EditDefaultsOnly, category = "Effects")
		UParticleSystem* LauchFX;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//重写actor重写函数
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;
	
};
