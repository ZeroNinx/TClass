// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "CoreMinimal.h"
#include "Widgets/SWidget.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/GameModeBase.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Kismet/KismetSystemLibrary.h"

#include "TClassGameInstance.h"
#include "UMG_MainMenu.h"

#include "GM_MainMenu.generated.h"

/**
 * ���˵���Ϸģʽ
 */
UCLASS()
class TCLASS_API AGM_MainMenu : public AGameModeBase
{
	GENERATED_BODY()

public:
	
	//��ʼ��Ϸ
	void StartPlay() override;

protected:

	//��Ϸʵ��
	UTClassGameInstance* GameInstance;

	//��ҿ�����
	APlayerController* PlayerController;

	//���˵�����
	UUMG_MainMenu* MainMenu;
};
