// Fill out your copyright notice in the Description page of Project Settings.


#include "TPSPlayerController.h"

//玩家本地登录
void ATPSPlayerController::ClientPostLogin_Implementation()
{

	//UKismetSystemLibrary::PrintString(this, TEXT("Client Post Login"));

	//初始化参数
	TPSPlayerState = Cast<ATPSPlayerState>(PlayerState);

	//初始化界面
	SetupUMG();

	//初始化玩家位置
	PlayerRestart();

	//设置输入模式仅游戏
	UWidgetBlueprintLibrary::SetInputMode_GameOnly(this);

}

//玩家重生
void ATPSPlayerController::PlayerRestart()
{
	AGM_TPS* GameMode = Cast<AGM_TPS>(UGameplayStatics::GetGameMode(GetWorld()));
	if (GameMode)
		GameMode->RespawnPlayerEvent(this);
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
		UKismetSystemLibrary::PrintString(this,TEXT("UMG_TPS Load Failed..."));
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
		UKismetSystemLibrary::PrintString(this, TEXT("UMG_Control Load Failed..."));
	}
}

//设定分数
void ATPSPlayerController::SetScore_Implementation(int Score)
{
	if(TPSPlayerState)
		TPSPlayerState->SetScore(Score);
	UMG_TPS->SetScore(Score);
}

//设定击杀
void ATPSPlayerController::SetKill_Implementation(int Kill)
{
	if(TPSPlayerState)
		TPSPlayerState->SetKill(Kill);
	UMG_TPS->SetKill(Kill);
}

//设定准备时间
void ATPSPlayerController::SetReadyTime_Implementation(int Time)
{
	UMG_TPS->SetReadyTime(Time);
}

//设定游戏时间
void ATPSPlayerController::SetGameplayTime_Implementation(int Time)
{
	UMG_TPS->SetGameplayTime(Time);
}

//设定游戏结束
void ATPSPlayerController::SetGameOver_Implementation(int Score, int Kill, int Die)
{
	UMG_TPS->SetGameOver(Score, Kill, Die);
}
