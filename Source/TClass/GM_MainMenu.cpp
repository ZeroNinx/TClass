// Fill out your copyright notice in the Description page of Project Settings.


#include "GM_MainMenu.h"


//��ʼ��Ϸ
void AGM_MainMenu::StartPlay()
{
	//��ȡ��Ϸʵ��
	GameInstance = Cast<UTClassGameInstance>(GetGameInstance());

	//��ȡ��ҿ�����
	PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);

	//ע����ҿ�����
	GameInstance->AssignPlayerController(PlayerController);

	//���Ҳ˵���ͼ
	TSubclassOf<UUMG_MainMenu> MainMenuClass = LoadClass<UUMG_MainMenu>(this,TEXT("/Game/Widgets/BP_UMG_MainMenu.BP_UMG_MainMenu_C"));
	if (MainMenuClass)
	{
		//�������˵�
		MainMenu = CreateWidget<UUMG_MainMenu>(GetWorld(), MainMenuClass);
		//��ӵ�����
		MainMenu->AddToViewport();

		//��ʾ���������
		PlayerController->bShowMouseCursor = true;
		PlayerController->bEnableClickEvents = true;
		PlayerController->bEnableMouseOverEvents = true;

	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("MainMenu Load Failed..."));
	}
	
}
