// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UMG_TPS.generated.h"

/**
 * 
 */
UCLASS()
class TCLASS_API UUMG_TPS : public UUserWidget
{
	GENERATED_BODY()

protected:

public:
	
	//设定分数
	UFUNCTION(BlueprintNativeEvent,BlueprintCallable)
	void SetScore(int Score);

	//设定击杀
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void SetKill(int Kill);

	//设定预备时间
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void SetReadyTime(int Time);

	//设定游戏时间
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void SetGameplayTime(int Time);

	//设定游戏结束
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void SetGameOver(int Score,int Kill, int Die);

};
