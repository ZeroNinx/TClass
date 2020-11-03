// Fill out your copyright notice in the Description page of Project Settings.


#include "TPSPlayerState.h"

//设定名称
void ATPSPlayerState::SetName(FString NewName)
{
	PlayerScore.PlayerName = NewName;
}

//设定分数
void ATPSPlayerState::SetScore(int NewScore)
{
	PlayerScore.PlayerScore = NewScore;
}

//获取玩家信息
FPlayerScore ATPSPlayerState::GetPlayerInfo()
{
	return PlayerScore;
}
