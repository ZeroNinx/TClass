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
	TArray<APlayerStart*> PlayerStarts;

	//��������
	UPROPERTY(BlueprintReadWrite)
	TArray<int> PlayerScore;

	//��ɱ����
	UPROPERTY(BlueprintReadWrite)
	TArray<int> PlayerKills;

	//��������
	UPROPERTY(BlueprintReadWrite)
	TArray<int> PlayerDeaths;

	//��Ϸ׼����ʱ�����
	FTimerHandle GameReadyTimerHandle;

	//��Ϸ׼������ʱ
	UPROPERTY(BlueprintReadWrite)
	int GameReadyCounter;

	//��Ϸʱ�䶨ʱ�����
	FTimerHandle GameplayTimerHandle;

	//��Ϸʱ�䵹��ʱ
	UPROPERTY(BlueprintReadWrite)
	int GameplayCounter;

public:

	//��ʼ����Ϸ
	void InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage) override;

	//�������
	UFUNCTION(Client,Reliable, BlueprintCallable)
	void RespawnPlayerEvent(AController* Controller);

	//������Ϸ��ʼ
	UFUNCTION(BlueprintCallable)
	void GameReady();

	//�����㲥
	UFUNCTION(Server,Reliable, BlueprintCallable)
	void ScoreMulticast();

	//��ɱ�㲥
	UFUNCTION(NetMulticast, Reliable, BlueprintCallable)
	void KillMulticast();

	//��Ϸ׼���㲥
	UFUNCTION(NetMulticast, Reliable, BlueprintCallable)
	void GameReadyMultiCast();

	//��Ϸ��ʼ�㲥
	UFUNCTION(NetMulticast, Reliable, BlueprintCallable)
	void GameplayMultiCast();

	//��Ϸ��ʼ
	UFUNCTION(NetMulticast,Reliable,BlueprintCallable)
	void GameStart();

	//��Ϸ����
	UFUNCTION(NetMulticast,Reliable)
	void GameOver();

	//��Ϸ׼����ʱ��
	void GameReadyTimerTick();

	//��Ϸ���̼�ʱ��
	void GameplayTimerTick();
};
