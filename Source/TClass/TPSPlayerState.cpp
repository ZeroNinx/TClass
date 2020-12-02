// Fill out your copyright notice in the Description page of Project Settings.


#include "TPSPlayerState.h"

//�趨����
void ATPSPlayerState::SetName(FString NewName)
{
	PlayerScore.PlayerName = NewName;
}

//�趨����
void ATPSPlayerState::SetScore(int NewScore)
{
	PlayerScore.PlayerScore = NewScore;
}

//�趨��ɱ
void ATPSPlayerState::SetKill(int NewKill)
{
	PlayerScore.Kill = NewKill;
}

//�趨����
void ATPSPlayerState::SetDied(int NewDied)
{
	PlayerScore.Died = NewDied;
}

//��ȡ�����Ϣ
FPlayerScore ATPSPlayerState::GetPlayerInfo()
{
	return PlayerScore;
}
