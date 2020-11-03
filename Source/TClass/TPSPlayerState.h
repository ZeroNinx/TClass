// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "TPSPlayerState.generated.h"

//玩家分数结构体
USTRUCT(BlueprintType)
struct FPlayerScore
{
	GENERATED_BODY()

	//玩家名称
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FString PlayerName;

	//玩家得分
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int PlayerScore;

};


/**
 * 玩家状态
 */
UCLASS()
class TCLASS_API ATPSPlayerState : public APlayerState
{
	GENERATED_BODY()

public:
	
	//设定名称
	UFUNCTION(BlueprintCallable)
	void SetName(FString NewName);

	//设定分数
	UFUNCTION(BlueprintCallable)
	void SetScore(int NewScore);

	//获取信息
	UFUNCTION(BlueprintCallable)
	FPlayerScore GetPlayerInfo();

protected:

	//玩家得分
	UPROPERTY(BlueprintReadWrite)
	FPlayerScore PlayerScore;

};
