// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UMG.h"
#include "TClassGameInstance.h"
#include "Kismet/KismetSystemLibrary.h"
#include "UMG_MainMenu.generated.h"

/**
 * ���˵���
 */
UCLASS()
class TCLASS_API UUMG_MainMenu : public UUserWidget
{
	GENERATED_BODY()

public:

	//���캯��
	UUMG_MainMenu(const FObjectInitializer& ObjectInitializer);

	//��ʼ��
	bool Initialize() override;

protected:

	//������Ϸ��ť
	UButton* btnCreate;
	
	UFUNCTION()
	void btnCreateClick();


	//������Ϸ��ť
	UButton* btnJoin;

	UFUNCTION()
	void btnJoinClick();

	//�˳���Ϸ��ť
	UButton* btnExit;

	UFUNCTION()
	void btnExitClick();

};
