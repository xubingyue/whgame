#include "StdAfx.h"
#include "DataBaseSink.h"
#include "AttemperEngineSink.h"

CAttemperEngineSink::CAttemperEngineSink()
{
	m_pInitParamter=NULL;
	m_pITimerEngine=NULL;
	m_pIEventService=NULL;
	m_pITCPSocketEngine=NULL;
}

CAttemperEngineSink::~CAttemperEngineSink()
{
}

//�ӿڲ�ѯ
void * __cdecl CAttemperEngineSink::QueryInterface(const IID & Guid, DWORD dwQueryVer)
{
	QUERYINTERFACE(IAttemperEngineSink,Guid,dwQueryVer);
	QUERYINTERFACE_IUNKNOWNEX(IAttemperEngineSink,Guid,dwQueryVer);
	return NULL;
}

//����ģ������
bool __cdecl CAttemperEngineSink::BeginService(IUnknownEx * pIUnknownEx)
{
	//Ч�����
	ASSERT(pIUnknownEx!=NULL);
	ASSERT(m_pInitParamter!=NULL);
	ASSERT(m_pIEventService!=NULL);

	//�������
	if (m_ServerListCenter.GetInterface()==NULL)
	{
		if (m_ServerListCenter.CreateInstance()==false)
		{
			m_pIEventService->ShowEventNotify(TEXT("���ķ������б��������ʧ��"),Level_Exception);
			return false;
		}
		m_ServerListCenter->SetEventService(m_pIEventService);
	}

	//�����б�
	tagDataBaseInfo DataBaseInfo;
	DataBaseInfo.wDataBasePort=m_pInitParamter->m_wServerDataBasePort;
	DataBaseInfo.dwDataBaseAddr=inet_addr(m_pInitParamter->m_szServerDataBaseAddr);
	lstrcpyn(DataBaseInfo.szDataBaseUser,m_pInitParamter->m_szServerDataBaseUser,CountArray(DataBaseInfo.szDataBaseUser));
	lstrcpyn(DataBaseInfo.szDataBasePass,m_pInitParamter->m_szServerDataBasePass,CountArray(DataBaseInfo.szDataBasePass));
	lstrcpyn(DataBaseInfo.szDataBaseName,m_pInitParamter->m_szServerDataBaseName,CountArray(DataBaseInfo.szDataBaseName));
	if (m_ServerListCenter->LoadServerList(DataBaseInfo)==false) 
	{
		m_pIEventService->ShowEventNotify(TEXT("��Ϸ�б����ʧ��"),Level_Exception);
		return false;
	}

	return true;
}

//����ģ��ر�
bool __cdecl CAttemperEngineSink::EndService(IUnknownEx * pIUnknownEx)
{
	//�����б�
	if (m_ServerListCenter.GetInterface()!=NULL) 
	{
		m_ServerListCenter->ResetServerList();
	}

	return true;
}

//�¼�����ӿ�
bool __cdecl CAttemperEngineSink::OnAttemperEvent(WORD wIdentifier, 
												  void * pDataBuffer, 
												  WORD wDataSize, 
												  DWORD dwInsertTime)
{
	return false;
}

//�����¼�
bool CAttemperEngineSink::SetEventService(IUnknownEx * pIUnknownEx)
{
	//��ѯ�ӿ�
	ASSERT(pIUnknownEx!=NULL);
	m_pIEventService=GET_OBJECTPTR_INTERFACE(pIUnknownEx,IEventService);
	ASSERT(m_pIEventService!=NULL);

	//�������
	if (m_ServerListCenter.GetInterface()!=NULL)
	{
		m_ServerListCenter->SetEventService(m_pIEventService);
	}

	return (m_pIEventService!=NULL);
}

//���ú���
bool CAttemperEngineSink::InitAttemperSink(CInitParamter * pInitParamter, 
										   IUnknownEx * pIUnknownEx)
{
	//Ч�����
	ASSERT(pIUnknownEx!=NULL);
	ASSERT(pInitParamter!=NULL);

	//���ñ���
	m_pInitParamter=pInitParamter;

	//��������
	IServiceEngine * pIServiceEngine=(IServiceEngine *)pIUnknownEx->QueryInterface(IID_IServiceEngine,VER_IServiceEngine);
	if (pIServiceEngine==NULL)
	{
		m_pIEventService->ShowEventNotify(TEXT("��ȡ�����������ʧ��"),
										Level_Exception);
		return false;
	}

	//��ʱ������
	m_pITimerEngine=(ITimerEngine *)pIServiceEngine->GetTimerEngine(IID_ITimerEngine,VER_ITimerEngine);
	if (m_pITimerEngine==NULL)
	{
		m_pIEventService->ShowEventNotify(TEXT("��ȡ��ʱ���������ʧ��"),Level_Exception);
		return false;
	}

	//��������
	m_pITCPSocketEngine=(ITCPSocketEngine *)pIServiceEngine->GetTCPSocketEngine(IID_ITCPSocketEngine,VER_ITCPSocketEngine);
	if (m_pITCPSocketEngine==NULL)
	{
		m_pIEventService->ShowEventNotify(TEXT("��ȡ�����������ʧ��"),
										Level_Exception);
		return false;
	}

	//���ݿ�����
	IDataBaseEngine * pIDataBaseEngine=(IDataBaseEngine *)pIServiceEngine->GetDataBaseEngine(IID_IDataBaseEngine,VER_IDataBaseEngine);
	if (pIDataBaseEngine==NULL)
	{
		m_pIEventService->ShowEventNotify(TEXT("��ȡ���ݿ��������ʧ��"),
										Level_Exception);
		return false;
	}

	//���ݿⴥ��
	IUnknownEx * pIQueueService=(IUnknownEx *)pIDataBaseEngine->GetQueueService(IID_IUnknownEx,VER_IUnknownEx);
	if (m_DataBaseEvent.SetQueueService(pIQueueService)==false)
	{
		m_pIEventService->ShowEventNotify(TEXT("��ȡ���ݿⴥ������ʧ��"),
											Level_Exception);
		return false;
	}

	return true;
}

//��ʱ���¼�
bool __cdecl CAttemperEngineSink::OnEventTimer(WORD wTimerID, WPARAM wBindParam)
{
	return false;
}

//���ݿ��¼�
bool __cdecl CAttemperEngineSink::OnEventDataBase(void * pDataBuffer, 
												  WORD wDataSize, 
												  NTY_DataBaseEvent * pDataBaseEvent)
{
	return false;
}

//����Ӧ���¼�
bool __cdecl CAttemperEngineSink::OnEventSocketAccept(NTY_SocketAcceptEvent * pSocketAcceptEvent)
{
	return true;
}

//�����ȡ�¼�
bool __cdecl CAttemperEngineSink::OnEventSocketRead(CMD_Command Command, 
													void * pDataBuffer, 
													WORD wDataSize, 
													NTY_SocketReadEvent * pSocketReadEvent)
{
	switch (Command.wMainCmdID)
	{
	//�б���Ϣ
	case MDM_CS_SERVER_LIST:			
		{
			return OnSocketMainServerList(Command,
									pDataBuffer,
									wDataSize,
									pSocketReadEvent);
		}

	//�������
	case MDM_CS_SERVER_MANAGER:			
		{
			return OnSocketMainServerManager(Command,
									pDataBuffer,
									wDataSize,
									pSocketReadEvent);
		}
	}

	return false;
}

//����ر��¼�
bool __cdecl CAttemperEngineSink::OnEventSocketClose(NTY_SocketCloseEvent * pSocketCloseEvent)
{
	return true;
}

//�б���Ϣ����
bool CAttemperEngineSink::OnSocketMainServerList(CMD_Command Command, 
												 void * pDataBuffer, 
												 WORD wDataSize, 
												 NTY_SocketReadEvent * pSocketReadEvent)
{
	ASSERT(Command.wMainCmdID==MDM_CS_SERVER_LIST);
	switch (Command.wSubCmdID)
	{
	//��ȡ�б�
	case SUB_CS_GET_SERVER_LIST:	
		{
			//��������
			WORD wIndex=pSocketReadEvent->wIndex;
			WORD wRountID=pSocketReadEvent->wRoundID;

			//�б���Ϣ
			CMD_CS_ListInfo ListInfo;
			memset(&ListInfo,0,sizeof(ListInfo));
			ListInfo.dwTypeCount=m_ServerListCenter->GetGameTypeCount();
			ListInfo.dwKindCount=m_ServerListCenter->GetGameKindCount();
			ListInfo.dwServerCount=m_ServerListCenter->GetGameServerCount();
			ListInfo.dwStationCount=m_ServerListCenter->GetGameStationCount();
			m_pITCPSocketEngine->SendData(wIndex,wRountID,MDM_CS_SERVER_LIST,SUB_CS_LIST_INFO,&ListInfo,sizeof(ListInfo));

			//������Ϣ
			POSITION Pos=NULL;
			WORD wSendSize=0L;
			BYTE cbBuffer[SOCKET_PACKAGE];
			for (DWORD i=0;i<ListInfo.dwTypeCount;i++)
			{
				if ((wSendSize+sizeof(tagGameType))>sizeof(cbBuffer))
				{
					m_pITCPSocketEngine->SendData(wIndex,wRountID,MDM_CS_SERVER_LIST,SUB_CS_LIST_TYPE,cbBuffer,wSendSize);
					wSendSize=0;
				}
				tagGameTypeItem * pGameTypeItem=m_ServerListCenter->EmunGameTypeItem(Pos);
				CopyMemory(cbBuffer+wSendSize,&pGameTypeItem->GameType,sizeof(tagGameType));
				wSendSize+=sizeof(tagGameType);
			}
			if (wSendSize>0) m_pITCPSocketEngine->SendData(wIndex,wRountID,MDM_CS_SERVER_LIST,SUB_CS_LIST_TYPE,cbBuffer,wSendSize);

			//������Ϣ
			Pos=NULL;
			wSendSize=0L;
			for (DWORD i=0;i<ListInfo.dwKindCount;i++)
			{
				if ((wSendSize+sizeof(tagGameKind))>sizeof(cbBuffer))
				{
					m_pITCPSocketEngine->SendData(wIndex,wRountID,MDM_CS_SERVER_LIST,SUB_CS_LIST_KIND,cbBuffer,wSendSize);
					wSendSize=0;
				}
				tagGameKindItem * pGameKindItem=m_ServerListCenter->EmunGameKindItem(Pos);
				CopyMemory(cbBuffer+wSendSize,&pGameKindItem->GameKind,sizeof(tagGameKind));
				wSendSize+=sizeof(tagGameKind);
			}
			if (wSendSize>0) m_pITCPSocketEngine->SendData(wIndex,wRountID,MDM_CS_SERVER_LIST,SUB_CS_LIST_KIND,cbBuffer,wSendSize);

			//վ����Ϣ
			Pos=NULL;
			wSendSize=0L;
			for (DWORD i=0;i<ListInfo.dwStationCount;i++)
			{
				if ((wSendSize+sizeof(tagGameStation))>sizeof(cbBuffer))
				{
					m_pITCPSocketEngine->SendData(wIndex,wRountID,MDM_CS_SERVER_LIST,SUB_CS_LIST_STATION,cbBuffer,wSendSize);
					wSendSize=0;
				}
				tagGameStationItem * pGameStationItem=m_ServerListCenter->EmunGameStationItem(Pos);
				CopyMemory(cbBuffer+wSendSize,&pGameStationItem->GameStation,sizeof(tagGameStation));
				wSendSize+=sizeof(tagGameStation);
			}
			if (wSendSize>0) m_pITCPSocketEngine->SendData(wIndex,wRountID,MDM_CS_SERVER_LIST,SUB_CS_LIST_STATION,cbBuffer,wSendSize);

			//������Ϣ
			Pos=NULL;
			wSendSize=0L;
			for (DWORD i=0;i<ListInfo.dwServerCount;i++)
			{
				if ((wSendSize+sizeof(tagGameServer))>sizeof(cbBuffer))
				{
					m_pITCPSocketEngine->SendData(wIndex,wRountID,MDM_CS_SERVER_LIST,SUB_CS_LIST_SERVER,cbBuffer,wSendSize);
					wSendSize=0;
				}
				tagGameServerItem * pGameServerItem=m_ServerListCenter->EmunGameServerItem(Pos);
				CopyMemory(cbBuffer+wSendSize,&pGameServerItem->GameServer,sizeof(tagGameServer));
				wSendSize+=sizeof(tagGameServer);
			}
			if (wSendSize>0) m_pITCPSocketEngine->SendData(wIndex,wRountID,MDM_CS_SERVER_LIST,SUB_CS_LIST_SERVER,cbBuffer,wSendSize);

			//�������
			m_pITCPSocketEngine->SendData(wIndex,wRountID,MDM_CS_SERVER_LIST,SUB_CS_LIST_FINISH);

			return true;	
		}
	}

	return false;
}

//������Ϣ����
bool CAttemperEngineSink::OnSocketMainServerManager(CMD_Command Command, 
													void * pDataBuffer, 
													WORD wDataSize, 
													NTY_SocketReadEvent * pSocketReadEvent)
{
	ASSERT(Command.wMainCmdID==MDM_CS_SERVER_MANAGER);
	switch (Command.wSubCmdID)
	{
	//����ע��
	case SUB_CS_REG_GAME_SERVER:		
		{
			//Ч�����
			ASSERT(wDataSize==sizeof(CMD_CS_RegGameServer));
			if (wDataSize!=sizeof(CMD_CS_RegGameServer)) return false;

			//��Ϣ����
			CMD_CS_RegGameServer * pRegGameServer=(CMD_CS_RegGameServer *)pDataBuffer;
			tagGameServer * pGameServer=&pRegGameServer->GameServer;
			tagGameServerItem * pGameServerItem=m_ServerListCenter->SearchGameServer(pGameServer->wKindID,pGameServer->wServerID);
			if (pGameServerItem!=NULL)
			{
				pGameServerItem->dwUpdateTime=(DWORD)time(NULL);
				CopyMemory(&pGameServerItem->GameServer,pGameServer,sizeof(tagGameServer));
			}
			else m_ServerListCenter->InsertGameServer(pGameServer);

			return true;
		}

	//ע������
	case SUB_CS_UNREG_GAME_SERVER:		
		{
			//Ч�����
			ASSERT(wDataSize==sizeof(CMD_CS_UnRegGameServer));
			if (wDataSize!=sizeof(CMD_CS_UnRegGameServer)) return false;

			//��Ϣ����
			CMD_CS_UnRegGameServer * pUnRegGameServer=(CMD_CS_UnRegGameServer *)pDataBuffer;
			m_ServerListCenter->DeleteGameServer(pUnRegGameServer->wKindID,pUnRegGameServer->wServerID);

			return true;
		}

	//��������
	case SUB_CS_SERVER_ONLINE_COUNT:	
		{
			//Ч�����
			ASSERT(wDataSize==sizeof(CMD_CS_ServerOnLineCount));
			if (wDataSize!=sizeof(CMD_CS_ServerOnLineCount)) return false;

			//��Ϣ����
			CMD_CS_ServerOnLineCount * pServerOnLineCount=(CMD_CS_ServerOnLineCount *)pDataBuffer;
			WORD wKindID=pServerOnLineCount->wKindID;
			WORD wServerID=pServerOnLineCount->wServerID;
			m_ServerListCenter->UpdateServerOnLineCount(wKindID,wServerID,pServerOnLineCount->dwOnLineCount);

			return true;
		}
	}

	return false;
}


//-----------------------------------------------
//					the end
//-----------------------------------------------
