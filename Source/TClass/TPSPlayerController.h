// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GM_TPS.h"
#include "UMG_TPS.h"
#include "UMG_Control.h"
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

	//初始化UMG界面
	UFUNCTION(BlueprintCallable)
	void SetupUMG();


};
