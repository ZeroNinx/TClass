// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UMG_TPS.generated.h"

/**
 * 
 */
UCLASS()
class TCLASS_API UUMG_TPS : public UUserWidget
{
	GENERATED_BODY()

protected:

public:
	
	//�趨����
	UFUNCTION(BlueprintNativeEvent,BlueprintCallable)
	void SetScore(int Score);

	//�趨��ɱ
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void SetKill(int Kill);

	//�趨Ԥ��ʱ��
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void SetReadyTime(int Time);

	//�趨��Ϸʱ��
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void SetGameplayTime(int Time);

	//�趨��Ϸ����
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void SetGameOver(int Score,int Kill, int Die);

};
