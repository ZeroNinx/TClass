// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GM_TPS.h"
#include "UMG_TPS.h"
#include "UMG_Control.h"
#include "TPSPlayerState.h"
#include "Engine/GameInstance.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/PlayerController.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "TPSPlayerController.generated.h"

/**
 * 玩家控制器
 */
UCLASS()
class TCLASS_API ATPSPlayerController : public APlayerController
{
	GENERATED_BODY()

protected:

	UPROPERTY(BlueprintReadWrite)
	ATPSPlayerState* TPSPlayerState;

	//状态界面
	UPROPERTY(BlueprintReadWrite)
	UUMG_TPS* UMG_TPS;
	
	//操控界面
	UPROPERTY(BlueprintReadWrite)
	UUMG_Control* UMG_Control;

public:

	//玩家本地登陆
	UFUNCTION(Client,Reliable,BlueprintCallable)
	void ClientPostLogin();

	//玩家重生
	UFUNCTION(BlueprintCallable)
	void PlayerRestart();

	//初始化UMG界面
	UFUNCTION(BlueprintCallable)
	void SetupUMG();

	//设定分数
	UFUNCTION(Client,Reliable,BlueprintCallable)
	void SetScore(int Score);

	//设定击杀
	UFUNCTION(Client, Reliable, BlueprintCallable)
	void SetKill(int Kill);

	//设定准备时间
	UFUNCTION(Client, Reliable, BlueprintCallable)
	void SetReadyTime(int Time);

	//设定游戏时间
	UFUNCTION(Client, Reliable, BlueprintCallable)
	void SetGameplayTime(int Time);

	//设定分数
	UFUNCTION(Client, Reliable, BlueprintCallable)
	void SetGameOver(int Score,int Kill,int Die);
};
