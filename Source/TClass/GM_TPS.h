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
 * ��Ϸģʽ
 */
UCLASS()
class TCLASS_API AGM_TPS : public AGameModeBase
{
	GENERATED_BODY()

protected:

	//�Ƿ���Ϸ��ʼ
	UPROPERTY(BlueprintReadWrite)
	bool bGameStart;

	//�Ƿ���Ϸ����
	UPROPERTY(BlueprintReadWrite)
	bool bGameOver;

	//��ҳ�����
	UPROPERTY(BlueprintReadWrite)
	APlayerStart* PlayerStart;

	//��������
	UPROPERTY(BlueprintReadWrite)
	TArray<int> PlayerScore;

	//��ɱ����
	UPROPERTY(BlueprintReadWrite)
	TArray<int> PlayerKills;

	//��������
	UPROPERTY(BlueprintReadWrite)
	TArray<int> PlayerDeaths;

	//��ʱ�����
	FTimerHandle GameReadyTimerHandle;

	//��Ϸ׼������ʱ
	UPROPERTY(BlueprintReadWrite)
	int GameReadyCounter;

public:

	//��ʼ����Ϸ
	void InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage) override;

	//�������
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void RespawnPlayerEvent(APlayerController* PlayerController);

	//������Ϸ��ʼ
	UFUNCTION(BlueprintCallable)
	void GameReady();

	//�����㲥
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void ScoreMulticast();

	//��Ϸ׼���㲥
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void GameReadyMultiCast();

	//��Ϸ��ʼ
	UFUNCTION(BlueprintNativeEvent,BlueprintCallable)
	void GameStart();

	//��Ϸ׼����ʱ��
	void GameReadyTimerTick();
};
