// Fill out your copyright notice in the Description page of Project Settings.


#include "UMG_MainMenu.h"

//���캯��
UUMG_MainMenu::UUMG_MainMenu(const FObjectInitializer& ObjectInitializer) :Super(ObjectInitializer)
{

	
}

//��ʼ��
bool UUMG_MainMenu::Initialize()
{
	if (!Super::Initialize())
	{
		return false;
	}

	//Ѱ�Ұ�ť
	btnCreate = (UButton*)GetWidgetFromName(TEXT("btnCreate"));
	btnJoin = (UButton*)GetWidgetFromName(TEXT("btnJoin"));
	btnExit = (UButton*)GetWidgetFromName(TEXT("btnExit"));

	UE_LOG(LogTemp, Warning, TEXT("Creating main menu..."));

	//��ӵ���¼�


	//��ʼ��Ϸ��ť

	//������Ϸ��ť
	FScriptDelegate btnJoinDel;
	btnJoinDel.BindUFunction(this, "btnJoinClick");
	btnJoin->OnClicked.Add(btnJoinDel);


	//�˳���Ϸ��ť
	FScriptDelegate btnExitDel;
	btnExitDel.BindUFunction(this, "btnExitClick");
	btnExit->OnClicked.Add(btnExitDel);

	return true;
}


//������Ϸ����¼�
void UUMG_MainMenu::btnCreateClick()
{

}


//������Ϸ����¼�
void UUMG_MainMenu::btnJoinClick()
{
	//��ȡ��Ϸʵ��
	UTClassGameInstance* GameInstance = Cast<UTClassGameInstance>(GetGameInstance());

	//GameInstance->ShowLoadingScreen();
}

//�˳���Ϸ����¼�
void UUMG_MainMenu::btnExitClick()
{
	UE_LOG(LogTemp, Warning, TEXT("Quiting Game..."));
	UKismetSystemLibrary::QuitGame(this, nullptr, EQuitPreference::Quit,false);
}
