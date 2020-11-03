// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "TPSPlayerState.generated.h"

//��ҷ����ṹ��
USTRUCT(BlueprintType)
struct FPlayerScore
{
	GENERATED_BODY()

	//�������
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FString PlayerName;

	//��ҵ÷�
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int PlayerScore;

};


/**
 * ���״̬
 */
UCLASS()
class TCLASS_API ATPSPlayerState : public APlayerState
{
	GENERATED_BODY()

public:
	
	//�趨����
	UFUNCTION(BlueprintCallable)
	void SetName(FString NewName);

	//�趨����
	UFUNCTION(BlueprintCallable)
	void SetScore(int NewScore);

	//��ȡ��Ϣ
	UFUNCTION(BlueprintCallable)
	FPlayerScore GetPlayerInfo();

protected:

	//��ҵ÷�
	UPROPERTY(BlueprintReadWrite)
	FPlayerScore PlayerScore;

};
