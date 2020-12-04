// Fill out your copyright notice in the Description page of Project Settings.


#include "TPSPlayerController.h"

//��ұ��ص�¼
void ATPSPlayerController::ClientPostLogin_Implementation()
{

	//UKismetSystemLibrary::PrintString(this, TEXT("Client Post Login"));

	//��ʼ������
	TPSPlayerState = Cast<ATPSPlayerState>(PlayerState);

	//��ʼ������
	SetupUMG();

	//��ʼ�����λ��
	PlayerRestart();

	//��������ģʽ����Ϸ
	UWidgetBlueprintLibrary::SetInputMode_GameOnly(this);

}

//�������
void ATPSPlayerController::PlayerRestart()
{
	AGM_TPS* GameMode = Cast<AGM_TPS>(UGameplayStatics::GetGameMode(GetWorld()));
	if (GameMode)
		GameMode->RespawnPlayerEvent(this);
}

//��ʼ��UMG����
void ATPSPlayerController::SetupUMG()
{
	//����״̬����
	TSubclassOf<UUMG_TPS> UMG_TPS_C = LoadClass<UUMG_TPS>(this, TEXT("/Game/Widgets/BP_UMG_TPS.BP_UMG_TPS_C"));
	if (UMG_TPS_C)
	{
		//��������
		UMG_TPS = CreateWidget<UUMG_TPS>(this, UMG_TPS_C);
		//��ӵ�����
		UMG_TPS->AddToViewport();
	}
	else
	{
		UKismetSystemLibrary::PrintString(this,TEXT("UMG_TPS Load Failed..."));
	}

	//���ҽ�����ͼ
	TSubclassOf<UUMG_Control> UMG_Control_C = LoadClass<UUMG_Control>(this, TEXT("/Game/Widgets/BP_UMG_Control.BP_UMG_Control_C"));
	if (UMG_Control_C)
	{
		//�������˵�
		UMG_Control = CreateWidget<UUMG_Control>(this, UMG_Control_C);
		//��ӵ�����
		UMG_Control->AddToViewport();
	}
	else
	{
		UKismetSystemLibrary::PrintString(this, TEXT("UMG_Control Load Failed..."));
	}
}

//�趨����
void ATPSPlayerController::SetScore_Implementation(int Score)
{
	if(TPSPlayerState)
		TPSPlayerState->SetScore(Score);
	UMG_TPS->SetScore(Score);
}

//�趨��ɱ
void ATPSPlayerController::SetKill_Implementation(int Kill)
{
	if(TPSPlayerState)
		TPSPlayerState->SetKill(Kill);
	UMG_TPS->SetKill(Kill);
}

//�趨׼��ʱ��
void ATPSPlayerController::SetReadyTime_Implementation(int Time)
{
	UMG_TPS->SetReadyTime(Time);
}

//�趨��Ϸʱ��
void ATPSPlayerController::SetGameplayTime_Implementation(int Time)
{
	UMG_TPS->SetGameplayTime(Time);
}

//�趨��Ϸ����
void ATPSPlayerController::SetGameOver_Implementation(int Score, int Kill, int Die)
{
	UMG_TPS->SetGameOver(Score, Kill, Die);
}
