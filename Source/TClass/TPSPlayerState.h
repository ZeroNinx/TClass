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
	FString Name="";

	//玩家得分
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int Score=0;

	//玩家击杀
	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	int Kill=0;

	//玩家死亡
	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	int Died=0;
};


/**
 * 玩家状态
 */
UCLASS()
class TCLASS_API ATPSPlayerState : public APlayerState
{
	GENERATED_BODY()

public:

	ATPSPlayerState();
	
	//设定名称
	UFUNCTION(BlueprintCallable)
	void SetName(FString NewName);

	//设定分数
	UFUNCTION(BlueprintCallable)
	void SetScore(int NewScore);

	//设定击杀
	UFUNCTION(BlueprintCallable)
	void SetKill(int NewKill);

	//设定死亡
	UFUNCTION(BlueprintCallable)
	void SetDied(int NewDied);

	//获取信息
	UFUNCTION(BlueprintCallable)
	FPlayerScore GetPlayerInfo();

protected:

	//玩家得分
	UPROPERTY(BlueprintReadWrite)
	FPlayerScore PlayerScore;

	//玩家生命值
	UPROPERTY(BlueprintReadWrite)
	int Life = 100;

};
