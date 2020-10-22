// Fill out your copyright notice in the Description page of Project Settings.


#include "UMG_MainMenu.h"

//构造函数
UUMG_MainMenu::UUMG_MainMenu(const FObjectInitializer& ObjectInitializer) :Super(ObjectInitializer)
{

	
}

//初始化
bool UUMG_MainMenu::Initialize()
{
	if (!Super::Initialize())
	{
		UE_LOG(LogTemp, Warning, TEXT("Initialize Fail..."));
		return false;
	}

	//获取游戏实例
	GameInstance = Cast<UTClassGameInstance>(GetGameInstance());

	//寻找按钮
	btnCreate = (UButton*)GetWidgetFromName(TEXT("btnCreate"));
	btnJoin = (UButton*)GetWidgetFromName(TEXT("btnJoin"));
	btnExit = (UButton*)GetWidgetFromName(TEXT("btnExit"));

	UE_LOG(LogTemp, Warning, TEXT("Creating main menu..."));

	///添加点击事件

	//开始游戏按钮
	FScriptDelegate btnCreateDel;
	btnCreateDel.BindUFunction(this, "btnCreateClick");
	btnCreate->OnClicked.Add(btnCreateDel);


	//加入游戏按钮
	FScriptDelegate btnJoinDel;
	btnJoinDel.BindUFunction(this, "btnJoinClick");
	btnJoin->OnClicked.Add(btnJoinDel);


	//退出游戏按钮
	FScriptDelegate btnExitDel;
	btnExitDel.BindUFunction(this, "btnExitClick");
	btnExit->OnClicked.Add(btnExitDel);


	return true;
}

//创建游戏点击事件
void UUMG_MainMenu::btnCreateClick()
{
	//创建会话
	GameInstance->HostSession();
}


//加入游戏点击事件
void UUMG_MainMenu::btnJoinClick()
{
	//显示载入界面
	GameInstance->ShowLoadingScreen();
	
	//查找并加入客户端
	GameInstance->ClientSession();
}

//退出游戏点击事件
void UUMG_MainMenu::btnExitClick()
{
	UE_LOG(LogTemp, Warning, TEXT("Quiting Game..."));
	UKismetSystemLibrary::QuitGame(this, nullptr, EQuitPreference::Quit,false);
}
