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

	//当前gamemode
	AFPSGameMode*GM;

public:
	//重写初始化方法，该方法会在初始化时调用
	virtual bool Initialize() override;

	//自定义 初始化控件引用
	void Init();

	UFUNCTION()
		void PlayAgainClick();

	UFUNCTION()
		void NextLevelClick();
};