// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GM_TPS.h"
#include "UMG_TPS.h"
#include "UMG_Control.h"
#include "Engine/GameInstance.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/PlayerController.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "TPSPlayerController.generated.h"

/**
 * ��ҿ�����
 */
UCLASS()
class TCLASS_API ATPSPlayerController : public APlayerController
{
	GENERATED_BODY()

protected:

	//״̬����
	UPROPERTY(BlueprintReadWrite)
	UUMG_TPS* UMG_TPS;
	
	//�ٿؽ���
	UPROPERTY(BlueprintReadWrite)
	UUMG_Control* UMG_Control;

public:

	//��ұ��ص�½
	UFUNCTION(Client,Reliable,BlueprintCallable)
	void ClientPostLogin();

	//��ʼ��UMG����
	UFUNCTION(BlueprintCallable)
	void SetupUMG();


};
