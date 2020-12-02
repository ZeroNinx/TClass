// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TimerManager.h"
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
	APlayerStart* PlayerStart;

	//分数数组
	UPROPERTY(BlueprintReadWrite)
	TArray<int> PlayerScore;

	//击杀数组
	UPROPERTY(BlueprintReadWrite)
	TArray<int> PlayerKills;

	//死亡数组
	UPROPERTY(BlueprintReadWrite)
	TArray<int> PlayerDeaths;

	//定时器句柄
	FTimerHandle GameReadyTimerHandle;

	//游戏准备倒计时
	UPROPERTY(BlueprintReadWrite)
	int GameReadyCounter;

public:

	//初始化游戏
	void InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage) override;

	//玩家重生
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void RespawnPlayerEvent(APlayerController* PlayerController);

	//多人游戏开始
	UFUNCTION(BlueprintCallable)
	void GameReady();

	//分数广播
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void ScoreMulticast();

	//游戏准备广播
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void GameReadyMultiCast();

	//游戏开始
	UFUNCTION(BlueprintNativeEvent,BlueprintCallable)
	void GameStart();

	//游戏准备计时器
	void GameReadyTimerTick();
};
