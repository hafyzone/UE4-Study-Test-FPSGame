// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FPSObjectiveActor.generated.h"

class USphereComponent;

UCLASS()
class FPSGAME_API AFPSObjectiveActor : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AFPSObjectiveActor();

protected:

	//�����Ԫ�ر�¶����ͼ
	UPROPERTY(VisibleAnywhere, category = "Components")
		UStaticMeshComponent *MeshComp;

	UPROPERTY(VisibleAnywhere, category = "Components")
		USphereComponent* SphereComp;

	UPROPERTY(EditDefaultsOnly, category = "Effects")
		UParticleSystem* PickUpFX;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ChangeTransparentalbe")
		UMaterial* M_SecondWeaponMaterial;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ChangeTransparentalbe")
		UMaterial* M_EmptyObjectiveMaterial;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//������ײЧ������
	void PlayEffects();

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//��дactor��д����
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

};
