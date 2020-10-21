// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Blueprint/UserWidget.h"
#include "UMG_Loading.h"
#include "Net/UnrealNetwork.h"
#include "Online.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/PlayerState.h"
#include "GameFramework/PlayerController.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "TClassGameInstance.generated.h"

/**
 * ��Ϸʵ����
 */
UCLASS()
class TCLASS_API UTClassGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:

    //���캯��
    UTClassGameInstance();

	//����ʱ
	virtual void Init() override;
    
    //�ر�ʱ
    virtual void Shutdown() override;

    //ע�������
    UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
    void AssignPlayerController(APlayerController* InController);

	//��ʾ�������
    UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void ShowLoadingScreen();

    //������Ϸ
    UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
    void HostSession();

	//������Ϸ
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void ClientSession();

    //�ݻٻỰ
    UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
    void DestroySession();

protected:	
    
    //�������
    UUMG_Loading* LoadingUMG;

protected:

    //��ҿ�����
    APlayerController* PlayerController;

    //�û�ID
    TSharedPtr<const FUniqueNetId> UserID;

    //������ϵͳ
    IOnlineSubsystem* OnlineSub;

    //����������ί��
    FOnCreateSessionCompleteDelegate OnCreateSessionCompleteDelegate;
    FOnStartSessionCompleteDelegate OnStartSessionCompleteDelegate;

    //����������ί�о��
    FDelegateHandle OnCreateSessionCompleteDelegateHandle;
    FDelegateHandle OnStartSessionCompleteDelegateHandle;

    //���������ί��
    FOnFindSessionsCompleteDelegate OnFindSessionsCompleteDelegate;
    FOnJoinSessionCompleteDelegate OnJoinSessionCompleteDelegate;

    //���������ί�о��
    FDelegateHandle OnFindSessionsCompleteDelegateHandle;
    FDelegateHandle OnJoinSessionCompleteDelegateHandle;

    //���ٻỰί������
    FOnDestroySessionCompleteDelegate OnDestroySessionCompleteDelegate;
    FDelegateHandle OnDestroySessionCompleteDelegateHandle;

    //�������ָ��
    TSharedPtr<FOnlineSessionSearch> SearchObject;

protected:

    //�������Ự�����󣬻ص�����
    void OnCreateSessionComplete(FName SessionName, bool bWasSuccessful);

    //����ʼ�Ự�����󣬻ص�����
    void OnStartSessionComplete(FName SessionName, bool bWasSuccessful);

    //Ѱ�ҷ������󣬻ص�����
    void OnFindSessionComplete(bool bWasSuccessful);
   
    //����������󣬻ص�����
    void OnJoinSessionComplete(FName SessionName, EOnJoinSessionCompleteResult::Type Result);

    //���ٻỰ��,�ص�����
    void OnDestroySessionComplete(FName SessionName, bool bWasSuccessful);

};
