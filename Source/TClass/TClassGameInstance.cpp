// Fill out your copyright notice in the Description page of Project Settings.


#include "TClassGameInstance.h"

UTClassGameInstance::UTClassGameInstance():Super::UGameInstance()
{
	//��ȡ������ϵͳ�ӿ�
	OnlineSub = IOnlineSubsystem::Get();

	//�󶨻ص�����
	OnCreateSessionCompleteDelegate = FOnCreateSessionCompleteDelegate::
		CreateUObject(this, &UTClassGameInstance::OnCreateSessionComplete);
	OnStartSessionCompleteDelegate = FOnStartSessionCompleteDelegate::
		CreateUObject(this, &UTClassGameInstance::OnStartSessionComplete);
	OnFindSessionsCompleteDelegate = FOnFindSessionsCompleteDelegate::
		CreateUObject(this, &UTClassGameInstance::OnFindSessionComplete);
	OnJoinSessionCompleteDelegate = FOnJoinSessionCompleteDelegate::
		CreateUObject(this, &UTClassGameInstance::OnJoinSessionComplete);
	OnDestroySessionCompleteDelegate = FOnDestroySessionCompleteDelegate::
		CreateUObject(this, &UTClassGameInstance::OnDestroySessionComplete);
	
}

//��ʼ��
void UTClassGameInstance::Init()
{
	UE_LOG(LogTemp, Warning, TEXT("Creating GameInstant..."));
	
}

//����ر�ʱ
void UTClassGameInstance::Shutdown()
{
	UE_LOG(LogTemp, Warning, TEXT("Shutting Down GameInstant..."));
	DestroySession();
}

//��ʾ�������
void UTClassGameInstance::ShowLoadingScreen_Implementation()
{
	//�жϽ����Ƿ����
	if (!IsValid(LoadingUMG))
	{
		//�����������
		TSubclassOf<UUMG_Loading> LoadingUMGClass = LoadClass<UUMG_Loading>(this, TEXT("/Game/Widgets/BP_UMG_Loading.BP_UMG_Loading_C"));
		if (LoadingUMGClass)
		{
			UE_LOG(LogTemp, Warning, TEXT("UMG_Loading Found..."));
			LoadingUMG = CreateWidget<UUMG_Loading>(GetWorld(), LoadingUMGClass);
		}
	}
	LoadingUMG->AddToViewport();

}

//ע�������
void UTClassGameInstance::AssignPlayerController_Implementation(APlayerController* InController)
{
	//��ȡ������ϵͳ�ӿ�
	OnlineSub = IOnlineSubsystem::Get();

	//��ȡ��ҿ�����
	PlayerController = GetPrimaryPlayerController();
	UserID = GetPrimaryPlayerUniqueId().ToSharedRef();

	if (PlayerController)
		UE_LOG(LogTemp, Warning, TEXT("Controller Assigned Success"));

}

//������Ϸ
void UTClassGameInstance::HostSession_Implementation()
{
	if (OnlineSub)
	{
		//��ȡ�Ự�ӿ�
		IOnlineSessionPtr Session = OnlineSub->GetSessionInterface();
		if (Session.IsValid())
		{
			//�Ự����
			FOnlineSessionSettings Settings;

			//������
			Settings.NumPublicConnections = 10;
			Settings.bShouldAdvertise = true;
			Settings.bAllowJoinInProgress = true;

			//ʹ�þ�����
			Settings.bIsLANMatch = true;
			Settings.bUsesPresence = true;
			Settings.bAllowJoinViaPresence = true;
		

			//��ί��
			OnCreateSessionCompleteDelegateHandle = Session
				->AddOnCreateSessionCompleteDelegate_Handle
				(OnCreateSessionCompleteDelegate);
			//�����Ự
			Session->CreateSession(*UserID, NAME_GameSession, Settings);
		}
	}
}

//������Ϸ
void UTClassGameInstance::ClientSession_Implementation()
{
	if (OnlineSub)
	{
		//��ȡ�Ự�ӿ�
		IOnlineSessionPtr Session = OnlineSub->GetSessionInterface();
		if (Session.IsValid())
		{
			//ʵ�����������ָ�벢���趨����
			SearchObject = MakeShareable(new FOnlineSessionSearch);

			//���ؽ����
			SearchObject->MaxSearchResults = 10;

			//�Ƿ��Ǿ�����������IsLAN
			SearchObject->bIsLanQuery = true;
			SearchObject->QuerySettings.Set(SEARCH_PRESENCE, true,EOnlineComparisonOp::Equals);
			
			//��Ѱ�һỰί��
			OnFindSessionsCompleteDelegateHandle = Session->
				AddOnFindSessionsCompleteDelegate_Handle
				(OnFindSessionsCompleteDelegate);
			//���лỰѰ��
			Session->FindSessions(*UserID, SearchObject.ToSharedRef());
		}
	}
}

//�ݻٻỰ
void UTClassGameInstance::DestroySession_Implementation()
{
	if (OnlineSub)
	{
		IOnlineSessionPtr Session = OnlineSub->GetSessionInterface();
		if (Session.IsValid())
		{
			//ע�����ٻỰί��
			Session->ClearOnDestroySessionCompleteDelegate_Handle
			(OnDestroySessionCompleteDelegateHandle);
			//�����߼�������
			Session->DestroySession(NAME_GameSession);
		}
	}
}

//�����Ự���
void UTClassGameInstance::OnCreateSessionComplete(FName SessionName, bool bWasSuccessful)
{

	if (OnlineSub)
	{
		IOnlineSessionPtr Session = OnlineSub->GetSessionInterface();
		if (Session.IsValid())
		{
			//��󴴽��Ự��ɻص�����
			Session->
				ClearOnCreateSessionCompleteDelegate_Handle
				(OnCreateSessionCompleteDelegateHandle);
			//�жϴ����Ự�Ƿ�ɹ�
			if (bWasSuccessful)
			{
				UE_LOG(LogTemp, Warning, TEXT("Create Session Succeed"));

				//�󶨿����Ựί��
				OnStartSessionCompleteDelegateHandle = Session->
					AddOnStartSessionCompleteDelegate_Handle
					(OnStartSessionCompleteDelegate);
				Session->StartSession(NAME_GameSession);
			}
			else UE_LOG(LogTemp, Warning, TEXT("Create Session Failed"));
		}
	}
}

//�Ự��ʼ
void UTClassGameInstance::OnStartSessionComplete(FName SessionName, bool bWasSuccessful)
{
	UE_LOG(LogTemp, Warning, TEXT("Session Started"));
	if (OnlineSub)
	{
		IOnlineSessionPtr Session = OnlineSub->GetSessionInterface();
		if (Session.IsValid())
		{
			//ע�������Ựί�а�
			Session->ClearOnStartSessionCompleteDelegate_Handle
			(OnStartSessionCompleteDelegateHandle);
			if (bWasSuccessful)
			{
				UE_LOG(LogTemp, Warning, TEXT("Start Session Succeed"));

				//�������ת����
				UGameplayStatics::OpenLevel(PlayerController->GetWorld(),
					FName("Map_TPS"), true, FString("listen"));
			}
			else
				UE_LOG(LogTemp, Warning, TEXT("Start Session Failed"));
		}
	}
}

//���һỰ���
void UTClassGameInstance::OnFindSessionComplete(bool bWasSuccessful)
{
	IOnlineSessionPtr Session = OnlineSub->GetSessionInterface();
	if (Session.IsValid())
	{
		//ȡ��Ѱ�һỰί�а�
		Session->ClearOnStartSessionCompleteDelegate_Handle
		(OnStartSessionCompleteDelegateHandle);

		//���Ѱ�һỰ�ɹ�
		if (bWasSuccessful)
		{
			//����ռ��Ľ�������Ҵ���0
			if (SearchObject.IsValid() && SearchObject->SearchResults.Num() > 0)
			{
				UE_LOG(LogTemp, Warning, TEXT("Find Session Succeed"));
				//�󶨼���Sessionί��
				OnJoinSessionCompleteDelegateHandle = Session
					->AddOnJoinSessionCompleteDelegate_Handle
					(OnJoinSessionCompleteDelegate);
				//ִ�м���Ự
				Session->JoinSession(*UserID, NAME_GameSession, SearchObject->SearchResults[0]);
			}
			else
				UE_LOG(LogTemp, Warning, TEXT("Session Num <=0 "));
		}
		else
			UE_LOG(LogTemp, Warning, TEXT("Find Session Failed"));
	}
}

//����Ự���
void UTClassGameInstance::OnJoinSessionComplete(FName SessionName, EOnJoinSessionCompleteResult::Type Result)
{
	if (OnlineSub)
	{
		IOnlineSessionPtr Session = OnlineSub->GetSessionInterface();
		if (Session.IsValid())
		{
			//ȡ������Ի�ί�а�
			Session->ClearOnJoinSessionCompleteDelegate_Handle
			(OnJoinSessionCompleteDelegateHandle);
			//�������ɹ�
			if (Result == EOnJoinSessionCompleteResult::Success)
			{
				//������ҵ��µ�ͼ
				FString ConnectString;
				if (Session->GetResolvedConnectString(NAME_GameSession, ConnectString))
				{
					UE_LOG(LogTemp, Warning, TEXT("Join Session Succeed"));
					
					//��������ģʽ����Ϸ
					UWidgetBlueprintLibrary::SetInputMode_GameOnly(PlayerController);

					//�ͻ����л����������Ĺؿ�
					PlayerController->ClientTravel(ConnectString, TRAVEL_Absolute);
				}
				else
					UE_LOG(LogTemp, Warning, TEXT("Join Session Failed"));
			}
		}
	}
}

//�Ự�������
void UTClassGameInstance::OnDestroySessionComplete(FName SessionName, bool bWasSuccessful)
{
	if (OnlineSub)
	{
		IOnlineSessionPtr Session = OnlineSub->GetSessionInterface();
		if (Session.IsValid())
		{
			//�����ٻỰί��
			OnDestroySessionCompleteDelegateHandle = Session->
				AddOnDestroySessionCompleteDelegate_Handle
				(OnDestroySessionCompleteDelegate);
			//ִ�����ٻỰ
			Session->DestroySession(NAME_GameSession);
		}
	}
}
