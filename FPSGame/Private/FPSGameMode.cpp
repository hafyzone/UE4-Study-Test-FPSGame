// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "FPSGameMode.h"
#include "FPSHUD.h"
#include "FPSCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "Kismet/GameplayStatics.h"
#include "Components/Button.h"

AFPSGameMode::AFPSGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/Blueprints/BP_Player"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = AFPSHUD::StaticClass();
}

//任务完成时触发
void AFPSGameMode::CompleteMission(APawn* InstigatorPawn)
{
	CurrentLevelName = UGameplayStatics::GetCurrentLevelName(this);

	if (InstigatorPawn)
	{
		//设置玩家不能输入指令
		InstigatorPawn->DisableInput(nullptr);

		//判断是否设置该视角
		if (SpectatingViewpointClass)
		{
			TArray<AActor*>ReturnActors;
			UGameplayStatics::GetAllActorsOfClass(this, SpectatingViewpointClass, ReturnActors);

			//判断是否存在多个actor
			if (ReturnActors.Num() > 0)
			{
				AActor *NewTargetView = ReturnActors[0];

				APlayerController* PC = Cast<APlayerController>(InstigatorPawn->GetController());

				//为玩家设置新视角及视角转移效果
				if (PC)
				{
					PC->SetViewTargetWithBlend(NewTargetView, 0.5f, EViewTargetBlendFunction::VTBlend_Cubic);
				}
			}
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("SpectatingViewpointClass is null,please set the value!"))
		}
	}

	//调用暴露给蓝图的完成事件
	OnMissionComplete(InstigatorPawn);

	//UButton*btn = Cast<UButton>(GetWidgetFromName("Button_199"));

	//TxtDebugMsg = Cast<UTextBlock>(GetWidgetFromName(TEXT("WBP_GameOver")));

	

}

void AFPSGameMode::PlayerDead(APawn* InstigatorPawn)
{
	//设置玩家不能输入指令
	InstigatorPawn->DisableInput(nullptr);

	//调用暴露给蓝图的死亡事件
	OnPawnDead(InstigatorPawn);
}

