// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DeadBox.generated.h"

UCLASS()
class FPSGAME_API ADeadBox : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADeadBox();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, Category = "Components")
		class UBoxComponent*OverlapComp;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	//÷ÿ–¥actor÷ÿ–¥∫Ø ˝
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;
};
