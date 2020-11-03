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
		UE_LOG(LogTemp, Warning, TEXT("Initialize Fail..."));
		return false;
	}

	//��ȡ��Ϸʵ��
	GameInstance = Cast<UTClassGameInstance>(GetGameInstance());

	//Ѱ�Ұ�ť
	btnLocal = (UButton*)GetWidgetFromName(TEXT("btnLocal"));
	btnCreate = (UButton*)GetWidgetFromName(TEXT("btnCreate"));
	btnJoin = (UButton*)GetWidgetFromName(TEXT("btnJoin"));
	btnExit = (UButton*)GetWidgetFromName(TEXT("btnExit"));

	UE_LOG(LogTemp, Warning, TEXT("Creating main menu..."));

	///��ӵ���¼�

	//������Ϸ��ť
	FScriptDelegate btnLocalDel;
	btnLocalDel.BindUFunction(this, "btnLocalClick");
	btnLocal->OnClicked.Add(btnLocalDel);

	//��ʼ��Ϸ��ť
	FScriptDelegate btnCreateDel;
	btnCreateDel.BindUFunction(this, "btnCreateClick");
	btnCreate->OnClicked.Add(btnCreateDel);


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

//������Ϸ��ť����¼�
void UUMG_MainMenu::btnLocalClick()
{
	//�򿪱��عؿ�
	UGameplayStatics::OpenLevel(GetWorld(),
		FName("Map_Local"));
}

//������Ϸ��ť����¼�
void UUMG_MainMenu::btnCreateClick()
{
	//�����Ự
	GameInstance->HostSession();
}


//������Ϸ��ť����¼�
void UUMG_MainMenu::btnJoinClick()
{
	//��ʾ�������
	GameInstance->ShowLoadingScreen();
	
	//���Ҳ�����ͻ���
	GameInstance->ClientSession();
}

//�˳���Ϸ��ť����¼�
void UUMG_MainMenu::btnExitClick()
{
	UE_LOG(LogTemp, Warning, TEXT("Quiting Game..."));
	UKismetSystemLibrary::QuitGame(this, nullptr, EQuitPreference::Quit,false);
}
