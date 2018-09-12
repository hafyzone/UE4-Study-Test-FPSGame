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

//�������ʱ����
void AFPSGameMode::CompleteMission(APawn* InstigatorPawn)
{
	CurrentLevelName = UGameplayStatics::GetCurrentLevelName(this);

	if (InstigatorPawn)
	{
		//������Ҳ�������ָ��
		InstigatorPawn->DisableInput(nullptr);

		//�ж��Ƿ����ø��ӽ�
		if (SpectatingViewpointClass)
		{
			TArray<AActor*>ReturnActors;
			UGameplayStatics::GetAllActorsOfClass(this, SpectatingViewpointClass, ReturnActors);

			//�ж��Ƿ���ڶ��actor
			if (ReturnActors.Num() > 0)
			{
				AActor *NewTargetView = ReturnActors[0];

				APlayerController* PC = Cast<APlayerController>(InstigatorPawn->GetController());

				//Ϊ����������ӽǼ��ӽ�ת��Ч��
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

	//���ñ�¶����ͼ������¼�
	OnMissionComplete(InstigatorPawn);

	//UButton*btn = Cast<UButton>(GetWidgetFromName("Button_199"));

	//TxtDebugMsg = Cast<UTextBlock>(GetWidgetFromName(TEXT("WBP_GameOver")));

	

}

void AFPSGameMode::PlayerDead(APawn* InstigatorPawn)
{
	//������Ҳ�������ָ��
	InstigatorPawn->DisableInput(nullptr);

	//���ñ�¶����ͼ�������¼�
	OnPawnDead(InstigatorPawn);
}

