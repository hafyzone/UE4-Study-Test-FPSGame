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

	//任务完成时触发
	void CompleteMission(APawn* InstigatorPawn);

	//玩家死亡时触发
	void PlayerDead(APawn* InstigatorPawn);

	//暴露完成事件给蓝图，在蓝图配置相关功能
	UFUNCTION(BlueprintImplementableEvent, Category = "GameMode")
		void OnMissionComplete(APawn* InstigatorPawn);

	//暴露死亡事件给蓝图，在蓝图配置相关功能
	UFUNCTION(BlueprintImplementableEvent, Category = "GameMode")
		void OnPawnDead(APawn* InstigatorPawn);

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "LevelName")
		FString CurrentLevelName;
};



