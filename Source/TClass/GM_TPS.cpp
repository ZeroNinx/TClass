// Fill out your copyright notice in the Description page of Project Settings.


#include "GM_TPS.h"

//��ʼ����Ϸ
void AGM_TPS::InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage)
{
	Super::InitGame(MapName, Options, ErrorMessage);

	//��Ϸ��ֵ��ʼ��
	bGameStart = false;
	bGameOver = false;
	GameReadyCounter = 3;
}

//������Ϸ��ʼ
void AGM_TPS::GameReady()
{
	//��ȡ�������
	int PlayerNum = UGameplayStatics::GetGameState(GetWorld())->PlayerArray.Num();

	//�������㲢�㲥
	PlayerScore.Init(PlayerNum, 0);
	ScoreMulticast();

	//�趨��Ϸ׼����ʱ��
	GetWorldTimerManager().SetTimer(GameReadyTimerHandle, this, &AGM_TPS::GameReadyTimerTick, 1.0f, true);

}

//�����㲥
void AGM_TPS::ScoreMulticast_Implementation()
{

}

//��Ϸ׼���㲥
void AGM_TPS::GameReadyMultiCast_Implementation()
{

}

//��Ϸ��ʼ
void AGM_TPS::GameStart_Implementation()
{

}

//�趨�������
void AGM_TPS::RespawnPlayerEvent_Implementation(APlayerController* PlayerController)
{

}

//��Ϸ׼����ʱ��
void AGM_TPS::GameReadyTimerTick()
{
	UKismetSystemLibrary::PrintString(GetWorld(), TEXT("GameReady..."));

	//�㲥ʱ��
	GameReadyMultiCast();	
	if (GameReadyCounter <= 0)
	{
		GetWorldTimerManager().ClearTimer(GameReadyTimerHandle);
		
		//��Ϸ��ʼ
		GameStart();
	}
	else
		GameReadyCounter--;
}
