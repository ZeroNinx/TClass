// Fill out your copyright notice in the Description page of Project Settings.


#include "GM_MainMenu.h"


//开始游戏
void AGM_MainMenu::StartPlay()
{
	//获取游戏实例
	GameInstance = Cast<UTClassGameInstance>(GetGameInstance());

	//获取玩家控制器
	PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);

	//注册玩家控制器
	GameInstance->AssignPlayerController(PlayerController);

	//查找菜单蓝图
	TSubclassOf<UUMG_MainMenu> MainMenuClass = LoadClass<UUMG_MainMenu>(this,TEXT("/Game/Widgets/BP_UMG_MainMenu.BP_UMG_MainMenu_C"));
	if (MainMenuClass)
	{
		//创建主菜单
		MainMenu = CreateWidget<UUMG_MainMenu>(GetWorld(), MainMenuClass);
		//添加到窗口
		MainMenu->AddToViewport();

		//显示并启用鼠标
		PlayerController->bShowMouseCursor = true;
		PlayerController->bEnableClickEvents = true;
		PlayerController->bEnableMouseOverEvents = true;

	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("MainMenu Load Failed..."));
	}
	
}
