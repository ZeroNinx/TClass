// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UMG.h"
#include "TClassGameInstance.h"
#include "Kismet/KismetSystemLibrary.h"
#include "UMG_MainMenu.generated.h"

/**
 * 主菜单类
 */
UCLASS()
class TCLASS_API UUMG_MainMenu : public UUserWidget
{
	GENERATED_BODY()

public:

	//构造函数
	UUMG_MainMenu(const FObjectInitializer& ObjectInitializer);

	//初始化
	bool Initialize() override;

protected:

	//创建游戏按钮
	UButton* btnCreate;
	
	UFUNCTION()
	void btnCreateClick();


	//加入游戏按钮
	UButton* btnJoin;

	UFUNCTION()
	void btnJoinClick();

	//退出游戏按钮
	UButton* btnExit;

	UFUNCTION()
	void btnExitClick();

};
