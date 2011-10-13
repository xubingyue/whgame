#include "StdAfx.h"
#include "AttemperEngineSink.h"

//////////////////////////////////////////////////////////////////////////

//�궨��
#define TIME_RECONNECT						15000L						//����ʱ��
#define TIME_UPDATE_LIST					30000L						//����ʱ��

//��ʱ�� ID
#define IDI_CONNECT_CENTER_SERVER			1							//���ӷ�����
#define IDI_UPDATE_SERVER_LIST				2							//�����б�

//////////////////////////////////////////////////////////////////////////

//���캯��
CAttemperEngineSink::CAttemperEngineSink()
{
	//���ñ���
	m_pInitParamter=NULL;
	m_pConnectItemInfo=NULL;

	//���ķ�����
	m_pCenterSocket=NULL;
	m_SocketState=SocketState_NoConnect;

	//�ӿڱ���
	m_pITimerEngine=NULL;
	m_pIEventService=NULL;
	m_pITCPSocketEngine=NULL;

	return;
}

//��������
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

	//������������
	m_pConnectItemInfo=new tagConnectItemInfo [m_pInitParamter->m_wMaxConnect];
	if (m_pConnectItemInfo==NULL) return false;
	memset(m_pConnectItemInfo,0,sizeof(tagConnectItemInfo)*m_pInitParamter->m_wMaxConnect);

	//�������ķ�����
	DWORD dwServerIP=inet_addr(m_pInitParamter->m_szCenterServerAddr);
	m_pCenterSocket->Connect(dwServerIP,PORT_CENTER_SERVER);

	return true;
}

//����ģ��ر�
bool __cdecl CAttemperEngineSink::EndService(IUnknownEx * pIUnknownEx)
{
	//ɾ������
	SafeDeleteArray(m_pConnectItemInfo);

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

//�����¼�
bool CAttemperEngineSink::SetEventService(IUnknownEx * pIUnknownEx)
{
	//��ѯ�ӿ�
	ASSERT(pIUnknownEx!=NULL);
	m_pIEventService=GET_OBJECTPTR_INTERFACE(pIUnknownEx,IEventService);
	ASSERT(m_pIEventService!=NULL);

	//���ýӿ�
	m_ServerList.SetEventService(m_pIEventService);

	return (m_pIEventService!=NULL);
}

//���ú���
bool CAttemperEngineSink::InitAttemperSink(CInitParamter * pInitParamter, CCenterSocket * pCenterSocket, IUnknownEx * pIUnknownEx)
{
	//Ч�����
	ASSERT(pIUnknownEx!=NULL);
	ASSERT(pInitParamter!=NULL);
	ASSERT(pCenterSocket!=NULL);

	//���ñ���
	m_pInitParamter=pInitParamter;
	m_pCenterSocket=pCenterSocket;

	//��������
	IServiceEngine * pIServiceEngine=(IServiceEngine *)pIUnknownEx->QueryInterface(IID_IServiceEngine,VER_IServiceEngine);
	if (pIServiceEngine==NULL)
	{
		m_pIEventService->ShowEventNotify(TEXT("��ȡ�����������ʧ��"),Level_Exception);
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
		m_pIEventService->ShowEventNotify(TEXT("��ȡ�����������ʧ��"),Level_Exception);
		return false;
	}

	//���ݿ�����
	IDataBaseEngine * pIDataBaseEngine=(IDataBaseEngine *)pIServiceEngine->GetDataBaseEngine(IID_IDataBaseEngine,VER_IDataBaseEngine);
	if (pIDataBaseEngine==NULL)
	{
		m_pIEventService->ShowEventNotify(TEXT("��ȡ���ݿ��������ʧ��"),Level_Exception);
		return false;
	}

	//���ݿⴥ��
	IUnknownEx * pIQueueService=(IUnknownEx *)pIDataBaseEngine->GetQueueService(IID_IUnknownEx,VER_IUnknownEx);
	if (m_DataBaseEvent.SetQueueService(pIQueueService)==false)
	{
		m_pIEventService->ShowEventNotify(TEXT("��ȡ���ݿⴥ������ʧ��"),Level_Exception);
		return false;
	}

	//�б����
	if (m_ServerList.SetSocketEngine(m_pITCPSocketEngine)==false)
	{
		m_pIEventService->ShowEventNotify(TEXT("�б���������������ʧ��"),Level_Exception);
		return false;
	}

	return true;
}

//��ʱ���¼�
bool CAttemperEngineSink::OnEventTimer(WORD wTimerID, WPARAM wBindParam)
{
	switch (wTimerID)
	{
	case IDI_CONNECT_CENTER_SERVER:		//�������ķ�����
		{
			DWORD dwServerIP=inet_addr(m_pInitParamter->m_szCenterServerAddr);
			m_pCenterSocket->Connect(dwServerIP,PORT_CENTER_SERVER);
			return true;
		}
	case IDI_UPDATE_SERVER_LIST:		//���·������б�
		{
			if (m_SocketState==SocketState_Connected)
			{
				m_pCenterSocket->SendData(MDM_CS_SERVER_LIST,SUB_CS_GET_SERVER_LIST,NULL,0);
			}
			return true;
		}
	}
	return false;
}

//���ݿ��¼�
bool CAttemperEngineSink::OnEventDataBase(void * pDataBuffer, WORD wDataSize, NTY_DataBaseEvent * pDataBaseEvent)
{
	switch (pDataBaseEvent->wRequestID)
	{
	case DBR_GP_LOGON_SUCCESS:		//��¼�ɹ�
		{
			return OnDBLogonSuccess(pDataBuffer,wDataSize,pDataBaseEvent);
		}
	case DBR_GP_LOGON_ERROR:		//��¼ʧ��
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
	ASSERT(pDataBaseEvent->wRequestID==DBR_GP_LOGON_SUCCESS);
	ASSERT(wDataSize==sizeof(DBR_GP_LogonSuccess));
	if (wDataSize!=sizeof(DBR_GP_LogonSuccess)) return false;

	//�ж�����
	ASSERT(pDataBaseEvent->wIndex<m_pInitParamter->m_wMaxConnect);
	tagConnectItemInfo * pConnectItemInfo=(m_pConnectItemInfo+pDataBaseEvent->wIndex);
	if (pConnectItemInfo->bConnect==FALSE) return true;
	if (pConnectItemInfo->wRoundID!=pDataBaseEvent->wRoundID) return true;

	//��������
	BYTE cbBuffer[SOCKET_PACKAGE];
	CMD_GP_LogonSuccess * pCMDLogonSuccess=(CMD_GP_LogonSuccess *)cbBuffer;
	DBR_GP_LogonSuccess * pDBRLogonSuccess=(DBR_GP_LogonSuccess *)pDataBuffer;
	pCMDLogonSuccess->wFaceID=pDBRLogonSuccess->wFaceID;
	pCMDLogonSuccess->cbGender=pDBRLogonSuccess->cbGender;
	pCMDLogonSuccess->cbMember=pDBRLogonSuccess->cbMember;
	pCMDLogonSuccess->dwUserID=pDBRLogonSuccess->dwUserID;
	pCMDLogonSuccess->dwGameID=pDBRLogonSuccess->dwGameID;
	pCMDLogonSuccess->dwExperience=pDBRLogonSuccess->dwExperience;

	//��������
	CSendPacketHelper SendPacket(cbBuffer+sizeof(CMD_GP_LogonSuccess),sizeof(cbBuffer)-sizeof(CMD_GP_LogonSuccess));
	SendPacket.AddPacket(pDBRLogonSuccess->szPassword,CountString(pDBRLogonSuccess->szPassword),DTP_USER_PASS);
	SendPacket.AddPacket(pDBRLogonSuccess->szAccounts,CountString(pDBRLogonSuccess->szAccounts),DTP_USER_ACCOUNTS);
	SendPacket.AddPacket(pDBRLogonSuccess->szUnderWrite,CountString(pDBRLogonSuccess->szUnderWrite),DTP_UNDER_WRITE);

	//������Ϣ
	if (pDBRLogonSuccess->szGroupName[0]!=0)
	{
		SendPacket.AddPacket(pDBRLogonSuccess->szGroupName,CountString(pDBRLogonSuccess->szGroupName),DTP_USER_GROUP_NAME);
	}
	
	//վ����ҳ
	if (m_pInitParamter->m_szMainPage[0]!=0)
	{
		SendPacket.AddPacket(m_pInitParamter->m_szMainPage,CountString(m_pInitParamter->m_szMainPage),DTP_STATION_PAGE);
	}

	//���͵�¼���
	WORD wIndex=pDataBaseEvent->wIndex;
	WORD wRoundID=pDataBaseEvent->wRoundID;
	WORD wSendSize=sizeof(CMD_GP_LogonSuccess)+SendPacket.GetDataSize();
	m_pITCPSocketEngine->SendData(wIndex,wRoundID,MDM_GP_LOGON,SUB_GP_LOGON_SUCCESS,cbBuffer,wSendSize);

	//�б�����
	CMD_GP_ListConfig ListConfig;
	ListConfig.bShowOnLineCount=TRUE;
	m_pITCPSocketEngine->SendData(wIndex,wRoundID,MDM_GP_SERVER_LIST,SUB_GP_LIST_CONFIG,&ListConfig,sizeof(ListConfig));

	//������Ϸ�б�
	m_ServerList.SendGameTypeList(wIndex,wRoundID);
	m_ServerList.SendGameKindList(wIndex,wRoundID);
	m_ServerList.SendGameStationList(wIndex,wRoundID);
	m_ServerList.SendGameServerList(wIndex,wRoundID);

	//���͵�¼���
	m_pITCPSocketEngine->SendData(wIndex,wRoundID,MDM_GP_LOGON,SUB_GP_LOGON_FINISH);

	//�ر�����
	m_pITCPSocketEngine->ShutDownSocket(wIndex,wRoundID);

	return true;
}

//�û���¼ʧ��
bool CAttemperEngineSink::OnDBLogonError(void * pDataBuffer, WORD wDataSize, NTY_DataBaseEvent * pDataBaseEvent)
{
	//Ч�����
	ASSERT(pDataBaseEvent->wRequestID==DBR_GP_LOGON_ERROR);
	ASSERT(wDataSize==sizeof(DBR_GP_LogonError));

	//�ж�����
	ASSERT(pDataBaseEvent->wIndex<m_pInitParamter->m_wMaxConnect);
	tagConnectItemInfo * pConnectItemInfo=(m_pConnectItemInfo+pDataBaseEvent->wIndex);
	if (pConnectItemInfo->bConnect==FALSE) return true;
	if (pConnectItemInfo->wRoundID!=pDataBaseEvent->wRoundID) return true;

	//��������
	CMD_GP_LogonError LogonError;
	DBR_GP_LogonError * pLogonError=(DBR_GP_LogonError *)pDataBuffer;
	pLogonError->szErrorDescribe[CountString(pLogonError->szErrorDescribe)-1]=0;

	//��������
	LogonError.lErrorCode=pLogonError->lErrorCode;
	lstrcpyn(LogonError.szErrorDescribe,pLogonError->szErrorDescribe,sizeof(LogonError.szErrorDescribe));
	WORD wDescribeSize=CountString(LogonError.szErrorDescribe);

	//��������
	WORD wSendSize=sizeof(LogonError)-sizeof(LogonError.szErrorDescribe)+wDescribeSize;
	m_pITCPSocketEngine->SendData(pDataBaseEvent->wIndex,pDataBaseEvent->wRoundID,MDM_GP_LOGON,
		SUB_GP_LOGON_ERROR,&LogonError,wSendSize);

	//�ر�����
	m_pITCPSocketEngine->ShutDownSocket(pDataBaseEvent->wIndex,pDataBaseEvent->wRoundID);

	return true;
}

//����Ӧ���¼�
bool __cdecl CAttemperEngineSink::OnEventSocketAccept(NTY_SocketAcceptEvent * pSocketAcceptEvent)
{
	//Ч�����
	ASSERT(pSocketAcceptEvent->wIndex<m_pInitParamter->m_wMaxConnect);

	//��������
	tagConnectItemInfo * pConnectItemInfo=m_pConnectItemInfo+pSocketAcceptEvent->wIndex;
	pConnectItemInfo->bConnect=TRUE;
	pConnectItemInfo->wRoundID=pSocketAcceptEvent->wRoundID;
	pConnectItemInfo->dwClientIP=pSocketAcceptEvent->dwClientIP;

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
	//��¼��Ϣ
	case MDM_GP_LOGON:				
		{
			return OnSocketMainLogon(Command,pDataBuffer,wDataSize,pSocketReadEvent);
		}
	}

	return false;
}

//����ر��¼�
bool __cdecl CAttemperEngineSink::OnEventSocketClose(NTY_SocketCloseEvent * pSocketCloseEvent)
{
	//Ч�����
	ASSERT(pSocketCloseEvent->wIndex<m_pInitParamter->m_wMaxConnect);

	//��������
	tagConnectItemInfo * pConnectItemInfo=m_pConnectItemInfo+pSocketCloseEvent->wIndex;
	pConnectItemInfo->wRoundID++;
	pConnectItemInfo->dwClientIP=0;
	pConnectItemInfo->bConnect=FALSE;

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

	//��ȡ�б�
	m_pCenterSocket->SendData(MDM_CS_SERVER_LIST,SUB_CS_GET_SERVER_LIST,NULL,0);

	//���ö�ʱ��
	m_pITimerEngine->SetTimer(IDI_UPDATE_SERVER_LIST,TIME_UPDATE_LIST,TIMER_REPEAT_TIMER,NULL);

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
	m_pITimerEngine->KillTimer(IDI_UPDATE_SERVER_LIST);

	//��������
	if (bCloseByServer==true) m_pITimerEngine->SetTimer(IDI_CONNECT_CENTER_SERVER,TIME_RECONNECT,1,NULL);

	return true;
}

//��¼��Ϣ����
bool CAttemperEngineSink::OnSocketMainLogon(CMD_Command Command, void * pDataBuffer, WORD wDataSize, NTY_SocketReadEvent * pSocketReadEvent)
{
	ASSERT(Command.wMainCmdID==MDM_GP_LOGON);
	switch (Command.wSubCmdID)
	{
	case SUB_GP_LOGON_ACCOUNTS:		//�ʺŵ�¼
		{
			//Ч�����
			ASSERT(wDataSize>=sizeof(CMD_GP_LogonByAccounts));
			if (wDataSize<sizeof(CMD_GP_LogonByAccounts)) return false;

			//������Ϣ
			CMD_GP_LogonByAccounts * pLogonByAccounts=(CMD_GP_LogonByAccounts *)pDataBuffer;
			pLogonByAccounts->szAccounts[CountArray(pLogonByAccounts->szAccounts)-1]=0;
			pLogonByAccounts->szPassWord[CountArray(pLogonByAccounts->szPassWord)-1]=0;

			//������Ϣ
			ASSERT(pSocketReadEvent->wIndex<m_pInitParamter->m_wMaxConnect);
			DWORD dwClientAddr=(m_pConnectItemInfo+pSocketReadEvent->wIndex)->dwClientIP;

			//Ч��汾
			if (pLogonByAccounts->dwPlazaVersion!=VER_PLAZA_FRAME)
			{
				//��ȡ�汾
				WORD wLow=LOWORD(pLogonByAccounts->dwPlazaVersion);
				WORD wHigh=HIWORD(pLogonByAccounts->dwPlazaVersion);

				//��������
				CMD_GP_Version Version;
				Version.bNewVersion=TRUE;
				Version.bAllowConnect=(wHigh==VER_PLAZA_HIGH)?TRUE:FALSE;

				//��������
				WORD wIndex=pSocketReadEvent->wIndex;
				WORD wRountID=pSocketReadEvent->wRoundID;
				m_pITCPSocketEngine->SendData(wIndex,wRountID,MDM_GP_SYSTEM,SUB_GP_VERSION,&Version,sizeof(Version));

				//�жϹر�
				if (Version.bAllowConnect==FALSE)
				{
					return true;
				}
			}

			//��������
			DBR_GP_LogonByAccounts LogonByAccounts;
			ZeroMemory(&LogonByAccounts,sizeof(LogonByAccounts));

			//���ñ���
			LogonByAccounts.dwClientIP=dwClientAddr;
			lstrcpyn(LogonByAccounts.szAccounts,pLogonByAccounts->szAccounts,sizeof(LogonByAccounts.szAccounts));
			lstrcpyn(LogonByAccounts.szPassWord,pLogonByAccounts->szPassWord,sizeof(LogonByAccounts.szPassWord));

			//��������
			VOID * pDataBuffer=NULL;
			tagDataDescribe DataDescribe;
			CRecvPacketHelper RecvPacket(pLogonByAccounts+1,wDataSize-sizeof(CMD_GP_LogonByAccounts));

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
						ASSERT(pDataBuffer!=NULL);
						ASSERT(DataDescribe.wDataSize==sizeof(tagClientSerial));
						if (DataDescribe.wDataSize==sizeof(tagClientSerial))
						{
							BYTE * pcbByte=(BYTE *)pDataBuffer;
							for (INT i=0;i<sizeof(tagClientSerial)/sizeof(BYTE);i++)
							{
								ASSERT(CountArray(LogonByAccounts.szComputerID)>((i*2)+1));
								_stprintf(&LogonByAccounts.szComputerID[i*2],TEXT("%02X"),*(pcbByte+i));
							}
						}

						break;
					}
				}
			}

			//Ͷ�����ݿ�
			m_DataBaseEvent.PostDataBaseEvent(DBR_GP_LOGON_BY_ACCOUNTS,pSocketReadEvent->wIndex,
				pSocketReadEvent->wRoundID,&LogonByAccounts,sizeof(LogonByAccounts));

			return true;
		}
	case SUB_GP_LOGON_USERID:		//ID ��¼
		{
			//Ч�����
			ASSERT(wDataSize>=sizeof(CMD_GP_LogonByUserID));
			if (wDataSize<sizeof(CMD_GP_LogonByUserID)) return false;

			//������Ϣ
			CMD_GP_LogonByUserID * pLogonByUserID=(CMD_GP_LogonByUserID *)pDataBuffer;
			pLogonByUserID->szPassWord[CountArray(pLogonByUserID->szPassWord)-1]=0;

			//������Ϣ
			ASSERT(pSocketReadEvent->wIndex<m_pInitParamter->m_wMaxConnect);
			DWORD dwClientAddr=(m_pConnectItemInfo+pSocketReadEvent->wIndex)->dwClientIP;

			//Ч��汾
			if (pLogonByUserID->dwPlazaVersion!=VER_PLAZA_FRAME)
			{
				//��ȡ�汾
				WORD wLow=LOWORD(pLogonByUserID->dwPlazaVersion);
				WORD wHigh=HIWORD(pLogonByUserID->dwPlazaVersion);

				//��������
				CMD_GP_Version Version;
				Version.bNewVersion=TRUE;
				Version.bAllowConnect=(wHigh==VER_PLAZA_HIGH)?TRUE:FALSE;

				//��������
				WORD wIndex=pSocketReadEvent->wIndex;
				WORD wRountID=pSocketReadEvent->wRoundID;
				m_pITCPSocketEngine->SendData(wIndex,wRountID,MDM_GP_SYSTEM,SUB_GP_VERSION,&Version,sizeof(Version));

				//�жϹر�
				if (Version.bAllowConnect==FALSE)
				{
					return true;
				}
			}

			//��������
			DBR_GP_LogonByUserID LogonByUserID;
			memset(&LogonByUserID,0,sizeof(LogonByUserID));
			LogonByUserID.dwClientIP=dwClientAddr;
			LogonByUserID.dwUserID=pLogonByUserID->dwUserID;
			lstrcpyn(LogonByUserID.szPassWord,pLogonByUserID->szPassWord,sizeof(LogonByUserID.szPassWord));

			//��������
			VOID * pDataBuffer=NULL;
			tagDataDescribe DataDescribe;
			CRecvPacketHelper RecvPacket(pLogonByUserID+1,wDataSize-sizeof(CMD_GP_LogonByUserID));

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
						ASSERT(pDataBuffer!=NULL);
						ASSERT(DataDescribe.wDataSize==sizeof(tagClientSerial));
						if (DataDescribe.wDataSize==sizeof(tagClientSerial))
						{
							BYTE * pcbByte=(BYTE *)pDataBuffer;
							for (INT i=0;i<sizeof(tagClientSerial)/sizeof(BYTE);i++)
							{
								ASSERT(CountArray(LogonByUserID.szComputerID)>((i*2)+1));
								_stprintf(&LogonByUserID.szComputerID[i*2],TEXT("%02X"),*(pcbByte+i));
							}
						}

						break;
					}
				}
			}

			//Ͷ�����ݿ�
			m_DataBaseEvent.PostDataBaseEvent(DBR_GP_LOGON_BY_USERID,pSocketReadEvent->wIndex,
				pSocketReadEvent->wRoundID,&LogonByUserID,sizeof(LogonByUserID));

			return true;
		}
	case SUB_GP_REGISTER_ACCOUNTS:		//ע���ʺ�
		{
			//Ч�����
			ASSERT(wDataSize>=sizeof(CMD_GP_RegisterAccounts));
			if (wDataSize<sizeof(CMD_GP_RegisterAccounts)) return false;

			//������Ϣ
			CMD_GP_RegisterAccounts * pRegisterAccounts=(CMD_GP_RegisterAccounts *)pDataBuffer;
			pRegisterAccounts->szAccounts[CountArray(pRegisterAccounts->szAccounts)-1]=0;
			pRegisterAccounts->szPassWord[CountArray(pRegisterAccounts->szPassWord)-1]=0;

			//������Ϣ
			ASSERT(pSocketReadEvent->wIndex<m_pInitParamter->m_wMaxConnect);
			DWORD dwClientAddr=(m_pConnectItemInfo+pSocketReadEvent->wIndex)->dwClientIP;

			//Ч��汾
			if (pRegisterAccounts->dwPlazaVersion!=VER_PLAZA_FRAME)
			{
				//��ȡ�汾
				WORD wLow=LOWORD(pRegisterAccounts->dwPlazaVersion);
				WORD wHigh=HIWORD(pRegisterAccounts->dwPlazaVersion);

				//��������
				CMD_GP_Version Version;
				Version.bNewVersion=TRUE;
				Version.bAllowConnect=(wHigh==VER_PLAZA_HIGH)?TRUE:FALSE;

				//��������
				WORD wIndex=pSocketReadEvent->wIndex;
				WORD wRountID=pSocketReadEvent->wRoundID;
				m_pITCPSocketEngine->SendData(wIndex,wRountID,MDM_GP_SYSTEM,SUB_GP_VERSION,&Version,sizeof(Version));

				//�жϹر�
				if (Version.bAllowConnect==FALSE)
				{
					return true;
				}
			}

			//��������
			DBR_GP_RegisterAccounts RegisterAccounts;
			memset(&RegisterAccounts,0,sizeof(RegisterAccounts));
			RegisterAccounts.dwClientIP=dwClientAddr;
			RegisterAccounts.wFaceID=pRegisterAccounts->wFaceID;
			RegisterAccounts.cbGender=pRegisterAccounts->cbGender;
			lstrcpyn(RegisterAccounts.szSpreader,pRegisterAccounts->szSpreader,sizeof(RegisterAccounts.szSpreader));
			lstrcpyn(RegisterAccounts.szAccounts,pRegisterAccounts->szAccounts,sizeof(RegisterAccounts.szAccounts));
			lstrcpyn(RegisterAccounts.szPassWord,pRegisterAccounts->szPassWord,sizeof(RegisterAccounts.szPassWord));

			//��������
			VOID * pDataBuffer=NULL;
			tagDataDescribe DataDescribe;
			CRecvPacketHelper RecvPacket(pRegisterAccounts+1,wDataSize-sizeof(CMD_GP_RegisterAccounts));

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
						ASSERT(pDataBuffer!=NULL);
						ASSERT(DataDescribe.wDataSize==sizeof(tagClientSerial));
						if (DataDescribe.wDataSize==sizeof(tagClientSerial))
						{
							BYTE * pcbByte=(BYTE *)pDataBuffer;
							for (INT i=0;i<sizeof(tagClientSerial)/sizeof(BYTE);i++)
							{
								ASSERT(CountArray(RegisterAccounts.szComputerID)>((i*2)+1));
								_stprintf(&RegisterAccounts.szComputerID[i*2],TEXT("%02X"),*(pcbByte+i));
							}
						}

						break;
					}
				}
			}

			//Ͷ�����ݿ�
			m_DataBaseEvent.PostDataBaseEvent(DBR_GP_REGISTER_ACCOUNTS,pSocketReadEvent->wIndex,
				pSocketReadEvent->wRoundID,&RegisterAccounts,sizeof(RegisterAccounts));

			return true;
		}
	}
	return false;
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
			//��Ϣ����
			m_ServerList.ActiveServerListBuffer();

			return true;
		}
	}

	return true;
}

//////////////////////////////////////////////////////////////////////////
