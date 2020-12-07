// Fill out your copyright notice in the Description page of Project Settings.


#include "GM_TPS.h"

//��ʼ����Ϸ
void AGM_TPS::InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage)
{
	Super::InitGame(MapName, Options, ErrorMessage);

	//��ϷĬ��ֵ����
	SetActorTickEnabled(false);

	//������
	TSubclassOf<ATPSCharacter> Character_C = LoadClass<ATPSCharacter>(this, TEXT("'/Game/Blueprints/BP_TPSCharacter.BP_TPSCharacter_C'"));
	if (Character_C)
	{
		DefaultPawnClass = Character_C->GetClass();
	}
	PlayerStateClass = ATPSPlayerState::StaticClass();
	PlayerControllerClass = ATPSPlayerController::StaticClass();
	
	//��Ϸ��ֵ��ʼ��
	bGameStart = false;
	bGameOver = false;
	GameReadyCounter = 3;
	GameplayCounter = 10;
	PlayerScore.Init(0, 1);//Ϊ������Ϸ������ϰģʽ

	//�������������ص�
	TArray<AActor*> Starts;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), APlayerStart::StaticClass(), Starts);
	for (int i = 0; i < Starts.Num(); i++)
	{
		APlayerStart* PlayerStart = Cast<APlayerStart>(Starts[i]);
		if (PlayerStart)
		{
			if (PlayerStart->PlayerStartTag.IsEqual(FName("Player1")))
			{
				PlayerStarts.Insert(PlayerStart, 0);
			}
			else
			{
				PlayerStarts.Insert(PlayerStart, 1);
			}

		}
	}
}

//��̨��¼
void AGM_TPS::PostLogin(APlayerController* NewPlayer)
{
	//���ӵ��Ȩ������Ϸδ��ʼ
	if (HasAuthority()&&!bGameStart)
	{
		//�ͻ��˵�¼
		ATPSPlayerController* Controller = Cast<ATPSPlayerController>(NewPlayer);
		Controller->ClientPostLogin();

		//�������������ڵ���2����Ϸ׼����ʼ
		if (GetNumPlayers() >= 2)
		{
			GameReady();
			UKismetSystemLibrary::PrintString(this, TEXT("Game Ready"));
		}
	}
}

//��Ϸ׼��
void AGM_TPS::GameReady()
{
	//��ʼ����Ϸ����
	int NumPlayers = GetNumPlayers();
	PlayerScore.Init(0, NumPlayers);
	PlayerKills.Init(0, NumPlayers);
	PlayerDeaths.Init(0, NumPlayers);

	//�ͻ��˹㲥����
	ScoreMulticast();
	KillMulticast();

	//�趨��Ϸ׼����ʱ��
	GetWorldTimerManager().SetTimer(GameReadyTimerHandle, this, &AGM_TPS::GameReadyTimerTick, 1.0f, true);

}

//��Ϸ��ʼ
void AGM_TPS::GameStart_Implementation()
{
	bGameStart = true;

	//�㲥��Ϸ��ʼ
	GameplayMultiCast();

	//�趨��Ϸ׼����ʱ��
	GetWorldTimerManager().SetTimer(GameplayTimerHandle, this, &AGM_TPS::GameplayTimerTick, 1.0f, true);
}

//��Ϸ����
void AGM_TPS::GameOver_Implementation()
{
	bGameOver = true;

	//������ҹ㲥��Ϸ���
	int NumPlayers = GetNumPlayers();
	for (int i = 0; i < NumPlayers; i++)
	{
		ATPSPlayerController* Controller = Cast<ATPSPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), i));
		if (i == 0)
			Controller->SetGameOver(PlayerScore[0], PlayerKills[0], PlayerKills[1]);
		else Controller->SetGameOver(PlayerScore[1], PlayerKills[1], PlayerKills[0]);
	}
}

//��ҵ÷�
void AGM_TPS::AddScore_Implementation(AController* Controller, int Score)
{
	//���˺Ͷ�����Ϸʱ���Լ������
	if (!bGameOver && (GetNumPlayers() == 1 || bGameStart))
	{
		//��ȡ��ұ��
		int Index = UGameplayStatics::GetGameState(this)->PlayerArray.Find(Controller->PlayerState);

		//��ӵ÷�
		PlayerScore[Index] += Score;

		//�㲥��ɱ���
		ScoreMulticast();
	}
}

//��һ�ɱ
void AGM_TPS::AddKill_Implementation(AController* Killer)
{
	//���˺Ͷ�����Ϸʱ���Լ����ɱ
	if (!bGameOver && (GetNumPlayers() == 1 || bGameStart))
	{
		//��ȡ��ұ��
		int Index = UGameplayStatics::GetGameState(this)->PlayerArray.Find(Killer->PlayerState);

		//��ӻ�ɱ������
		if (Index == 0)
		{
			PlayerKills[0]++;
			PlayerDeaths[1]++;
		}
		else
		{
			PlayerKills[1]++;
			PlayerDeaths[0]++;
		}

		//�㲥��ɱ���
		KillMulticast();
	}
}

//�����㲥
void AGM_TPS::ScoreMulticast_Implementation()
{
	//������ҹ㲥����
	int NumPlayers = GetNumPlayers();
	for (int i = 0; i < NumPlayers; i++)
	{
		ATPSPlayerController* Controller = Cast<ATPSPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), i));
		Controller->SetScore(PlayerScore[i]);
	}
}

//��ɱ�㲥
void AGM_TPS::KillMulticast_Implementation()
{
	//������ҹ㲥��ɱ
	int NumPlayers = GetNumPlayers();
	for (int i = 0; i < NumPlayers; i++)
	{
		ATPSPlayerController* Controller = Cast<ATPSPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), i));
		Controller->SetKill(PlayerKills[i]);
	}
}

//��Ϸ׼���㲥
void AGM_TPS::GameReadyMultiCast_Implementation()
{
	//������ҹ㲥׼��ʱ��
	int NumPlayers = GetNumPlayers();
	for (int i = 0; i < NumPlayers; i++)
	{
		ATPSPlayerController* Controller = Cast<ATPSPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), i));
		Controller->SetReadyTime(GameReadyCounter);
	}
}

//��Ϸ��ʼ�㲥
void AGM_TPS::GameplayMultiCast_Implementation()
{
	//������ҹ㲥׼��ʱ��
	int NumPlayers = GetNumPlayers();
	for (int i = 0; i < NumPlayers; i++)
	{
		ATPSPlayerController* Controller = Cast<ATPSPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), i));
		Controller->SetGameplayTime(GameplayCounter);
	}
}

//�趨�������
void AGM_TPS::RespawnPlayerEvent_Implementation(AController* Controller)
{
	//�����Ҵ��ھ�����
	APawn* Pawn = Controller->GetPawn();
	if (Pawn)
	{
		Pawn->Destroy();
	}

	//��ȡ��ͼ���������
	TSubclassOf<ATPSCharacter> BP_Character_C = LoadClass<ATPSCharacter>(this, TEXT("/Game/Blueprints/BP_TPSCharacter.BP_TPSCharacter_C"));
	
	if (BP_Character_C)
	{
		//��ȡ��ұ��
		int Index = UGameplayStatics::GetGameState(this)->PlayerArray.Find(Controller->PlayerState);

		//���������������
		ATPSCharacter* newPawn = GetWorld()->SpawnActor<ATPSCharacter>(BP_Character_C, PlayerStarts[Index]->GetActorTransform());
		
		//��Ϊ����
		if (newPawn)
		{
			Controller->Possess(newPawn);
			
		}
		else
			UKismetSystemLibrary::PrintString(this, TEXT("Spawn Failed"));
	}
	else
	{
		UKismetSystemLibrary::PrintString(this, TEXT("BP Not Found"));
	}

}

//��Ϸ׼����ʱ��
void AGM_TPS::GameReadyTimerTick()
{
	//UKismetSystemLibrary::PrintString(GetWorld(), TEXT("GameReady...")+FString::FromInt(GameReadyCounter));

	//�㲥ʱ��
	GameReadyMultiCast();	
	if (GameReadyCounter <= 0)
	{
		GetWorldTimerManager().ClearTimer(GameReadyTimerHandle);
		
		//��Ϸ��ʼ
		GameStart();
	}
	else GameReadyCounter--;
}

//��Ϸʱ���ʱ��
void AGM_TPS::GameplayTimerTick()
{
	UKismetSystemLibrary::PrintString(GetWorld(), TEXT("GameTicking...") + FString::FromInt(GameplayCounter));

	//�㲥ʱ��
	GameplayMultiCast();
	if (GameplayCounter <= 0)
	{
		GetWorldTimerManager().ClearTimer(GameplayTimerHandle);

		//��Ϸ����
		GameOver();
	}
	else GameplayCounter--;

}
