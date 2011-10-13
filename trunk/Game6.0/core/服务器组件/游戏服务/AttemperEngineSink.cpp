#include "StdAfx.h"
#include "TableFrame.h"
#include "DataBaseSink.h"
#include "AttemperEngineSink.h"

//////////////////////////////////////////////////////////////////////////

//���캯��
CAttemperEngineSink::CAttemperEngineSink()
{
	//��Ϸ����
	m_wMaxUserItem=0;
	m_pTableFrame=NULL;
	m_pNormalParameter=NULL;
	m_pAndroidParameter=NULL;

	//��Ϣ����
	m_cbRoomMsgIndex=0;
	m_cbGameMsgIndex=0;

	//���ñ���
	m_dwCenterServer=0L;
	m_pGameServiceAttrib=NULL;
	m_pGameServiceOption=NULL;

	//���Ʊ���
	m_bShallClose=false;
	m_bAllowWisper=true;
	m_bAllowRoomChat=true;
	m_bAllowGameChat=true;
	m_bAllowEnterRoom=true;
	m_bAllowEnterGame=true;

	//���ķ�����
	m_pCenterSocket=NULL;
	m_SocketState=SocketState_NoConnect;

	//��������
	m_wColumnInfoSize=0;
	m_wOnLineInfoSize=0;
	memset(&m_ColumnInfo,0,sizeof(m_ColumnInfo));
	memset(&m_OnLineCountInfo,0,sizeof(m_OnLineCountInfo));

	//��Ϸ���
	m_hDllInstance=NULL;
	m_pIGameServiceManager=NULL;

	//�ӿڱ���
	m_pITimerEngine=NULL;
	m_pIEventService=NULL;
	m_pIAttemperEngine=NULL;
	m_pITCPSocketEngine=NULL;

	return;
}

//��������
CAttemperEngineSink::~CAttemperEngineSink()
{
	//ɾ���ڴ�
	SafeDeleteArray(m_pTableFrame);
	SafeDeleteArray(m_pNormalParameter);
	SafeDeleteArray(m_pAndroidParameter);

	return;
}

//�ӿڲ�ѯ
void * __cdecl CAttemperEngineSink::QueryInterface(const IID & Guid, DWORD dwQueryVer)
{
	QUERYINTERFACE(IAttemperEngineSink,Guid,dwQueryVer);
	QUERYINTERFACE(IGameServiceFrame,Guid,dwQueryVer);
	QUERYINTERFACE_IUNKNOWNEX(IAttemperEngineSink,Guid,dwQueryVer);
	return NULL;
}

//����ģ������
bool __cdecl CAttemperEngineSink::BeginService(IUnknownEx * pIUnknownEx)
{
	//Ч�����
	ASSERT(pIUnknownEx!=NULL);

	//���ñ���
	m_wColumnInfoSize=0;
	m_wOnLineInfoSize=0;
	memset(&m_ColumnInfo,0,sizeof(m_ColumnInfo));
	memset(&m_OnLineCountInfo,0,sizeof(m_OnLineCountInfo));

	//������������
	m_wMaxUserItem=m_pGameServiceOption->wMaxConnect;
	m_pNormalParameter=new tagConnectItemInfo [m_wMaxUserItem];
	m_pAndroidParameter=new tagConnectItemInfo [MAX_ANDROID];
	memset(m_pNormalParameter,0,sizeof(tagConnectItemInfo)*m_wMaxUserItem);
	memset(m_pAndroidParameter,0,sizeof(tagConnectItemInfo)*MAX_ANDROID);

	//������Ϸ���
	if (m_pIGameServiceManager->RectifyServiceOption(m_pGameServiceOption)==false) return false;

	//������Ϸ����
	ASSERT(m_pGameServiceOption->wTableCount!=0);
	m_pTableFrame=new CTableFrame [m_pGameServiceOption->wTableCount];
	if (m_pTableFrame==NULL) return false;

	//��ʼ������
	bool bSuccess=false;
	tagTableFrameParameter TableFrameParameter;
	TableFrameParameter.pGameServiceAttrib=m_pGameServiceAttrib;
	TableFrameParameter.pGameServiceOption=m_pGameServiceOption;
	TableFrameParameter.pIGameServiceFrame=GET_MYSELF_INTERFACE(IUnknownEx);
	TableFrameParameter.pIGameServiceManager=GET_OBJECTPTR_INTERFACE(m_pIGameServiceManager,IUnknownEx);
	for (WORD i=0;i<m_pGameServiceOption->wTableCount;i++)
	{
		bSuccess=(m_pTableFrame+i)->InitTableFrame(i,&TableFrameParameter);
		if (bSuccess==false) return false;
	}

	//�����б����
	switch (m_pGameServiceOption->wServerType)
	{
	case GAME_GENRE_GOLD:	//�������
		{
			//��������
			tagColumnItem ColumnItem[]=
			{
				115,DTP_USER_ACCOUNTS,TEXT("�û���"),
					60,DTP_GAME_ID,TEXT("ID ����"),
					60,DTP_USER_SCORE,TEXT("��Ϸ��"),
					40,DTP_USER_TABLE,TEXT("����"),
					85,DTP_GAME_LEVEL,TEXT("��Ϸ����"),
					50,DTP_USER_EXPERIENCE,TEXT("����ֵ"),
					60,DTP_WIN_RATE,TEXT("ʤ��"),
					60,DTP_FLEE_RATE,TEXT("����"),
					60,DTP_USER_PLAY_COUNT,TEXT("�ܾ�"),
					60,DTP_USER_WIN,TEXT("Ӯ��"),
					60,DTP_USER_LOST,TEXT("���"),
					60,DTP_USER_DRAW,TEXT("�;�"),
					60,DTP_USER_FLEE,TEXT("�Ӿ�"),
					200,DTP_UNDER_WRITE,TEXT("����ǩ��"),
			};

			//���ñ���
			m_ColumnInfo.wColumnCount=CountArray(ColumnItem);
			CopyMemory(m_ColumnInfo.ColumnItem,ColumnItem,sizeof(ColumnItem));

			break;
		}
	case GAME_GENRE_MATCH:	//��������
		{
			//��������
			tagColumnItem ColumnItem[]=
			{
				115,DTP_USER_ACCOUNTS,TEXT("�û���"),
					60,DTP_GAME_ID,TEXT("ID ����"),
					60,DTP_USER_SCORE,TEXT("����"),
					40,DTP_USER_TABLE,TEXT("����"),
					85,DTP_GAME_LEVEL,TEXT("��Ϸ����"),
					50,DTP_USER_EXPERIENCE,TEXT("����ֵ"),
					60,DTP_WIN_RATE,TEXT("ʤ��"),
					60,DTP_FLEE_RATE,TEXT("����"),
					60,DTP_USER_PLAY_COUNT,TEXT("�ܾ�"),
					60,DTP_USER_WIN,TEXT("Ӯ��"),
					60,DTP_USER_LOST,TEXT("���"),
					60,DTP_USER_DRAW,TEXT("�;�"),
					60,DTP_USER_FLEE,TEXT("�Ӿ�"),
					200,DTP_UNDER_WRITE,TEXT("����ǩ��"),
			};

			//���ñ���
			m_ColumnInfo.wColumnCount=CountArray(ColumnItem);
			CopyMemory(m_ColumnInfo.ColumnItem,ColumnItem,sizeof(ColumnItem));

			break;
		}
	default:
		{
			//��������
			tagColumnItem ColumnItem[]=
			{
				115,DTP_USER_ACCOUNTS,TEXT("�û���"),
					60,DTP_GAME_ID,TEXT("ID ����"),
					60,DTP_USER_SCORE,TEXT("����"),
					40,DTP_USER_TABLE,TEXT("����"),
					85,DTP_GAME_LEVEL,TEXT("��Ϸ����"),
					50,DTP_USER_EXPERIENCE,TEXT("����ֵ"),
					60,DTP_WIN_RATE,TEXT("ʤ��"),
					60,DTP_FLEE_RATE,TEXT("����"),
					60,DTP_USER_PLAY_COUNT,TEXT("�ܾ�"),
					60,DTP_USER_WIN,TEXT("Ӯ��"),
					60,DTP_USER_LOST,TEXT("���"),
					60,DTP_USER_DRAW,TEXT("�;�"),
					60,DTP_USER_FLEE,TEXT("�Ӿ�"),
					200,DTP_UNDER_WRITE,TEXT("����ǩ��"),
			};

			//���ñ���
			m_ColumnInfo.wColumnCount=CountArray(ColumnItem);
			CopyMemory(m_ColumnInfo.ColumnItem,ColumnItem,sizeof(ColumnItem));

			break;
		}
	}

	//�����б�
	WORD wColumnInfoHandSize=sizeof(m_ColumnInfo)-sizeof(m_ColumnInfo.ColumnItem);
	m_wColumnInfoSize=wColumnInfoHandSize+m_ColumnInfo.wColumnCount*sizeof(m_ColumnInfo.ColumnItem[0]);

	//�������
	srand((DWORD)time(NULL));

	//�������ķ�����
	m_pCenterSocket->Connect(m_dwCenterServer,PORT_CENTER_SERVER);

	//ϵͳ��Ϣ
	m_pITimerEngine->SetTimer(IDI_SEND_SYSTEM_MESSAGE,300000L,(DWORD)(-1),0);

	//�����û�
	m_DataBaseEvent.PostDataBaseEvent(DBR_GR_LOAD_ANDROID,0,0,NULL,0);

	//�����û�
	m_pITimerEngine->SetTimer(IDI_DISTRIBUTE_ANDROID,TIME_DISTRIBUTE_ANDROID*1000L,(DWORD)(-1),NULL);

	return true;
}

//����ģ��ر�
bool __cdecl CAttemperEngineSink::EndService(IUnknownEx * pIUnknownEx)
{
	//ע������
	if (m_SocketState==SocketState_Connected)
	{
		CMD_CS_UnRegGameServer UnRegGameServer;
		memset(&UnRegGameServer,0,sizeof(UnRegGameServer));
		UnRegGameServer.wKindID=m_pGameServiceAttrib->wKindID;
		UnRegGameServer.wServerID=m_pGameServiceOption->wServerID;
		m_pCenterSocket->SendData(MDM_CS_SERVER_MANAGER,SUB_CS_UNREG_GAME_SERVER,&UnRegGameServer,sizeof(UnRegGameServer));
	}

	//�ر����
	m_pCenterSocket->CloseSocket(false);
	m_ServerUserManager.ResetUserManager();

	//ɾ������
	m_wMaxUserItem=0;
	SafeDeleteArray(m_pTableFrame);
	SafeDeleteArray(m_pNormalParameter);
	SafeDeleteArray(m_pAndroidParameter);

	//���Ʊ���
	m_bShallClose=false;
	m_bAllowWisper=true;
	m_bAllowRoomChat=true;
	m_bAllowGameChat=true;
	m_bAllowEnterRoom=true;
	m_bAllowEnterGame=true;

	//��Ϣ����
	m_cbRoomMsgIndex=0;
	m_cbGameMsgIndex=0;

	//���ñ���
	m_wColumnInfoSize=0;
	m_wOnLineInfoSize=0;
	memset(&m_ColumnInfo,0,sizeof(m_ColumnInfo));
	memset(&m_OnLineCountInfo,0,sizeof(m_OnLineCountInfo));

	return true;
}

//�¼�����ӿ�
bool __cdecl CAttemperEngineSink::OnAttemperEvent(WORD wIdentifier, void * pDataBuffer, WORD wDataSize, DWORD dwInsertTime)
{
	switch (wIdentifier)
	{
	case EVENT_CENTER_CONNECT:	//���������¼�
		{
			//Ч���С
			ASSERT(wDataSize==sizeof(NTY_CenterConnect));
			if (wDataSize!=sizeof(NTY_CenterConnect)) return false;

			//��Ϣ����
			NTY_CenterConnect * pCenterSocketConnect=(NTY_CenterConnect *)pDataBuffer;

			return OnEventCenterSocketConnect(pCenterSocketConnect->iErrorCode);
		}
	case EVENT_CENTER_READ:		//���Ķ�ȡ�¼�
		{
			//Ч���С
			NTY_CenterRead * pCenterSocketRead=(NTY_CenterRead *)pDataBuffer;
			ASSERT(wDataSize>=((sizeof(NTY_CenterRead)-sizeof(pCenterSocketRead->cbReadBuffer))));
			ASSERT(wDataSize==(sizeof(NTY_CenterRead)-sizeof(pCenterSocketRead->cbReadBuffer)+pCenterSocketRead->wDataSize));
			if (wDataSize<(sizeof(NTY_CenterRead)-sizeof(pCenterSocketRead->cbReadBuffer))) return false;
			if (wDataSize!=sizeof(NTY_CenterRead)-sizeof(pCenterSocketRead->cbReadBuffer)+pCenterSocketRead->wDataSize) return false;

			//������Ϣ
			bool bSuccess=false;
			try 
			{ 
				bSuccess=OnEventCenterSocketRead(pCenterSocketRead->Command,pCenterSocketRead->cbReadBuffer,pCenterSocketRead->wDataSize);
			}
			catch (...)	{ }
			if (bSuccess==false) m_pCenterSocket->CloseSocket(true);

			return true;
		}
	case EVENT_CENTER_CLOSE:		//���Ĺر��¼�
		{
			//Ч���С
			ASSERT(wDataSize==sizeof(NTY_CenterClose));
			if (wDataSize!=sizeof(NTY_CenterClose)) return false;

			//��Ϣ����
			NTY_CenterClose * pCenterSocketClose=(NTY_CenterClose *)pDataBuffer;
			OnEventCenterSocketClose(pCenterSocketClose->bCloseByServer);

			return true;
		}
	}

	return false;
}

//����״̬
bool __cdecl CAttemperEngineSink::SendTableStatus(WORD wTableID)
{
	//Ч�����
	ASSERT(wTableID<m_pGameServiceOption->wTableCount);
	if (wTableID>=m_pGameServiceOption->wTableCount) return false;

	//�������
	CMD_GR_TableStatus TableStatus;
	memset(&TableStatus,0,sizeof(TableStatus));
	TableStatus.wTableID=wTableID;
	TableStatus.bPlayStatus=(m_pTableFrame+wTableID)->IsGameStarted()?TRUE:FALSE;

	//��������
	m_pITCPSocketEngine->SendDataBatch(MDM_GR_STATUS,SUB_GR_TABLE_STATUS,&TableStatus,sizeof(TableStatus));

	return true;
}

//���ͷ���
bool __cdecl CAttemperEngineSink::SendUserScore(IServerUserItem * pIServerUserItem)
{
	tagServerUserData * pUserData=pIServerUserItem->GetUserData();

	//��������
	CMD_GR_UserScore UserScore;
	UserScore.dwUserID=pUserData->dwUserID;
	UserScore.UserScore=pUserData->UserScoreInfo;
	UserScore.UserScore.lScore=pUserData->UserScoreInfo.lScore+pUserData->lStorageScore;
	m_pITCPSocketEngine->SendDataBatch(MDM_GR_USER,SUB_GR_USER_SCORE,&UserScore,sizeof(UserScore));

	return true;
}

//����״̬
bool __cdecl CAttemperEngineSink::SendUserStatus(IServerUserItem * pIServerUserItem)
{
	//Ч�����
	ASSERT(pIServerUserItem!=NULL);
	ASSERT(pIServerUserItem->IsActive()==true);
	if (pIServerUserItem->IsActive()==false) return false;

	//��������
	CMD_GR_UserStatus UserStatus;
	memset(&UserStatus,0,sizeof(UserStatus));
	tagServerUserData * pUserData=pIServerUserItem->GetUserData();

	//��������
	UserStatus.dwUserID=pUserData->dwUserID;
	UserStatus.wTableID=pUserData->wTableID;
	UserStatus.wChairID=pUserData->wChairID;
	UserStatus.cbUserStatus=pUserData->cbUserStatus;

	//��������
	m_pITCPSocketEngine->SendDataBatch(MDM_GR_USER,SUB_GR_USER_STATUS,&UserStatus,sizeof(UserStatus));

	return true;
}

//ɾ���û�
bool __cdecl CAttemperEngineSink::DeleteUserItem(IServerUserItem * pIServerUserItem)
{
	//Ч�����
	ASSERT(pIServerUserItem!=NULL);
	if (pIServerUserItem==NULL) return false;

	//Ч��״̬
	ASSERT(pIServerUserItem->GetTableID()==INVALID_TABLE);
	ASSERT(pIServerUserItem->GetChairID()==INVALID_CHAIR);

	//д�����
	DBR_GR_LeaveGameServer LeaveGameServer;
	memset(&LeaveGameServer,0,sizeof(LeaveGameServer));
	LeaveGameServer.dwUserID=pIServerUserItem->GetUserID();
	LeaveGameServer.dwClientIP=pIServerUserItem->GetClientIP();
	LeaveGameServer.dwPlayTimeCount=pIServerUserItem->GetPlayTimeCount();
	LeaveGameServer.dwOnlineTimeCount=pIServerUserItem->GetOnlineTimeCount();
	pIServerUserItem->GetUserScoreInfo(LeaveGameServer.ScoreModifyInfo);
	m_DataBaseEvent.PostDataBaseEvent(DBR_GR_LEAVE_GAME_SERVER,0,0,&LeaveGameServer,sizeof(LeaveGameServer));

	//����״̬
	CMD_GR_UserStatus UserStatus;
	memset(&UserStatus,0,sizeof(UserStatus));
	tagServerUserData * pUserData=pIServerUserItem->GetUserData();
	UserStatus.dwUserID=pIServerUserItem->GetUserID();
	UserStatus.wTableID=INVALID_TABLE;
	UserStatus.wChairID=INVALID_CHAIR;
	UserStatus.cbUserStatus=US_NULL;
	m_pITCPSocketEngine->SendDataBatch(MDM_GR_USER,SUB_GR_USER_STATUS,&UserStatus,sizeof(UserStatus));

	//��������
	WORD wBindIndex=pIServerUserItem->GetUserIndex();
	if (wBindIndex<m_pGameServiceOption->wMaxConnect)
	{
		(m_pNormalParameter+wBindIndex)->pIServerUserItem=NULL;
	}
	else if ((wBindIndex>=INDEX_ANDROID)&&(wBindIndex<(INDEX_ANDROID+MAX_ANDROID)))
	{
		(m_pAndroidParameter+(wBindIndex-INDEX_ANDROID))->pIServerUserItem=NULL;
	}
	else
	{
		ASSERT(FALSE);
	}

	//ɾ���û�
	m_ServerUserManager.DeleteUserItem(pIServerUserItem);

	return true;
}

//��������
bool __cdecl CAttemperEngineSink::SendData(IServerUserItem * pIServerUserItem, WORD wMainCmdID, WORD wSubCmdID)
{
	//Ч�����
	ASSERT(pIServerUserItem!=NULL);
	ASSERT(pIServerUserItem->IsActive()==true);
	if (pIServerUserItem->IsActive()==false) return false;

	//��������
	WORD wIndex=pIServerUserItem->GetUserIndex();
	if (wIndex!=0xFFFF)
	{
		tagConnectItemInfo * pConnectItemInfo=GetBindParameter(wIndex);
		if (wIndex>=INDEX_ANDROID)
		{
			DWORD dwID=MAKELONG(wIndex,pConnectItemInfo->wRoundID);
		}
		else
		{
			m_pITCPSocketEngine->SendData(wIndex,pConnectItemInfo->wRoundID,wMainCmdID,wSubCmdID);
		}
	}

	return true;
}

//��������
bool __cdecl CAttemperEngineSink::SendData(IServerUserItem * pIServerUserItem, WORD wMainCmdID, WORD wSubCmdID, void * pData, WORD wDataSize)
{
	//Ч�����
	ASSERT(pIServerUserItem!=NULL);
	ASSERT(pIServerUserItem->IsActive()==true);
	if (pIServerUserItem->IsActive()==false) return false;

	//��������
	WORD wIndex=pIServerUserItem->GetUserIndex();
	if (wIndex!=0xFFFF)
	{
		tagConnectItemInfo * pConnectItemInfo=GetBindParameter(wIndex);
		if (wIndex>=INDEX_ANDROID)
		{
			DWORD dwID=MAKELONG(wIndex,pConnectItemInfo->wRoundID);
		}
		else
		{
			m_pITCPSocketEngine->SendData(wIndex,pConnectItemInfo->wRoundID,wMainCmdID,wSubCmdID,pData,wDataSize);
		}
	}

	return true;
}

//���ö�ʱ��
bool __cdecl CAttemperEngineSink::SetTableTimer(WORD wTableID, WORD wTimerID, DWORD dwElapse, DWORD dwRepeat, WPARAM wBindParam)
{
	//Ч�����
	ASSERT(wTimerID<RANGE_TABLE_TIME);
	ASSERT(wTableID<m_pGameServiceOption->wTableCount);

	//���ö�ʱ��
	if (wTableID>=m_pGameServiceOption->wTableCount) return false;
	WORD wTableTimeID=IDI_TABLE_FRAME_START+wTableID*RANGE_TABLE_TIME+wTimerID;
	return m_pITimerEngine->SetTimer(wTableTimeID,dwElapse,dwRepeat,wBindParam);
}

//ɾ����ʱ��
bool __cdecl CAttemperEngineSink::KillTableTimer(WORD wTableID, WORD wTimerID)
{
	//Ч�����
	ASSERT(wTimerID<RANGE_TABLE_TIME);
	ASSERT(wTableID<m_pGameServiceOption->wTableCount);

	//ɾ����ʱ��
	if (wTableID>=m_pGameServiceOption->wTableCount) return false;
	WORD wTableTimeID=IDI_TABLE_FRAME_START+wTableID*RANGE_TABLE_TIME+wTimerID;
	return m_pITimerEngine->KillTimer(wTableTimeID);
}

//�����Ϣ
void __cdecl CAttemperEngineSink::ExportInformation(LPCTSTR pszString, enTraceLevel TraceLevel)
{
	if (m_pIEventService!=NULL) m_pIEventService->ShowEventNotify(pszString,TraceLevel);
	return;
}

//�����¼�
bool CAttemperEngineSink::SetEventService(IUnknownEx * pIUnknownEx)
{
	ASSERT(pIUnknownEx!=NULL);
	m_pIEventService=GET_OBJECTPTR_INTERFACE(pIUnknownEx,IEventService);
	ASSERT(m_pIEventService!=NULL);

	return (m_pIEventService!=NULL);
}

//���ú���
bool CAttemperEngineSink::InitAttemperSink(tagAttemperSinkParameter * pAttemperSinkParameter, IUnknownEx * pIUnknownEx)
{
	//Ч�����
	ASSERT(pIUnknownEx!=NULL);
	ASSERT(pAttemperSinkParameter!=NULL);

	//���ñ���
	m_pCenterSocket=pAttemperSinkParameter->pCenterSocket;
	m_dwCenterServer=pAttemperSinkParameter->dwCenterServer;
	m_pIAttemperEngine=pAttemperSinkParameter->pIAttemperEngine;
	m_pGameServiceAttrib=pAttemperSinkParameter->pGameServiceAttrib;
	m_pGameServiceOption=pAttemperSinkParameter->pGameServiceOption;
	m_pIGameServiceManager=pAttemperSinkParameter->pIGameServiceManager;

	//��������
	IServiceEngine * pIServiceEngine=(IServiceEngine *)pIUnknownEx->QueryInterface(IID_IServiceEngine,VER_IServiceEngine);
	if (pIServiceEngine==NULL)
	{
		ExportInformation(TEXT("��ȡ�����������ʧ��"),Level_Exception);
		return false;
	}

	//��ʱ������
	m_pITimerEngine=(ITimerEngine *)pIServiceEngine->GetTimerEngine(IID_ITimerEngine,VER_ITimerEngine);
	if (m_pITimerEngine==NULL)
	{
		ExportInformation(TEXT("��ȡ��ʱ���������ʧ��"),Level_Exception);
		return false;
	}

	//��������
	m_pITCPSocketEngine=(ITCPSocketEngine *)pIServiceEngine->GetTCPSocketEngine(IID_ITCPSocketEngine,VER_ITCPSocketEngine);
	if (m_pITCPSocketEngine==NULL)
	{
		ExportInformation(TEXT("��ȡ�����������ʧ��"),Level_Exception);
		return false;
	}

	//���ݿ�����
	IDataBaseEngine * pIDataBaseEngine=(IDataBaseEngine *)pIServiceEngine->GetDataBaseEngine(IID_IDataBaseEngine,VER_IDataBaseEngine);
	if (pIDataBaseEngine==NULL)
	{
		ExportInformation(TEXT("��ȡ���ݿ��������ʧ��"),Level_Exception);
		return false;
	}

	//���ݿⴥ��
	IUnknownEx * pIQueueService=(IUnknownEx *)pIDataBaseEngine->GetQueueService(IID_IUnknownEx,VER_IUnknownEx);
	if (m_DataBaseEvent.SetQueueService(pIQueueService)==false)
	{
		ExportInformation(TEXT("��ȡ���ݿⴥ������ʧ��"),Level_Exception);
		return false;
	}

	return true;
}

//���͵�¼ʧ��
bool CAttemperEngineSink::SendLogonFailed(WORD wIndex, WORD wRoundID, LPCTSTR pszMessage, LONG lErrorCode)
{
	//��������
	CMD_GR_LogonError LogonError;
	LogonError.lErrorCode=lErrorCode;
	lstrcpyn(LogonError.szErrorDescribe,pszMessage,sizeof(LogonError.szErrorDescribe));
	WORD wDescribeSize=CountString(LogonError.szErrorDescribe);

	//��������
	WORD wSendSize=sizeof(LogonError)-sizeof(LogonError.szErrorDescribe)+wDescribeSize;
	if (wIndex>=INDEX_ANDROID)
	{
		DWORD dwID=MAKELONG(wIndex,wRoundID);
	}
	else m_pITCPSocketEngine->SendData(wIndex,wRoundID,MDM_GR_LOGON,SUB_GR_LOGON_ERROR,&LogonError,wSendSize);

	return true;
}

//���ͷ�����Ϣ
bool CAttemperEngineSink::SendRoomMessage(WORD wIndex, WORD wRoundID, LPCTSTR lpszMessage, WORD wMessageType)
{
	//�������ݰ�
	CMD_GR_Message Message;
	Message.wMessageType=wMessageType;
	lstrcpyn(Message.szContent,lpszMessage,CountArray(Message.szContent));
	Message.wMessageLength=CountString(Message.szContent);

	//��������
	WORD wSendSize=sizeof(Message)-sizeof(Message.szContent)+Message.wMessageLength*sizeof(TCHAR);
	if (wIndex==INDEX_ALL_SOCKET)
	{
		m_pITCPSocketEngine->SendDataBatch(MDM_GR_SYSTEM,SUB_GR_MESSAGE,&Message,wSendSize);
	}
	else
	{
		if (wIndex>=INDEX_ANDROID)
		{
			DWORD dwID=MAKELONG(wIndex,wRoundID);
		}
		else m_pITCPSocketEngine->SendData(wIndex,wRoundID,MDM_GR_SYSTEM,SUB_GR_MESSAGE,&Message,wSendSize);
	}

	return true;
}

//������Ϸ��Ϣ
bool CAttemperEngineSink::SendGameMessage(WORD wIndex, WORD wRoundID, LPCTSTR lpszMessage, WORD wMessageType)
{
	//�������ݰ�
	CMD_GF_Message Message;
	Message.wMessageType=wMessageType;
	lstrcpyn(Message.szContent,lpszMessage,CountArray(Message.szContent));
	Message.wMessageLength=CountString(Message.szContent);

	//��������
	WORD wSendSize=sizeof(Message)-sizeof(Message.szContent)+Message.wMessageLength*sizeof(TCHAR);
	if (wIndex==INDEX_ALL_SOCKET)
	{
		m_pITCPSocketEngine->SendDataBatch(MDM_GF_FRAME,SUB_GF_MESSAGE,&Message,wSendSize);
	}
	else
	{
		if (wIndex>=INDEX_ANDROID)
		{
			DWORD dwID=MAKELONG(wIndex,wRoundID);
		}
		else m_pITCPSocketEngine->SendData(wIndex,wRoundID,MDM_GF_FRAME,SUB_GF_MESSAGE,&Message,wSendSize);
	}

	return true;
}

//���ͷ�����Ϣ
bool CAttemperEngineSink::SendRoomMessage(IServerUserItem * pIServerUserItem, LPCTSTR lpszMessage, WORD wMessageType)
{
	//Ч���û�
	ASSERT(pIServerUserItem!=NULL);
	if (pIServerUserItem==NULL) return false;

	//��������
	WORD wIndex=pIServerUserItem->GetUserIndex();
	if (wIndex!=0xFFFF)
	{
		tagConnectItemInfo * pConnectItemInfo=GetBindParameter(wIndex);
		SendRoomMessage(wIndex,pConnectItemInfo->wRoundID,lpszMessage,wMessageType);
		return true;
	}

	return false;
}

//������Ϸ��Ϣ
bool CAttemperEngineSink::SendGameMessage(IServerUserItem * pIServerUserItem, LPCTSTR lpszMessage, WORD wMessageType)
{
	//Ч���û�
	ASSERT(pIServerUserItem!=NULL);
	if (pIServerUserItem==NULL) return false;

	//�û�����
	if ((pIServerUserItem->GetTableID()==INVALID_TABLE)||(pIServerUserItem->GetChairID()==INVALID_CHAIR)) return false;

	//��������
	WORD wIndex=pIServerUserItem->GetUserIndex();
	if (wIndex!=0xFFFF)
	{
		tagConnectItemInfo * pConnectItemInfo=GetBindParameter(wIndex);
		SendGameMessage(wIndex,pConnectItemInfo->wRoundID,lpszMessage,wMessageType);

		return true;
	}

	return false;
}

//��ʱ���¼�
bool __cdecl CAttemperEngineSink::OnEventTimer(WORD wTimerID, WPARAM wBindParam)
{
	//�ں˶�ʱ��
	if ((wTimerID>=IDI_ATTEMPER_START)&&(wTimerID<=IDI_ATTEMPER_CONCLUDE))
	{
		switch (wTimerID)
		{
		case IDI_CONNECT_CENTER_SERVER:		//���ӷ�����
			{
				m_pCenterSocket->Connect(m_dwCenterServer,PORT_CENTER_SERVER);
				return true;
			}
		case IDI_UPDATE_SERVER_LIST:		//�����б�
			{
				if (m_SocketState==SocketState_Connected)
				{
					m_pCenterSocket->SendData(MDM_CS_SERVER_LIST,SUB_CS_GET_SERVER_LIST,NULL,0);
				}
				return true;
			}
		case IDI_UPDATE_ONLINE_COUNT:		//��������
			{
				if (m_SocketState==SocketState_Connected)
				{
					CMD_CS_ServerOnLineCount ServerOnLineCount;
					ServerOnLineCount.wKindID=m_pGameServiceOption->wKindID;
					ServerOnLineCount.wServerID=m_pGameServiceOption->wServerID;
					ServerOnLineCount.dwOnLineCount=(m_ServerUserManager.GetOnLineCount()+m_ServerUserManager.GetOffLineCount());
					m_pCenterSocket->SendData(MDM_CS_SERVER_MANAGER,SUB_CS_SERVER_ONLINE_COUNT,&ServerOnLineCount,sizeof(ServerOnLineCount));
				}

				return true;
			}
		case IDI_SEND_SYSTEM_MESSAGE:		//ϵͳ��Ϣ
			{
				//��ȡĿ¼
				TCHAR szPath[MAX_PATH]=TEXT("");
				GetCurrentDirectory(sizeof(szPath),szPath);

				//��ȡ����
				TCHAR szFileName[MAX_PATH],szMessage[1024];
				_snprintf(szFileName,sizeof(szFileName),TEXT("%s\\GameService.ini"),szPath);
				
				//ѭ����Ϣ
				TCHAR szRoomMsgName[64],szGameMsgName[64];
				_snprintf(szRoomMsgName,sizeof(szRoomMsgName),TEXT("RoomMessage%d"),m_cbRoomMsgIndex++);
				_snprintf(szGameMsgName,sizeof(szGameMsgName),TEXT("GameMessage%d"),m_cbGameMsgIndex++);

				//ϵͳ��Ϣ
				GetPrivateProfileString(TEXT("Message"),szRoomMsgName,TEXT(""),szMessage,sizeof(szMessage),szFileName);
				if (szMessage[0]!=0) SendRoomMessage(INDEX_ALL_SOCKET,0,szMessage,SMT_INFO);
				else m_cbRoomMsgIndex=0;

				//��Ϸ��Ϣ
				GetPrivateProfileString(TEXT("Message"),szGameMsgName,TEXT(""),szMessage,sizeof(szMessage),szFileName);
				if (szMessage[0]!=0) SendGameMessage(INDEX_ALL_SOCKET,0,szMessage,SMT_INFO);
				else m_cbGameMsgIndex=0;

				return true;
			}
		}

		return false;
	}

	//���Ӷ�ʱ��
	if (wTimerID>=IDI_TABLE_FRAME_START)
	{
		//��������
		WORD wTableID=(wTimerID-IDI_TABLE_FRAME_START)/RANGE_TABLE_TIME;
		WORD wTableTimeID=(wTimerID-IDI_TABLE_FRAME_START)%RANGE_TABLE_TIME;

		//��ʱ������
		ASSERT(wTableID<m_pGameServiceOption->wTableCount);
		return (m_pTableFrame+wTableID)->OnEventTimer(wTableTimeID,wBindParam);
	}

	return false;
}

//���ݿ��¼�
bool __cdecl CAttemperEngineSink::OnEventDataBase(void * pDataBuffer, WORD wDataSize, NTY_DataBaseEvent * pDataBaseEvent)
{
	switch (pDataBaseEvent->wRequestID)
	{
	case DBR_GR_LOGON_SUCCESS:		//��¼�ɹ�
		{
			return OnDBLogonSuccess(pDataBuffer,wDataSize,pDataBaseEvent);
		}
	case DBR_GR_LOGON_ERROR:		//��¼ʧ��
		{
			return OnDBLogonError(pDataBuffer,wDataSize,pDataBaseEvent);
		}
	}

	return false;
}

//�û���¼�ɹ�
bool CAttemperEngineSink::OnDBLogonSuccess(void * pDataBuffer, WORD wDataSize, NTY_DataBaseEvent * pDataBaseEvent)
{
	//Ч�����
	ASSERT(pDataBaseEvent->wRequestID==DBR_GR_LOGON_SUCCESS);
	ASSERT(wDataSize==sizeof(DBR_GR_LogonSuccess));
	if (wDataSize!=sizeof(DBR_GR_LogonSuccess)) return false;

	//�ж�����
	tagConnectItemInfo * pConnectItemInfo=GetBindParameter(pDataBaseEvent->wIndex);
	if (pConnectItemInfo==NULL) return true;
	if (pConnectItemInfo->bConnect==false) return true;
	if (pConnectItemInfo->wRoundID!=pDataBaseEvent->wRoundID) return true;
	ASSERT(pConnectItemInfo->pIServerUserItem==NULL);

	//��Ϣ����
	DBR_GR_LogonSuccess * pLogonSuccess=(DBR_GR_LogonSuccess *)pDataBuffer;

	//�����ж�
	IServerUserItem * pIServerUserItem=m_ServerUserManager.SearchOnLineUser(pLogonSuccess->dwUserID);
	if (pIServerUserItem!=NULL) return false;

	//��������
	WORD wIndex=pDataBaseEvent->wIndex;
	WORD wRoundID=pDataBaseEvent->wRoundID;

	//״̬�ж�
	if ((m_bAllowEnterRoom==false)&&(pLogonSuccess->dwMasterRight==0L))
	{
		//������Ϣ
		LPCTSTR pszMessage=TEXT("��Ǹ������ϵͳά����ԭ�򣬱���Ϸ���䲻�����κ���ҵ�¼���룡");
		SendRoomMessage(wIndex,wRoundID,pszMessage,SMT_EJECT|SMT_INFO|SMT_INTERMIT_LINE|SMT_CLOSE_ROOM);

		//�������
		DBR_GR_LeaveGameServer LeaveGameServer;
		ZeroMemory(&LeaveGameServer,sizeof(LeaveGameServer));
		LeaveGameServer.dwUserID=pLogonSuccess->dwUserID;
		LeaveGameServer.dwClientIP=pConnectItemInfo->dwClientIP;
		m_DataBaseEvent.PostDataBaseEvent(DBR_GR_LEAVE_GAME_SERVER,0,0,&LeaveGameServer,sizeof(LeaveGameServer));

		return true;
	}

	//�ж���Ŀ
	DWORD dwUserCount=m_ServerUserManager.GetOnLineCount()+m_ServerUserManager.GetOffLineCount();
	if ((pLogonSuccess->cbMemberOrder==0)&&(pLogonSuccess->cbMasterOrder==0)&&((dwUserCount+50L)>=m_pGameServiceOption->wMaxConnect))
	{
		//������Ϣ
		LPCTSTR pszMessage=TEXT("��Ǹ������Ϸ�����Ѿ����ˣ���ֹ�ǻ�Ա��ҵ�¼���룡");
		SendRoomMessage(wIndex,wRoundID,pszMessage,SMT_EJECT|SMT_INFO|SMT_INTERMIT_LINE|SMT_CLOSE_ROOM);

		//�������
		DBR_GR_LeaveGameServer LeaveGameServer;
		ZeroMemory(&LeaveGameServer,sizeof(LeaveGameServer));
		LeaveGameServer.dwUserID=pLogonSuccess->dwUserID;
		LeaveGameServer.dwClientIP=pConnectItemInfo->dwClientIP;
		m_DataBaseEvent.PostDataBaseEvent(DBR_GR_LEAVE_GAME_SERVER,0,0,&LeaveGameServer,sizeof(LeaveGameServer));

		return true;
	}

	//�����û���Ϣ
	tagServerUserData ServerUserData;
	memset(&ServerUserData,0,sizeof(ServerUserData));
	ServerUserData.wFaceID=pLogonSuccess->wFaceID;
	ServerUserData.cbGender=pLogonSuccess->cbGender;
	ServerUserData.dwUserID=pLogonSuccess->dwUserID;
	ServerUserData.dwGameID=pLogonSuccess->dwGameID;
	ServerUserData.dwGroupID=pLogonSuccess->dwGroupID;
	ServerUserData.dwUserRight=pLogonSuccess->dwUserRight;
	ServerUserData.dwMasterRight=pLogonSuccess->dwMasterRight;
	ServerUserData.cbMemberOrder=pLogonSuccess->cbMemberOrder;
	ServerUserData.cbMasterOrder=pLogonSuccess->cbMasterOrder;
	ServerUserData.UserScoreInfo.lWinCount=pLogonSuccess->lWinCount;
	ServerUserData.UserScoreInfo.lLostCount=pLogonSuccess->lLostCount;
	ServerUserData.UserScoreInfo.lDrawCount=pLogonSuccess->lDrawCount;
	ServerUserData.UserScoreInfo.lFleeCount=pLogonSuccess->lFleeCount;
	ServerUserData.UserScoreInfo.lExperience=pLogonSuccess->lExperience;
	lstrcpyn(ServerUserData.szAccounts,pLogonSuccess->szAccounts,CountArray(ServerUserData.szAccounts));
	lstrcpyn(ServerUserData.szGroupName,pLogonSuccess->szGroupName,CountArray(ServerUserData.szGroupName));
	lstrcpyn(ServerUserData.szUnderWrite,pLogonSuccess->szUnderWrite,CountArray(ServerUserData.szUnderWrite));

	//��ȡ����
	ServerUserData.lStorageScore=0L;
	ServerUserData.UserScoreInfo.lScore=pLogonSuccess->lScore;

	//�洢����
	if ((m_pGameServiceOption->wServerType==GAME_GENRE_GOLD)&&(m_pGameServiceOption->lRestrictScore>0L))
	{
		if (pLogonSuccess->lScore>m_pGameServiceOption->lRestrictScore)
		{
			ServerUserData.UserScoreInfo.lScore=m_pGameServiceOption->lRestrictScore;
			ServerUserData.lStorageScore=pLogonSuccess->lScore-m_pGameServiceOption->lRestrictScore;
		}
	}

	//״̬��Ϣ
	ServerUserData.cbUserStatus=US_FREE;
	ServerUserData.wTableID=INVALID_TABLE;
	ServerUserData.wChairID=INVALID_CHAIR;

	//�����û�
	pConnectItemInfo->wRoundID=wRoundID;
	pConnectItemInfo->pIServerUserItem=m_ServerUserManager.ActiveUserItem(ServerUserData,pConnectItemInfo->dwClientIP,wIndex,pLogonSuccess->szPassWord);

	//���ͷ�����Ϣ
	SendGameServerInfo(pConnectItemInfo->pIServerUserItem,wIndex,wRoundID);

	//�㲥�û���Ϣ
	SendUserItem(pConnectItemInfo->pIServerUserItem,INDEX_ALL_SOCKET,0xFFFF);

	//������Ϣ
	LPCTSTR pszMessage=TEXT("�װ����û�����ӭ����ᱦ���飡");
	SendRoomMessage(wIndex,wRoundID,pszMessage,SMT_INFO);

	//��ϰ�ж�
	if (m_pGameServiceOption->wServerType&GAME_GENRE_EDUCATE)
	{
		LPCTSTR pszMessage=TEXT("��ע�⣬������Ϸ��ϰ���䣬�㽫�õ�һ����Ŀ��ģ����Ϸ�ң���Ϸ�ɼ��������¼�����ݿ⣡");
		SendRoomMessage(wIndex,wRoundID,pszMessage,SMT_INFO);
	}

	//�����ж�
	if (m_pGameServiceOption->wServerType&GAME_GENRE_MATCH)
	{
		LPCTSTR pszMessage=TEXT("��ע�⣬������Ϸ�������䣬�Ǳ���ѡ�ֽ������ڴ˷��������Ϸ��");
		SendRoomMessage(wIndex,wRoundID,pszMessage,SMT_INFO);
	}

	//������Ϣ
	if (m_bShallClose==true)
	{
		LPCTSTR pszMessage=TEXT("��ע�⣬������Ҫ������Ϸ����ά�����¹���������Ϸ���伴����ͣ����");
		SendRoomMessage(wIndex,wRoundID,pszMessage,SMT_INFO);
	}

	//����Ⱥ��
	if (wIndex<INDEX_ANDROID) m_pITCPSocketEngine->AllowBatchSend(wIndex,wRoundID,true);

	return true;
}

//�û���¼ʧ��
bool CAttemperEngineSink::OnDBLogonError(void * pDataBuffer, WORD wDataSize, NTY_DataBaseEvent * pDataBaseEvent)
{
	//�ж�����
	tagConnectItemInfo * pConnectItemInfo=GetBindParameter(pDataBaseEvent->wIndex);
	if (pConnectItemInfo==NULL) return true;
	if (pConnectItemInfo->bConnect==false) return true;
	if (pConnectItemInfo->wRoundID!=pDataBaseEvent->wRoundID) return true;

	//������Ϣ
	DBR_GR_LogonError * pLogonError=(DBR_GR_LogonError *)pDataBuffer;
	pLogonError->szErrorDescribe[CountString(pLogonError->szErrorDescribe)-1]=0;
	SendLogonFailed(pDataBaseEvent->wIndex,pDataBaseEvent->wRoundID,pLogonError->szErrorDescribe,pLogonError->lErrorCode);

	if (pDataBaseEvent->wIndex>=INDEX_ANDROID)
	{
		DWORD dwID=MAKELONG(pDataBaseEvent->wIndex,pConnectItemInfo->wRoundID);
	}
	else m_pITCPSocketEngine->ShutDownSocket(pDataBaseEvent->wIndex,pDataBaseEvent->wRoundID);

	return true;
}

//����Ӧ���¼�
bool __cdecl CAttemperEngineSink::OnEventSocketAccept(NTY_SocketAcceptEvent * pSocketAcceptEvent)
{
	tagConnectItemInfo * pConnectItemInfo=GetBindParameter(pSocketAcceptEvent->wIndex);
	if (pConnectItemInfo==NULL) return false;

	//��������
	pConnectItemInfo->bConnect=true;
	pConnectItemInfo->wRoundID=pSocketAcceptEvent->wRoundID;
	pConnectItemInfo->dwClientIP=pSocketAcceptEvent->dwClientIP;

	return true;
}

//�����¼�
bool CAttemperEngineSink::OnEventSocketRead(CMD_Command Command, void * pDataBuffer, WORD wDataSize, NTY_SocketReadEvent * pSocketReadEvent)
{
	switch (Command.wMainCmdID)
	{
	case MDM_GR_LOGON:	//��¼��Ϣ
		{
			return OnSocketMainLogon(Command,pDataBuffer,wDataSize,pSocketReadEvent);
		}
	case MDM_GR_USER:	//�û���Ϣ
		{
			return OnSocketMainUser(Command,pDataBuffer,wDataSize,pSocketReadEvent);
		}
	case MDM_GR_MANAGER://������Ϣ
		{
			return OnSocketMainManager(Command,pDataBuffer,wDataSize,pSocketReadEvent);
		}
	case MDM_GF_FRAME:	//�����Ϣ
		{
			return OnSocketMainFrame(Command,pDataBuffer,wDataSize,pSocketReadEvent);
		}
	case MDM_GF_GAME:	//��Ϸ��Ϣ
		{
			return OnSocketMainGame(Command,pDataBuffer,wDataSize,pSocketReadEvent);
		}
	case MDM_GF_VIDEO:	//��Ƶ��Ϣ
		{
			return OnSocketMainVideo(Command,pDataBuffer,wDataSize,pSocketReadEvent);
		}
	}

	return false;
}

//����ر��¼�
bool CAttemperEngineSink::OnEventSocketClose(NTY_SocketCloseEvent * pSocketCloseEvent)
{
	//�û�����
	tagConnectItemInfo * pConnectItemInfo=GetBindParameter(pSocketCloseEvent->wIndex);
	if (pConnectItemInfo==NULL) return true;
	IServerUserItem * pIServerUserItem=pConnectItemInfo->pIServerUserItem;
	if (pIServerUserItem!=NULL)
	{
		//�ж���Ϸ
		bool bOffLine=false;
		if (pIServerUserItem->GetTableID()!=INVALID_TABLE)
		{
			//��������
			CTableFrame * pTableFrame=(m_pTableFrame+pIServerUserItem->GetTableID());

			//����ע��
			WORD wChairID=pIServerUserItem->GetChairID();
			if ((pTableFrame->IsUserPlaying(pIServerUserItem)==true)&&(pTableFrame->OnUserReqOffLine(wChairID)==true))
			{
				bOffLine=m_ServerUserManager.RegOffLineUserItem(pIServerUserItem);
			}

			//���ߴ���
			if (bOffLine==true) pTableFrame->OnUserOffLine(wChairID);
			else pTableFrame->PerformStandUpAction(pIServerUserItem);
		}

		//ɾ���û�
		if (bOffLine==false) DeleteUserItem(pIServerUserItem);
	}

	//��������
	pConnectItemInfo->wRoundID++;
	pConnectItemInfo->dwClientIP=0;
	pConnectItemInfo->bConnect=false;
	pConnectItemInfo->pIServerUserItem=NULL;

	return true;
}

//���������¼�
bool __cdecl CAttemperEngineSink::OnEventCenterSocketConnect(int iErrorCode)
{
	//�����ж�
	if (iErrorCode!=0)
	{
		m_SocketState=SocketState_NoConnect;
		m_pITimerEngine->SetTimer(IDI_CONNECT_CENTER_SERVER,TIME_RECONNECT,1,NULL);
		return true;
	}

	//���ñ���
	m_SocketState=SocketState_Connected;

	//ע�᷿��
	CMD_CS_RegGameServer RegGameServer;
	memset(&RegGameServer,0,sizeof(RegGameServer));
	RegGameServer.GameServer.wSortID=0;
	RegGameServer.GameServer.wKindID=m_pGameServiceOption->wKindID;
	RegGameServer.GameServer.wServerID=m_pGameServiceOption->wServerID;
	RegGameServer.GameServer.wStationID=m_pGameServiceOption->wStationID;
	RegGameServer.GameServer.wServerPort=m_pGameServiceOption->wServerPort;
	RegGameServer.GameServer.dwServerAddr=m_pGameServiceOption->dwServerAddr;
	RegGameServer.GameServer.dwOnLineCount=(m_ServerUserManager.GetOnLineCount()+m_ServerUserManager.GetOffLineCount())*2;
	lstrcpyn(RegGameServer.GameServer.szServerName,m_pGameServiceOption->szGameRoomName,CountArray(RegGameServer.GameServer.szServerName));
	m_pCenterSocket->SendData(MDM_CS_SERVER_MANAGER,SUB_CS_REG_GAME_SERVER,&RegGameServer,sizeof(RegGameServer));

	//��ȡ�б�
	m_pCenterSocket->SendData(MDM_CS_SERVER_LIST,SUB_CS_GET_SERVER_LIST,NULL,0);

	//���ö�ʱ��
	m_pITimerEngine->SetTimer(IDI_UPDATE_SERVER_LIST,TIME_UPDATE_LIST,TIMER_REPEAT_TIMER,NULL);
	m_pITimerEngine->SetTimer(IDI_UPDATE_ONLINE_COUNT,TIME_UPDATE_ONLINE,TIMER_REPEAT_TIMER,NULL);

	return true;
}

//���Ķ�ȡ�¼�
bool __cdecl CAttemperEngineSink::OnEventCenterSocketRead(CMD_Command Command, void * pDataBuffer, WORD wDataSize)
{
	switch (Command.wMainCmdID)
	{
	case MDM_CS_SERVER_LIST:	//�б���Ϣ
		{
			return OnCenterMainServerList(Command,pDataBuffer,wDataSize);
		}
	}
	return true;
}

//���Ĺر��¼�
bool __cdecl CAttemperEngineSink::OnEventCenterSocketClose(bool bCloseByServer)
{
	//���ñ���
	m_SocketState=SocketState_NoConnect;

	//��������
	m_pITimerEngine->KillTimer(IDI_UPDATE_SERVER_LIST);
	m_pITimerEngine->KillTimer(IDI_UPDATE_ONLINE_COUNT);
	m_pITimerEngine->SetTimer(IDI_CONNECT_CENTER_SERVER,TIME_RECONNECT,1,NULL);

	return true;
}

//��¼��Ϣ����
bool CAttemperEngineSink::OnSocketMainLogon(CMD_Command Command, void * pDataBuffer, WORD wDataSize, NTY_SocketReadEvent * pSocketReadEvent)
{
	switch (Command.wSubCmdID)
	{
	case SUB_GR_LOGON_USERID:		//ID ��¼
		{
			//������Ϣ
			CMD_GR_LogonByUserID * pLogonByUserID=(CMD_GR_LogonByUserID *)pDataBuffer;
			pLogonByUserID->szPassWord[CountArray(pLogonByUserID->szPassWord)-1]=0;

			//�ظ��ж�
			tagConnectItemInfo * pConnectItemInfo=GetBindParameter(pSocketReadEvent->wIndex);
			if (pConnectItemInfo==NULL) return false;
			IServerUserItem * pIServerUserItem=GetServerUserItem(pSocketReadEvent->wIndex);
			if (pIServerUserItem!=NULL) return false;

			//�����ж�
			pIServerUserItem=m_ServerUserManager.SearchOnLineUser(pLogonByUserID->dwUserID);
			if (pIServerUserItem!=NULL)
			{
				//Ч������
				if (lstrcmp(pIServerUserItem->GetPassword(),pLogonByUserID->szPassWord)!=0)
				{
					TCHAR szMessage[]=TEXT("�ʻ������������֤���ٴγ��Ե�¼��");
					SendLogonFailed(pSocketReadEvent->wIndex,pSocketReadEvent->wRoundID,szMessage,0);

					if (pSocketReadEvent->wIndex>=INDEX_ANDROID)
					{
						DWORD dwID=MAKELONG(pSocketReadEvent->wIndex,pSocketReadEvent->wRoundID);
					}
					else m_pITCPSocketEngine->ShutDownSocket(pSocketReadEvent->wIndex,pSocketReadEvent->wRoundID);

					return true;
				}

				//����֪ͨ
				WORD wSourceIndex=pIServerUserItem->GetUserIndex();
				tagConnectItemInfo * pConnectItemInfo=GetBindParameter(wSourceIndex);
				if (pConnectItemInfo!=NULL)
				{
					WORD wSourceRoundID=pConnectItemInfo->wRoundID;
					LPCTSTR pszMessage=TEXT("��ע�⣬����ʺ�����һ�ط��������Ϸ�����ˣ��㱻���뿪��");
					SendRoomMessage(wSourceIndex,wSourceRoundID,pszMessage,SMT_INFO|SMT_EJECT|SMT_GLOBAL|SMT_CLOSE_ROOM);

					//�Ͽ�ԭ�û�
					pConnectItemInfo->pIServerUserItem=NULL;

					if (wSourceIndex>=INDEX_ANDROID)
					{
						DWORD dwID=MAKELONG(wSourceIndex,wSourceRoundID);
					}
					else m_pITCPSocketEngine->ShutDownSocket(wSourceIndex,wSourceRoundID);
				}

				//�������û�
				pConnectItemInfo->pIServerUserItem=pIServerUserItem;
				pConnectItemInfo->wRoundID=pSocketReadEvent->wRoundID;
				m_ServerUserManager.SwitchOnLineUserItem(pIServerUserItem,pConnectItemInfo->dwClientIP,pSocketReadEvent->wIndex);

				//���ͷ�����Ϣ
				SendGameServerInfo(pIServerUserItem,pSocketReadEvent->wIndex,pSocketReadEvent->wRoundID);

				//����Ⱥ��
				if (pSocketReadEvent->wIndex<INDEX_ANDROID)
				{
					m_pITCPSocketEngine->AllowBatchSend(pSocketReadEvent->wIndex,pSocketReadEvent->wRoundID,true);
				}

				return true;
			}

			//�����ж�
			pIServerUserItem=m_ServerUserManager.SearchOffLineUser(pLogonByUserID->dwUserID);
			if (pIServerUserItem!=NULL)
			{
				//Ч������
				if (lstrcmp(pIServerUserItem->GetPassword(),pLogonByUserID->szPassWord)!=0)
				{
					TCHAR szMessage[]=TEXT("�ʻ������������֤���ٴγ��Ե�¼��");
					SendLogonFailed(pSocketReadEvent->wIndex,pSocketReadEvent->wRoundID,szMessage,0);

					if (pSocketReadEvent->wIndex>=INDEX_ANDROID)
					{
						DWORD dwID=MAKELONG(pSocketReadEvent->wIndex,pSocketReadEvent->wRoundID);
					}
					else m_pITCPSocketEngine->ShutDownSocket(pSocketReadEvent->wIndex,pSocketReadEvent->wRoundID);

					return true;
				}

				//�����û�
				pConnectItemInfo->pIServerUserItem=pIServerUserItem;
				pConnectItemInfo->wRoundID=pSocketReadEvent->wRoundID;
				m_ServerUserManager.ActiveOffLineUserItem(pIServerUserItem,pConnectItemInfo->dwClientIP,pSocketReadEvent->wIndex);

				//��������
				WORD wTableID=pIServerUserItem->GetTableID();
				WORD wChairID=pIServerUserItem->GetChairID();
				(m_pTableFrame+wTableID)->OnUserReConnect(wChairID);

				//���ͷ�����Ϣ
				SendGameServerInfo(pIServerUserItem,pSocketReadEvent->wIndex,pSocketReadEvent->wRoundID);

				//����Ⱥ��
				if (pSocketReadEvent->wIndex<INDEX_ANDROID)
				{
					m_pITCPSocketEngine->AllowBatchSend(pSocketReadEvent->wIndex,pSocketReadEvent->wRoundID,true);
				}

				return true;
			}

			//��������
			DBR_GR_LogonByUserID LogonByUserID;
			memset(&LogonByUserID,0,sizeof(LogonByUserID));
			LogonByUserID.dwUserID=pLogonByUserID->dwUserID;
			LogonByUserID.dwClientIP=pConnectItemInfo->dwClientIP;
			lstrcpyn(LogonByUserID.szPassWord,pLogonByUserID->szPassWord,sizeof(LogonByUserID.szPassWord));

			//��������
			VOID * pDataBuffer=NULL;
			tagDataDescribe DataDescribe;
			CRecvPacketHelper RecvPacket(pLogonByUserID+1,wDataSize-sizeof(CMD_GR_LogonByUserID));

			//��չ��Ϣ
			while (true)
			{
				//��ȡ����
				pDataBuffer=RecvPacket.GetData(DataDescribe);
				if (DataDescribe.wDataDescribe==DTP_NULL) break;

				//���ݷ���
				switch (DataDescribe.wDataDescribe)
				{
				case DTP_COMPUTER_ID:		//������ʶ
					{
						if (DataDescribe.wDataSize==sizeof(tagClientSerial))
						{
							BYTE * pcbByte=(BYTE *)pDataBuffer;
							for (INT i=0;i<sizeof(tagClientSerial)/sizeof(BYTE);i++)
							{
								_stprintf(&LogonByUserID.szComputerID[i*2],TEXT("%02X"),*(pcbByte+i));
							}
						}

						break;
					}
				}
			}

			//Ͷ�����ݿ�
			m_DataBaseEvent.PostDataBaseEvent(DBR_GR_LOGON_BY_USERID,pSocketReadEvent->wIndex,
				pSocketReadEvent->wRoundID,&LogonByUserID,sizeof(LogonByUserID));

			return true;
		}
	}

	return false;
}

//�û���Ϣ����
bool CAttemperEngineSink::OnSocketMainUser(CMD_Command Command, void * pDataBuffer, WORD wDataSize, NTY_SocketReadEvent * pSocketReadEvent)
{
	switch (Command.wSubCmdID)
	{
	case SUB_GR_USER_SIT_REQ:		//��������
	case SUB_GR_USER_LOOKON_REQ:	//�Թ�����
		{
			//��������
			CMD_GR_UserSitReq * pUserSitReq=(CMD_GR_UserSitReq *)pDataBuffer;
			WORD wHeadSize=sizeof(CMD_GR_UserSitReq)-sizeof(pUserSitReq->szTablePass);
				
			//�ж�λ��
			if (pUserSitReq->wTableID>=m_pGameServiceOption->wTableCount) return false;
			if (pUserSitReq->wChairID>=m_pGameServiceAttrib->wChairCount) return false;

			//��ȡ�û�
			IServerUserItem * pIServerUserItem=GetServerUserItem(pSocketReadEvent->wIndex);
			if (pIServerUserItem==NULL) return false;

			//�������
			tagServerUserData * pUserData=pIServerUserItem->GetUserData();
			if ((pUserData->wTableID==pUserSitReq->wTableID)&&(pUserData->wChairID==pUserSitReq->wChairID))
			{
				if ((pUserData->cbUserStatus!=US_LOOKON)&&(Command.wSubCmdID==SUB_GR_USER_SIT_REQ)) return true;
				if ((pUserData->cbUserStatus==US_LOOKON)&&(Command.wSubCmdID==SUB_GR_USER_LOOKON_REQ)) return true;
			}

			//�뿪λ��
			if (pUserData->wTableID!=INVALID_TABLE)
			{
				CTableFrame * pTableFrame=(m_pTableFrame+pUserData->wTableID);
				if (pTableFrame->IsUserPlaying(pIServerUserItem)==true)
				{
					//��������
					CMD_GR_SitFailed SitFailed;
					memset(&SitFailed,0,sizeof(SitFailed));
					_snprintf(SitFailed.szFailedDescribe,sizeof(SitFailed.szFailedDescribe),TEXT("�����ڵ� [ %d ] ����Ϸ����Ϸ����ʱ�����뿪λ�ã�"),pUserData->wTableID+1);

					//��������
					WORD wSendSize=sizeof(SitFailed)-sizeof(SitFailed.szFailedDescribe)+CountString(SitFailed.szFailedDescribe);
					SendData(pIServerUserItem,MDM_GR_USER,SUB_GR_SIT_FAILED,&SitFailed,wSendSize);

					return true;
				}
				pTableFrame->PerformStandUpAction(pIServerUserItem);
			}

			//����λ��
			CTableFrame * pTableFrame=(m_pTableFrame+pUserSitReq->wTableID);
			if (Command.wSubCmdID==SUB_GR_USER_SIT_REQ)	
			{
				pTableFrame->PerformSitDownAction(pUserSitReq->wChairID,pIServerUserItem);
			}
			else
			{
				pTableFrame->PerformLookonAction(pUserSitReq->wChairID,pIServerUserItem);
			}

			return true;
		}
	case SUB_GR_USER_STANDUP_REQ:	//��������
	case SUB_GR_USER_LEFT_GAME_REQ:	//ǿ������
		{
			//��ȡ�û�
			IServerUserItem * pIServerUserItem=GetServerUserItem(pSocketReadEvent->wIndex);
			if (pIServerUserItem==NULL) return false;

			//�������
			tagServerUserData * pUserData=pIServerUserItem->GetUserData();
			if ((pUserData->wTableID==INVALID_TABLE)||(pUserData->wChairID==INVALID_CHAIR)) return true;

			//����λ��
			CTableFrame * pTableFrame=(m_pTableFrame+pUserData->wTableID);
			if ((Command.wSubCmdID==SUB_GR_USER_STANDUP_REQ)&&(pTableFrame->IsUserPlaying(pIServerUserItem)==true))
			{
				TCHAR szMessage[256]=TEXT("");
				_snprintf(szMessage,sizeof(szMessage),TEXT("�����ڵ� [ %d ] ����Ϸ����Ϸ����ʱ�����뿪λ�ã�"),pUserData->wTableID+1);
				SendRoomMessage(pSocketReadEvent->wIndex,pSocketReadEvent->wRoundID,szMessage,SMT_EJECT);
				return true;
			}

			//�뿪λ��
			pTableFrame->PerformStandUpAction(pIServerUserItem);

			return true;
		}
	case SUB_GR_USER_RULE:		//�û�����
		{
			//��Ϣ����
			CMD_GR_UserRule * pUserRule=(CMD_GR_UserRule *)pDataBuffer;
			pUserRule->szPassword[CountArray(pUserRule->szPassword)-1]=0;

			//��ȡ�û�
			IServerUserItem * pIServerUserItem=GetServerUserItem(pSocketReadEvent->wIndex);
			if (pIServerUserItem==NULL) return false;

			//�������
			tagUserRule UserRule;
			UserRule.bLimitWin=pUserRule->bLimitWin;
			UserRule.bPassword=pUserRule->bPassword;
			UserRule.bLimitFlee=pUserRule->bLimitFlee;
			UserRule.bLimitScore=pUserRule->bLimitScore;
			UserRule.bCheckSameIP=pUserRule->bCheckSameIP;
			UserRule.wWinRate=pUserRule->wWinRate;
			UserRule.wFleeRate=pUserRule->wFleeRate;
			UserRule.lMaxScore=pUserRule->lMaxScore;
			UserRule.lLessScore=pUserRule->lLessScore;
			lstrcpyn(UserRule.szPassword,pUserRule->szPassword,CountArray(UserRule.szPassword));

			//���ù���
			pIServerUserItem->SetUserRule(UserRule);

			return true;
		}

	case SUB_GR_USER_INVITE_REQ:		//�����û�
		{
			//��Ϣ����
			CMD_GR_UserInviteReq * pUserInviteReq=(CMD_GR_UserInviteReq *)pDataBuffer;

			//��ȡ�û�
			IServerUserItem * pIServerUserItem=GetServerUserItem(pSocketReadEvent->wIndex);
			if (pIServerUserItem==NULL) return false;

			//Ч��״̬
			if (pUserInviteReq->wTableID==INVALID_TABLE) return true;
			if (pIServerUserItem->GetTableID()!=pUserInviteReq->wTableID) return true;

			//Ŀ���û�
			IServerUserItem * pITargetUserItem=m_ServerUserManager.SearchOnLineUser(pUserInviteReq->dwUserID);
			if (pITargetUserItem==NULL) return true;

			//������Ϣ
			CMD_GR_UserInvite UserInvite;
			memset(&UserInvite,0,sizeof(UserInvite));
			UserInvite.wTableID=pUserInviteReq->wTableID;
			UserInvite.dwUserID=pIServerUserItem->GetUserID();
			SendData(pITargetUserItem,MDM_GR_USER,SUB_GR_USER_INVITE,&UserInvite,sizeof(UserInvite));

			return true;
		}
	}

	return true;
}

//������Ϣ����
bool CAttemperEngineSink::OnSocketMainManager(CMD_Command Command, void * pDataBuffer, WORD wDataSize, NTY_SocketReadEvent * pSocketReadEvent)
{
	//��Ϣ����
	switch (Command.wSubCmdID)
	{
	case SUB_GR_LOOK_USER_IP:	//�鿴��ַ
		{
			//Ч������
			ASSERT(wDataSize==sizeof(CMD_GR_LookUserIP));
			if (wDataSize!=sizeof(CMD_GR_LookUserIP)) return false;

			//��Ϣ����
			CMD_GR_LookUserIP * pLookUserIP=(CMD_GR_LookUserIP *)pDataBuffer;

			//�����û�
			IServerUserItem * pIServerUserItemSend=GetServerUserItem(pSocketReadEvent->wIndex);

			//Ŀ���û�
			IServerUserItem * pIServerUserItemRecv=m_ServerUserManager.SearchOnLineUser(pLookUserIP->dwTargetUserID);

			//��������
			DWORD dwUserIP=pIServerUserItemRecv->GetClientIP();

			//������Ϣ
			TCHAR szMessage[128]=TEXT("");
			BYTE * pcbUserIP=(BYTE *)(&dwUserIP);
			_snprintf(szMessage,CountArray(szMessage),TEXT("[ %s ]��%d.%d.%d.%d"),pIServerUserItemRecv->GetAccounts(),
				pcbUserIP[0],pcbUserIP[1],pcbUserIP[2],pcbUserIP[3]);

			//������Ϣ
			SendRoomMessage(pIServerUserItemSend,szMessage,SMT_INFO);

			return true;
		}
	case SUB_GR_KILL_USER:		//�߳��û�
		{
			//Ч������
			ASSERT(wDataSize==sizeof(CMD_GR_KillUser));
			if (wDataSize!=sizeof(CMD_GR_KillUser)) return false;

			//��Ϣ����
			CMD_GR_KillUser * pKillUser=(CMD_GR_KillUser *)pDataBuffer;

			//�����û�
			IServerUserItem * pIServerUserItemSend=GetServerUserItem(pSocketReadEvent->wIndex);

			//Ŀ���û�
			IServerUserItem * pIServerUserItemRecv=m_ServerUserManager.SearchOnLineUser(pKillUser->dwTargetUserID);
			if (pIServerUserItemRecv==NULL) return true;

			//������Ϣ
			LPCTSTR szMessage=TEXT("��Ǹ����������Ա�߳����䣬�����κ����ʣ�����ϵ��Ϸ�ͷ���");
			SendRoomMessage(pIServerUserItemRecv,szMessage,SMT_INFO|SMT_EJECT|SMT_INTERMIT_LINE);

			return true;
		}
	case SUB_GR_LIMIT_ACCOUNS:	//�����ʻ�
		{
			//Ч������
			ASSERT(wDataSize==sizeof(CMD_GR_LimitAccounts));
			if (wDataSize!=sizeof(CMD_GR_LimitAccounts)) return false;

			//��Ϣ����
			CMD_GR_LimitAccounts * pLimitAccounts=(CMD_GR_LimitAccounts *)pDataBuffer;

			//�����û�
			IServerUserItem * pIServerUserItemSend=GetServerUserItem(pSocketReadEvent->wIndex);
			IServerUserItem * pIServerUserItemRecv=m_ServerUserManager.SearchOnLineUser(pLimitAccounts->dwTargetUserID);

			//Ͷ�����ݿ�
			DBR_GR_LimitAccounts LimitAccounts;
			LimitAccounts.dwUserID=pLimitAccounts->dwTargetUserID;
			LimitAccounts.dwMasterUserID=pIServerUserItemSend->GetUserID();
			LimitAccounts.dwMasterClientIP=pIServerUserItemSend->GetClientIP();
			m_DataBaseEvent.PostDataBaseEvent(DBR_GR_LIMIT_ACCOUNTS,0,0,&LimitAccounts,sizeof(LimitAccounts));

			//������Ϣ
			LPCTSTR szMessage=TEXT("��Ǹ�������ʺű������ˣ������κ����ʣ�����ϵ��Ϸ�ͷ���");
			SendRoomMessage(pIServerUserItemRecv,szMessage,SMT_INFO|SMT_EJECT|SMT_INTERMIT_LINE);

			return true;
		}
	case SUB_GR_SET_USER_RIGHT:	//�û�Ȩ��
		{
			//��Ϣ����
			CMD_GR_SetUserRight * pSetUserRight=(CMD_GR_SetUserRight *)pDataBuffer;

			//�����û�
			IServerUserItem * pIServerUserItemSend=GetServerUserItem(pSocketReadEvent->wIndex);
			IServerUserItem * pIServerUserItemRecv=m_ServerUserManager.SearchOnLineUser(pSetUserRight->dwTargetUserID);

			//Ȩ���ж�
			DWORD dwMasterRight=pIServerUserItemSend->GetUserData()->dwMasterRight;
			if (dwMasterRight==0L) return true;

			//��ȡȨ��
			tagServerUserData * pUserData=pIServerUserItemRecv->GetUserData();

			//Ȩ������
			if (CUserRight::CanLimitPlay(dwMasterRight)==true)
			{
				if (pSetUserRight->cbLimitPlayGame==TRUE) pUserData->dwUserRight|=UR_CANNOT_PLAY;
				else pUserData->dwUserRight&=~UR_CANNOT_PLAY;
			}
			if (CUserRight::CanLimitLookon(dwMasterRight)==true)
			{
				if (pSetUserRight->cbLimitLookonGame==TRUE) pUserData->dwUserRight|=UR_CANNOT_LOOKON;
				else pUserData->dwUserRight&=~UR_CANNOT_LOOKON;
			}
			if (CUserRight::CanLimitWisper(dwMasterRight)==true)
			{
				if (pSetUserRight->cbLimitSendWisper==TRUE) pUserData->dwUserRight|=UR_CANNOT_WISPER;
				else pUserData->dwUserRight&=~UR_CANNOT_WISPER;
			}
			if (CUserRight::CanLimitRoomChat(dwMasterRight)==true)
			{
				if (pSetUserRight->cbLimitRoomChat==TRUE) pUserData->dwUserRight|=UR_CANNOT_ROOM_CHAT;
				else pUserData->dwUserRight&=~UR_CANNOT_ROOM_CHAT;
			}
			if (CUserRight::CanLimitGameChat(dwMasterRight)==true)
			{
				if (pSetUserRight->cbLimitGameChat==TRUE) pUserData->dwUserRight|=UR_CANNOT_GAME_CHAT;
				else pUserData->dwUserRight&=~UR_CANNOT_GAME_CHAT;
			}

			//����Ȩ��
			DBR_GR_SetUserRight SetUserRight;
			SetUserRight.dwUserRight=pUserData->dwUserRight;
			SetUserRight.dwUserID=pSetUserRight->dwTargetUserID;
			SetUserRight.dwMasterUserID=pIServerUserItemSend->GetUserID();
			SetUserRight.dwMasterClientIP=pIServerUserItemSend->GetClientIP();
			SetUserRight.cbGame=(CUserRight::CanBindGame(dwMasterRight)==true)?TRUE:FALSE;
			SetUserRight.cbAccounts=(CUserRight::CanBindGlobal(dwMasterRight)==true)?TRUE:FALSE;

			//Ͷ������
			if ((SetUserRight.cbAccounts==TRUE)||(SetUserRight.cbGame==TRUE))
			{
				m_DataBaseEvent.PostDataBaseEvent(DBR_GR_SET_USER_RIGHT,0,0,&SetUserRight,sizeof(SetUserRight));
			}

			return true;
		}
	case SUB_GR_OPTION_SERVER:	//��������
		{
			//Ч������
			ASSERT(wDataSize==sizeof(CMD_GR_OptionServer));
			if (wDataSize!=sizeof(CMD_GR_OptionServer)) return false;

			//��Ϣ����
			CMD_GR_OptionServer * pOptionServer=(CMD_GR_OptionServer *)pDataBuffer;

			//�����û�
			IServerUserItem * pIServerUserItemSend=GetServerUserItem(pSocketReadEvent->wIndex);
			if (pIServerUserItemSend==NULL) return false;

			//Ȩ���ж�
			DWORD dwMasterRight=pIServerUserItemSend->GetUserData()->dwMasterRight;
			if (CUserRight::CanServerOption(dwMasterRight)==false) return true;

			//��������
			if (pOptionServer->cbOptionFlags==OSF_ROOM_CHAT)
			{
				m_bAllowRoomChat=(pOptionServer->cbOptionValue==TRUE)?true:false;
			}

			//��Ϸ����
			if (pOptionServer->cbOptionFlags==OSF_GAME_CHAT)
			{
				m_bAllowGameChat=(pOptionServer->cbOptionValue==TRUE)?true:false;
			}

			//����˽��
			if (pOptionServer->cbOptionFlags==OSF_ROOM_WISPER)
			{
				m_bAllowWisper=(pOptionServer->cbOptionValue==TRUE)?true:false;
			}

			//������Ϸ
			if (pOptionServer->cbOptionFlags==OSF_ENTER_GAME)
			{
				m_bAllowEnterGame=(pOptionServer->cbOptionValue==TRUE)?true:false;
			}

			//���뷿��
			if (pOptionServer->cbOptionFlags==OSF_ENTER_ROOM)
			{
				m_bAllowEnterRoom=(pOptionServer->cbOptionValue==TRUE)?true:false;
			}

			//�����ر�
			if (pOptionServer->cbOptionFlags==OSF_SHALL_CLOSE)
			{
				m_bShallClose=(pOptionServer->cbOptionValue==TRUE)?true:false;
			}

			//������Ϣ
			LPCTSTR pszMessage=TEXT("�������������ò���ѡ�����óɹ���");
			SendRoomMessage(pIServerUserItemSend,pszMessage,SMT_INFO);

			return true;
		}
	}

	return false;
}

//�����Ϣ����
bool CAttemperEngineSink::OnSocketMainFrame(CMD_Command Command, void * pDataBuffer, WORD wDataSize, NTY_SocketReadEvent * pSocketReadEvent)
{
	//��ȡ�û�
	IServerUserItem * pIServerUserItem=GetServerUserItem(pSocketReadEvent->wIndex);

	//�������
	tagServerUserData * pUserData=pIServerUserItem->GetUserData();

	//��Ϣ���� 
	CTableFrame * pTableFrame=(m_pTableFrame+pUserData->wTableID);
	return pTableFrame->OnEventSocketFrame(Command.wSubCmdID,pDataBuffer,wDataSize,pIServerUserItem);
}

//��Ϸ��Ϣ����
bool CAttemperEngineSink::OnSocketMainGame(CMD_Command Command, void * pDataBuffer, WORD wDataSize, NTY_SocketReadEvent * pSocketReadEvent)
{
	//Ч�����
	ASSERT(Command.wMainCmdID==MDM_GF_GAME);

	//��ȡ�û�
	IServerUserItem * pIServerUserItem=GetServerUserItem(pSocketReadEvent->wIndex);
	if (pIServerUserItem==NULL) return false;

	//�������
	tagServerUserData * pUserData=pIServerUserItem->GetUserData();
	if ((pUserData->wTableID==INVALID_TABLE)||(pUserData->wChairID==INVALID_CHAIR)) return true;

	//��Ϣ���� 
	CTableFrame * pTableFrame=(m_pTableFrame+pUserData->wTableID);
	return pTableFrame->OnEventSocketGame(Command.wSubCmdID,pDataBuffer,wDataSize,pIServerUserItem);
}

//��Ƶ��Ϣ����
bool CAttemperEngineSink::OnSocketMainVideo(CMD_Command Command, void * pDataBuffer, WORD wDataSize, NTY_SocketReadEvent * pSocketReadEvent)
{
	//Ч�����
	ASSERT(Command.wMainCmdID==MDM_GF_VIDEO);

	//��ȡ�û�
	IServerUserItem * pIServerUserItem=GetServerUserItem(pSocketReadEvent->wIndex);
	if (pIServerUserItem==NULL) return false;

	//�������
	tagServerUserData * pUserData=pIServerUserItem->GetUserData();
	if ((pUserData->wTableID==INVALID_TABLE)||(pUserData->wChairID==INVALID_CHAIR)) return true;

	//��Ϣ���� 
	CTableFrame * pTableFrame=(m_pTableFrame+pUserData->wTableID);
	return pTableFrame->OnEventSocketVideo(Command.wSubCmdID,pDataBuffer,wDataSize,pIServerUserItem);
}

//�����û�
bool CAttemperEngineSink::SendUserItem(IServerUserItem * pIServerUserItem, WORD wTargetIndex, WORD wTargetRoundID)
{
	//Ч�����
	ASSERT(pIServerUserItem!=NULL);

	//��������
	BYTE cbBuffer[SOCKET_PACKAGE];
	tagUserInfoHead * pUserInfoHead=(tagUserInfoHead *)cbBuffer;
	tagServerUserData * pUserData=pIServerUserItem->GetUserData();

	//��д����
	memset(pUserInfoHead,0,sizeof(tagUserInfoHead));
	pUserInfoHead->wFaceID=pUserData->wFaceID;
	pUserInfoHead->wTableID=pUserData->wTableID;
	pUserInfoHead->wChairID=pUserData->wChairID;
	pUserInfoHead->cbGender=pUserData->cbGender;
	pUserInfoHead->cbUserStatus=pUserData->cbUserStatus;
	pUserInfoHead->dwUserID=pUserData->dwUserID;
	pUserInfoHead->dwGameID=pUserData->dwGameID;
	pUserInfoHead->dwGroupID=pUserData->dwGroupID;
	pUserInfoHead->dwUserRight=pUserData->dwUserRight;
	pUserInfoHead->dwMasterRight=pUserData->dwMasterRight;
	pUserInfoHead->cbGender=pUserData->cbGender;
	pUserInfoHead->cbMemberOrder=pUserData->cbMemberOrder;
	pUserInfoHead->cbMasterOrder=pUserData->cbMasterOrder;
	pUserInfoHead->UserScoreInfo=pUserData->UserScoreInfo;
	pUserInfoHead->UserScoreInfo.lScore=pUserData->UserScoreInfo.lScore+pUserData->lStorageScore;

	//��������
	CSendPacketHelper SendPacket(cbBuffer+sizeof(tagUserInfoHead),sizeof(cbBuffer)-sizeof(tagUserInfoHead));
	SendPacket.AddPacket(pUserData->szAccounts,CountString(pUserData->szAccounts),DTP_USER_ACCOUNTS);
	if (pUserData->szUnderWrite[0]!=0) SendPacket.AddPacket(pUserData->szUnderWrite,CountString(pUserData->szUnderWrite),DTP_UNDER_WRITE);
	if (pUserData->szGroupName[0]!=0) SendPacket.AddPacket(pUserData->szGroupName,CountString(pUserData->szGroupName),DTP_USER_GROUP_NAME);

	//��������
	WORD wSendLength=sizeof(tagUserInfoHead)+SendPacket.GetDataSize();
	if (wTargetIndex!=INDEX_ALL_SOCKET) 
	{
		if (wTargetIndex>=INDEX_ANDROID)
		{
			DWORD dwID=MAKELONG(wTargetIndex,wTargetRoundID);
		}
		else m_pITCPSocketEngine->SendData(wTargetIndex,wTargetRoundID,MDM_GR_USER,SUB_GR_USER_COME,cbBuffer,wSendLength);
	}
	else m_pITCPSocketEngine->SendDataBatch(MDM_GR_USER,SUB_GR_USER_COME,cbBuffer,wSendLength);

	return true;
}

//������Ϣ
bool CAttemperEngineSink::SendGameServerInfo(IServerUserItem * pIServerUserItem, WORD wIndex, WORD wRoundID)
{
	//���͵�¼�ɹ�
	CMD_GR_LogonSuccess LogonSuccess;
	memset(&LogonSuccess,0,sizeof(LogonSuccess));
	LogonSuccess.dwUserID=pIServerUserItem->GetUserID();

	if (wIndex>=INDEX_ANDROID)
	{
		DWORD dwID=MAKELONG(wIndex,wRoundID);
	}
	else m_pITCPSocketEngine->SendData(wIndex,wRoundID,MDM_GR_LOGON,SUB_GR_LOGON_SUCCESS,&LogonSuccess,sizeof(LogonSuccess));

	//����������Ϣ
	BYTE cbBuffer[SOCKET_PACKAGE];
	CMD_GR_ServerInfo * pServerInfo=(CMD_GR_ServerInfo *)cbBuffer;
	memset(pServerInfo,0,sizeof(CMD_GR_ServerInfo));
	pServerInfo->wKindID=m_pGameServiceAttrib->wKindID;
	pServerInfo->wGameGenre=m_pGameServiceOption->wServerType;
	pServerInfo->wTableCount=m_pGameServiceOption->wTableCount;
	pServerInfo->wChairCount=m_pGameServiceAttrib->wChairCount;
	pServerInfo->dwVideoAddr=m_pGameServiceOption->dwVideoServer;
	pServerInfo->cbHideUserInfo=m_pGameServiceOption->cbHideUserInfo;
	pServerInfo->cbDistributeMode=m_pGameServiceOption->cbDistributeMode;

	if (wIndex>=INDEX_ANDROID)
	{
		DWORD dwID=MAKELONG(wIndex,wRoundID);
	}
	else m_pITCPSocketEngine->SendData(wIndex,wRoundID,MDM_GR_INFO,SUB_GR_SERVER_INFO,cbBuffer,sizeof(CMD_GR_ServerInfo));

	//�����б����
	if (wIndex>=INDEX_ANDROID)
	{
		DWORD dwID=MAKELONG(wIndex,wRoundID);
	}
	else m_pITCPSocketEngine->SendData(wIndex,wRoundID,MDM_GR_INFO,SUB_GR_COLUMN_INFO,&m_ColumnInfo,m_wColumnInfoSize);

	//�����������
	if (wIndex>=INDEX_ANDROID)
	{
		DWORD dwID=MAKELONG(wIndex,wRoundID);
	}
	else m_pITCPSocketEngine->SendData(wIndex,wRoundID,MDM_GR_INFO,SUB_GR_CONFIG_FINISH);

	//�����Լ���Ϣ
	SendUserItem(pIServerUserItem,wIndex,wRoundID);

	//���������û�
	WORD wEnumIndex=0;
	IServerUserItem * pIServerUserItemSend=NULL;
	while (true)
	{
		pIServerUserItemSend=m_ServerUserManager.EnumOnLineUser(wEnumIndex++);
		if (pIServerUserItemSend==NULL) break;
		if (pIServerUserItemSend==pIServerUserItem) continue;
		SendUserItem(pIServerUserItemSend,wIndex,wRoundID);
	}

	//���Ͷ����û�
	wEnumIndex=0;
	while (true)
	{
		pIServerUserItemSend=m_ServerUserManager.EnumOffLineUser(wEnumIndex++);
		if (pIServerUserItemSend==NULL) break;
		if (pIServerUserItemSend==pIServerUserItem) continue;
		SendUserItem(pIServerUserItemSend,wIndex,wRoundID);
	}

	//����������Ϣ
	CMD_GR_TableInfo TableInfo;
	CTableFrame * pTableFrame=NULL;
	TableInfo.wTableCount=m_pGameServiceOption->wTableCount;
	ASSERT(TableInfo.wTableCount<CountArray(TableInfo.TableStatus));
	for (WORD i=0;i<TableInfo.wTableCount;i++)
	{
		pTableFrame=(m_pTableFrame+i);
		TableInfo.TableStatus[i].bTableLock=pTableFrame->IsTableLocked()?TRUE:FALSE;
		TableInfo.TableStatus[i].bPlayStatus=pTableFrame->IsGameStarted()?TRUE:FALSE;
	}
	WORD wSendSize=sizeof(TableInfo)-sizeof(TableInfo.TableStatus)+TableInfo.wTableCount*sizeof(TableInfo.TableStatus[0]);

	if (wIndex>=INDEX_ANDROID)
	{
		DWORD dwID=MAKELONG(wIndex,wRoundID);
	}
	else m_pITCPSocketEngine->SendData(wIndex,wRoundID,MDM_GR_STATUS,SUB_GR_TABLE_INFO,&TableInfo,wSendSize);

	//�������
	if (wIndex>=INDEX_ANDROID)
	{
		DWORD dwID=MAKELONG(wIndex,wRoundID);
	}
	else m_pITCPSocketEngine->SendData(wIndex,wRoundID,MDM_GR_LOGON,SUB_GR_LOGON_FINISH);

	return true;
}

//�б���Ϣ����
bool CAttemperEngineSink::OnCenterMainServerList(CMD_Command Command, void * pDataBuffer, WORD wDataSize)
{
	ASSERT(Command.wMainCmdID==MDM_CS_SERVER_LIST);
	switch (Command.wSubCmdID)
	{
	case SUB_CS_LIST_INFO:		//�б���Ϣ
		{
			//Ч�����
			ASSERT(wDataSize==sizeof(CMD_CS_ListInfo));
			if (wDataSize!=sizeof(CMD_CS_ListInfo)) return false;

			//��Ϣ����
			m_ServerList.ResetServerListBuffer();

			return true;
		}
	case SUB_CS_LIST_TYPE:		//������Ϣ
		{
			//Ч�����
			ASSERT(wDataSize>=sizeof(tagGameType));
			ASSERT(wDataSize%sizeof(tagGameType)==0);

			//��Ϣ����
			DWORD dwCount=wDataSize/sizeof(tagGameType);
			tagGameType * pGameType=(tagGameType *)pDataBuffer;
			m_ServerList.AppendGameTypeBuffer(pGameType,dwCount);

			return true;
		}
	case SUB_CS_LIST_KIND:		//������Ϣ
		{
			//Ч�����
			ASSERT(wDataSize>=sizeof(tagGameKind));
			ASSERT(wDataSize%sizeof(tagGameKind)==0);

			//��Ϣ����
			DWORD dwCount=wDataSize/sizeof(tagGameKind);
			tagGameKind * pGameKind=(tagGameKind *)pDataBuffer;
			m_ServerList.AppendGameKindBuffer(pGameKind,dwCount);

			return true;
		}
	case SUB_CS_LIST_STATION:	//վ����Ϣ
		{
			//Ч�����
			ASSERT(wDataSize>=sizeof(tagGameStation));
			ASSERT(wDataSize%sizeof(tagGameStation)==0);

			//��Ϣ����
			DWORD dwCount=wDataSize/sizeof(tagGameStation);
			tagGameStation * pGameStation=(tagGameStation *)pDataBuffer;
			m_ServerList.AppendGameStationBuffer(pGameStation,dwCount);

			return true;
		}
	case SUB_CS_LIST_SERVER:	//������Ϣ
		{
			//Ч�����
			ASSERT(wDataSize>=sizeof(tagGameServer));
			ASSERT(wDataSize%sizeof(tagGameServer)==0);

			//��Ϣ����
			DWORD dwCount=wDataSize/sizeof(tagGameServer);
			tagGameServer * pGameServer=(tagGameServer *)pDataBuffer;
			m_ServerList.AppendGameServerBuffer(pGameServer,dwCount);

			return true;
		}
	case SUB_CS_LIST_FINISH:	//�������
		{
			//�����
			m_ServerList.ActiveServerListBuffer();

			//��������
			WORD wInfoCount=m_ServerList.GetOnLineCountInfo(m_OnLineCountInfo,CountArray(m_OnLineCountInfo));
			m_wOnLineInfoSize=wInfoCount*sizeof(tagOnLineCountInfo);

			//������Ϣ
			if (m_wOnLineInfoSize>0)
			{
				ASSERT(m_pITCPSocketEngine!=NULL);
				m_pITCPSocketEngine->SendDataBatch(MDM_GR_SERVER_INFO,SUB_GR_ONLINE_COUNT_INFO,&m_OnLineCountInfo,m_wOnLineInfoSize);
			}

			return true;
		}
	}

	return true;
}

//�󶨲���
tagConnectItemInfo * CAttemperEngineSink::GetBindParameter(WORD wBindIndex)
{
	//��Ч����
	if (wBindIndex==0xFFFF) return NULL;

	//��������
	if (wBindIndex<m_pGameServiceOption->wMaxConnect)
	{
		return m_pNormalParameter+wBindIndex;
	}

	//��������
	if ((wBindIndex>=INDEX_ANDROID)&&(wBindIndex<(INDEX_ANDROID+MAX_ANDROID)))
	{
		return m_pAndroidParameter+(wBindIndex-INDEX_ANDROID);
	}

	//�������
	ASSERT(FALSE);

	return NULL;
}

//���û�
IServerUserItem * CAttemperEngineSink::GetServerUserItem(WORD wBindIndex)
{
	//��ȡ����
	tagConnectItemInfo * pBindParameter=GetBindParameter(wBindIndex);

	//��ȡ�û�
	if (pBindParameter!=NULL)
	{
		return pBindParameter->pIServerUserItem;
	}

	//�������
	ASSERT(FALSE);

	return NULL;
}

//////////////////////////////////////////////////////////////////////////
