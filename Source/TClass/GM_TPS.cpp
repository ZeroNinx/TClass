// Fill out your copyright notice in the Description page of Project Settings.


#include "GM_TPS.h"

//初始化游戏
void AGM_TPS::InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage)
{
	Super::InitGame(MapName, Options, ErrorMessage);

	//游戏数值初始化
	bGameStart = false;
	bGameOver = false;
	GameReadyCounter = 3;
}

//多人游戏开始
void AGM_TPS::GameReady()
{
	//获取玩家数量
	int PlayerNum = UGameplayStatics::GetGameState(GetWorld())->PlayerArray.Num();

	//分数清零并广播
	PlayerScore.Init(PlayerNum, 0);
	ScoreMulticast();

	//设定游戏准备定时器
	GetWorldTimerManager().SetTimer(GameReadyTimerHandle, this, &AGM_TPS::GameReadyTimerTick, 1.0f, true);

}

//分数广播
void AGM_TPS::ScoreMulticast_Implementation()
{

}

//游戏准备广播
void AGM_TPS::GameReadyMultiCast_Implementation()
{

}

//游戏开始
void AGM_TPS::GameStart_Implementation()
{

}

//设定玩家重生
void AGM_TPS::RespawnPlayerEvent_Implementation(APlayerController* PlayerController)
{

}

//游戏准备计时器
void AGM_TPS::GameReadyTimerTick()
{
	UKismetSystemLibrary::PrintString(GetWorld(), TEXT("GameReady..."));

	//广播时间
	GameReadyMultiCast();	
	if (GameReadyCounter <= 0)
	{
		GetWorldTimerManager().ClearTimer(GameReadyTimerHandle);
		
		//游戏开始
		GameStart();
	}
	else
		GameReadyCounter--;
}
