// Fill out your copyright notice in the Description page of Project Settings.


#include "TPSPlayerController.h"

//��ұ��ص�¼
void ATPSPlayerController::ClientPostLogin_Implementation()
{

	//��ʼ������
	SetupUMG();

	//��������ģʽ����Ϸ
	UWidgetBlueprintLibrary::SetInputMode_GameOnly(this);

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
		UE_LOG(LogTemp, Warning, TEXT("UMG_TPS Load Failed..."));
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
		UE_LOG(LogTemp, Warning, TEXT("UMG_Control Load Failed..."));
	}
}
