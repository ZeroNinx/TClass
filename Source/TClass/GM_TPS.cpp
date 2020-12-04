// Fill out your copyright notice in the Description page of Project Settings.


#include "GM_TPS.h"

//初始化游戏
void AGM_TPS::InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage)
{
	Super::InitGame(MapName, Options, ErrorMessage);

	//游戏数值初始化
	bGameStart = false;
	bGameOver = false;
	GameReadyCounter = 3;
	GameplayCounter = 10;
}

//游戏准备
void AGM_TPS::GameReady()
{
	//初始化游戏数据
	int NumPlayers = GetNumPlayers();
	PlayerScore.Init(0, NumPlayers);
	PlayerKills.Init(0, NumPlayers);

	//客户端广播数据
	ScoreMulticast();
	KillMulticast();

	//设定游戏准备定时器
	GetWorldTimerManager().SetTimer(GameReadyTimerHandle, this, &AGM_TPS::GameReadyTimerTick, 1.0f, true);

}

//游戏开始
void AGM_TPS::GameStart_Implementation()
{
	bGameStart = true;

	//广播游戏开始
	GameplayMultiCast();

	//设定游戏准备定时器
	GetWorldTimerManager().SetTimer(GameplayTimerHandle, this, &AGM_TPS::GameplayTimerTick, 1.0f, true);
}



//分数广播
void AGM_TPS::ScoreMulticast_Implementation()
{
	//遍历玩家广播分数
	int NumPlayers = GetNumPlayers();
	for (int i = 0; i < NumPlayers; i++)
	{
		ATPSPlayerController* Controller = Cast<ATPSPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), i));
		Controller->SetScore(PlayerScore[i]);
	}
}

//击杀广播
void AGM_TPS::KillMulticast_Implementation()
{
	//遍历玩家广播击杀
	int NumPlayers = GetNumPlayers();
	for (int i = 0; i < NumPlayers; i++)
	{
		ATPSPlayerController* Controller = Cast<ATPSPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), i));
		Controller->SetKill(PlayerKills[i]);
	}
}

//游戏准备广播
void AGM_TPS::GameReadyMultiCast_Implementation()
{
	//遍历玩家广播准备时间
	int NumPlayers = GetNumPlayers();
	for (int i = 0; i < NumPlayers; i++)
	{
		ATPSPlayerController* Controller = Cast<ATPSPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), i));
		Controller->SetReadyTime(GameReadyCounter);
	}
}


//游戏开始广播
void AGM_TPS::GameplayMultiCast_Implementation()
{
	//遍历玩家广播准备时间
	int NumPlayers = GetNumPlayers();
	for (int i = 0; i < NumPlayers; i++)
	{
		ATPSPlayerController* Controller = Cast<ATPSPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), i));
		Controller->SetGameplayTime(GameplayCounter);
	}
}

//游戏结束
void AGM_TPS::GameOver_Implementation()
{
	//遍历玩家广播准备时间
	int NumPlayers = GetNumPlayers();
	for (int i = 0; i < NumPlayers; i++)
	{
		ATPSPlayerController* Controller = Cast<ATPSPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), i));
		if (i == 0)
			Controller->SetGameOver(PlayerScore[0], PlayerKills[0], PlayerKills[1]);
		else Controller->SetGameOver(PlayerScore[1], PlayerKills[1], PlayerKills[0]);
	}
}

//设定玩家重生
void AGM_TPS::RespawnPlayerEvent_Implementation(AController* Controller)
{
	//如果玩家存在就销毁
	APawn* Pawn = Controller->GetPawn();
	if (Pawn)
	{
		Pawn->Destroy();
	}

	//读取蓝图，重生玩家
	TSubclassOf<ATPSCharacter> BP_Character_C = LoadClass<ATPSCharacter>(this, TEXT("/Game/Blueprints/BP_TPSCharacter.BP_TPSCharacter_C"));
	
	if (BP_Character_C)
	{
		//获取重生点
		int Index = UGameplayStatics::GetGameState(this)->PlayerArray.Find(Controller->PlayerState);

		//重生玩家
		ATPSCharacter* newPawn = GetWorld()->SpawnActor<ATPSCharacter>(BP_Character_C, PlayerStarts[Index]->GetActorTransform());
		
		//设为控制
		if(newPawn)
			Controller->Possess(newPawn);
		else
			UKismetSystemLibrary::PrintString(this, TEXT("Spawn Failed"));
	}
	else
	{
		UKismetSystemLibrary::PrintString(this, TEXT("BP Not Found"));
	}

}

//游戏准备计时器
void AGM_TPS::GameReadyTimerTick()
{
	//UKismetSystemLibrary::PrintString(GetWorld(), TEXT("GameReady...")+FString::FromInt(GameReadyCounter));

	//广播时间
	GameReadyMultiCast();	
	if (GameReadyCounter <= 0)
	{
		GetWorldTimerManager().ClearTimer(GameReadyTimerHandle);
		
		//游戏开始
		GameStart();
	}
	else GameReadyCounter--;
}

//游戏时间计时器
void AGM_TPS::GameplayTimerTick()
{
	UKismetSystemLibrary::PrintString(GetWorld(), TEXT("GameTicking...") + FString::FromInt(GameplayCounter));

	//广播时间
	GameplayMultiCast();
	if (GameplayCounter <= 0)
	{
		GetWorldTimerManager().ClearTimer(GameplayTimerHandle);

		//游戏结束
		GameOver();
	}
	else GameplayCounter--;

}
