// Fill out your copyright notice in the Description page of Project Settings.

#include "FPSUIUserWidget.h"
#include "Blueprint/UserWidget.h"
#include "Button.h"
#include "FPSGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "Components/Widget.h"

bool UFPSUIUserWidget::Initialize()
{
	if (!Super::Initialize())
	{
		return false;
	}

	Init();
	return true;
}

void UFPSUIUserWidget::Init()
{
	GM = Cast<AFPSGameMode>(GetWorld()->GetAuthGameMode());

	if (GM)
	{
		/** ��ʼ����Ϸ��ʼ��ť GetWidgetFromName ��ʵ��������ͼ�л�ȡ��Ӧ���ֵĿؼ�*/
		Button_PlayAgain = Cast<UButton>(GetWidgetFromName("Button_PlayAgain1"));

		if (Button_PlayAgain)
		{
			Button_PlayAgain->OnClicked.AddDynamic(this, &UFPSUIUserWidget::PlayAgainClick);
		}

		/** ��ʼ����Ϸע�ᰴť */
		Button_NextLevel = Cast<UButton>(GetWidgetFromName("Button_NextLevel1"));

		if (Button_NextLevel)
		{
			if (GM->CurrentLevelName == "FirstPersonExampleMap_2")
			{
				Button_NextLevel->SetVisibility(ESlateVisibility::Hidden);
				return;
			}
			Button_NextLevel->OnClicked.AddDynamic(this, &UFPSUIUserWidget::NextLevelClick);
		}
	}
}

//playagain��ť����¼�
void UFPSUIUserWidget::PlayAgainClick()
{
	FName levelName = FName(*GM->CurrentLevelName);

	UGameplayStatics::OpenLevel(this, levelName);
}

//NextLevel��ť����¼�
void UFPSUIUserWidget::NextLevelClick()
{

	FName levelName = "FirstPersonExampleMap_2";

	UGameplayStatics::OpenLevel(this, levelName);
}
