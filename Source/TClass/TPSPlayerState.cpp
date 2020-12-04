// Fill out your copyright notice in the Description page of Project Settings.


#include "TPSPlayerState.h"

ATPSPlayerState::ATPSPlayerState()
{
	PlayerScore = FPlayerScore();
}

//�趨����
void ATPSPlayerState::SetName(FString NewName)
{
	PlayerScore.Name = NewName;
}

//�趨����
void ATPSPlayerState::SetScore(int NewScore)
{
	PlayerScore.Score = NewScore;
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
