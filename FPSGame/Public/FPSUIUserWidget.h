// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "FPSUIUserWidget.generated.h"

class UButton;
class AFPSGameMode;
/**
 *
 */
UCLASS()
class FPSGAME_API UFPSUIUserWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "UI")
		UButton* Button_PlayAgain;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "UI")
		UButton* Button_NextLevel;

	//��ǰgamemode
	AFPSGameMode*GM;

public:
	//��д��ʼ���������÷������ڳ�ʼ��ʱ����
	virtual bool Initialize() override;

	//�Զ��� ��ʼ���ؼ�����
	void Init();

	UFUNCTION()
		void PlayAgainClick();

	UFUNCTION()
		void NextLevelClick();
};