// Fill out your copyright notice in the Description page of Project Settings.


#include "TPSPlayerController.h"

//玩家本地登录
void ATPSPlayerController::ClientPostLogin_Implementation()
{

	//初始化界面
	SetupUMG();

	//设置输入模式仅游戏
	UWidgetBlueprintLibrary::SetInputMode_GameOnly(this);

}

//初始化UMG界面
void ATPSPlayerController::SetupUMG()
{
	//查找状态界面
	TSubclassOf<UUMG_TPS> UMG_TPS_C = LoadClass<UUMG_TPS>(this, TEXT("/Game/Widgets/BP_UMG_TPS.BP_UMG_TPS_C"));
	if (UMG_TPS_C)
	{
		//创建界面
		UMG_TPS = CreateWidget<UUMG_TPS>(this, UMG_TPS_C);
		//添加到窗口
		UMG_TPS->AddToViewport();
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("UMG_TPS Load Failed..."));
	}

	//查找界面蓝图
	TSubclassOf<UUMG_Control> UMG_Control_C = LoadClass<UUMG_Control>(this, TEXT("/Game/Widgets/BP_UMG_Control.BP_UMG_Control_C"));
	if (UMG_Control_C)
	{
		//创建主菜单
		UMG_Control = CreateWidget<UUMG_Control>(this, UMG_Control_C);
		//添加到窗口
		UMG_Control->AddToViewport();
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("UMG_Control Load Failed..."));
	}
}
