// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TimerManager.h"
#include "TPSCharacter.h"
#include "TPSPlayerController.h"
#include "GameFramework/PlayerStart.h"
#include "GameFramework/GameModeBase.h"
#include "GameFramework/GameStateBase.h"
#include "GameFramework/PlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetStringLibrary.h"
#include "GM_TPS.generated.h"

/**
 * 游戏模式
 */
UCLASS()
class TCLASS_API AGM_TPS : public AGameModeBase
{
	GENERATED_BODY()

protected:

	//是否游戏开始
	UPROPERTY(BlueprintReadWrite)
	bool bGameStart;

	//是否游戏结束
	UPROPERTY(BlueprintReadWrite)
	bool bGameOver;

	//玩家出生点
	UPROPERTY(BlueprintReadWrite)
	TArray<APlayerStart*> PlayerStarts;

	//分数数组
	UPROPERTY(BlueprintReadWrite)
	TArray<int> PlayerScore;

	//击杀数组
	UPROPERTY(BlueprintReadWrite)
	TArray<int> PlayerKills;

	//死亡数组
	UPROPERTY(BlueprintReadWrite)
	TArray<int> PlayerDeaths;

	//游戏准备定时器句柄
	FTimerHandle GameReadyTimerHandle;

	//游戏准备倒计时
	UPROPERTY(BlueprintReadWrite)
	int GameReadyCounter;

	//游戏时间定时器句柄
	FTimerHandle GameplayTimerHandle;

	//游戏时间倒计时
	UPROPERTY(BlueprintReadWrite)
	int GameplayCounter;

public:

	//初始化游戏
	void InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage) override;

	//玩家重生
	UFUNCTION(Client,Reliable, BlueprintCallable)
	void RespawnPlayerEvent(AController* Controller);

	//多人游戏开始
	UFUNCTION(BlueprintCallable)
	void GameReady();

	//分数广播
	UFUNCTION(Server,Reliable, BlueprintCallable)
	void ScoreMulticast();

	//击杀广播
	UFUNCTION(NetMulticast, Reliable, BlueprintCallable)
	void KillMulticast();

	//游戏准备广播
	UFUNCTION(NetMulticast, Reliable, BlueprintCallable)
	void GameReadyMultiCast();

	//游戏开始广播
	UFUNCTION(NetMulticast, Reliable, BlueprintCallable)
	void GameplayMultiCast();

	//游戏开始
	UFUNCTION(NetMulticast,Reliable,BlueprintCallable)
	void GameStart();

	//游戏结束
	UFUNCTION(NetMulticast,Reliable)
	void GameOver();

	//游戏准备计时器
	void GameReadyTimerTick();

	//游戏进程计时器
	void GameplayTimerTick();
};
