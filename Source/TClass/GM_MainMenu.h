// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "CoreMinimal.h"
#include "Widgets/SWidget.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/GameModeBase.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Kismet/KismetSystemLibrary.h"

#include "TClassGameInstance.h"
#include "UMG_MainMenu.h"

#include "GM_MainMenu.generated.h"

/**
 * 主菜单游戏模式
 */
UCLASS()
class TCLASS_API AGM_MainMenu : public AGameModeBase
{
	GENERATED_BODY()

public:
	
	//开始游戏
	void StartPlay() override;

protected:

	//游戏实例
	UTClassGameInstance* GameInstance;

	//玩家控制器
	APlayerController* PlayerController;

	//主菜单界面
	UUMG_MainMenu* MainMenu;
};
