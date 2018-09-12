// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "FPSGameMode.generated.h"

UCLASS()
class AFPSGameMode : public AGameModeBase
{
	GENERATED_BODY()

protected:

	UPROPERTY(EditDefaultsOnly, Category = "Spectating")
		TSubclassOf<AActor> SpectatingViewpointClass;

public:

	AFPSGameMode();

	class UButton*btn;

	//�������ʱ����
	void CompleteMission(APawn* InstigatorPawn);

	//�������ʱ����
	void PlayerDead(APawn* InstigatorPawn);

	//��¶����¼�����ͼ������ͼ������ع���
	UFUNCTION(BlueprintImplementableEvent, Category = "GameMode")
		void OnMissionComplete(APawn* InstigatorPawn);

	//��¶�����¼�����ͼ������ͼ������ع���
	UFUNCTION(BlueprintImplementableEvent, Category = "GameMode")
		void OnPawnDead(APawn* InstigatorPawn);

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "LevelName")
		FString CurrentLevelName;
};



