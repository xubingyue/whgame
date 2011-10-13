#include "StdAfx.h"
#include "Commonality.h"
#include "DataBaseSink.h"

//////////////////////////////////////////////////////////////////////////

//���캯��
CDataBaseSink::CDataBaseSink()
{
	m_pInitParamter=NULL;
	m_pIEventService=NULL;
}

//��������
CDataBaseSink::~CDataBaseSink()
{
}

//�ӿڲ�ѯ
void * __cdecl CDataBaseSink::QueryInterface(const IID & Guid, DWORD dwQueryVer)
{
	QUERYINTERFACE(IDataBaseSink,Guid,dwQueryVer);
	QUERYINTERFACE_IUNKNOWNEX(IDataBaseSink,Guid,dwQueryVer);
	return NULL;
}

//ģ������
bool __cdecl CDataBaseSink::BeginService(IUnknownEx * pIUnknownEx)
{
	//Ч�����
	ASSERT(m_pInitParamter!=NULL);
	ASSERT(m_pIEventService!=NULL);
	ASSERT(m_AttemperEvent.IsValid()==true);

	//����ʵ��
	if (m_UserDataBase.GetInterface()!=NULL==false)
	{
		if (m_UserDataBase.CreateInstance()==false)
		{
			m_pIEventService->ShowEventNotify(TEXT("�û����ݿ���󴴽�ʧ��"),Level_Exception);
			return false;
		}
	}

	try
	{
		//�����û����ݿ�
		m_UserDataBase->SetConnectionInfo(m_pInitParamter->m_szUserDataBaseAddr,m_pInitParamter->m_wUserDataBasePort,
			m_pInitParamter->m_szUserDataBaseName,m_pInitParamter->m_szUserDataBaseUser,m_pInitParamter->m_szUserDataBasePass);
		m_UserDataBase->OpenConnection();

		return true;
	}
	catch (IADOError * pIADOError)
	{
		m_pIEventService->ShowEventNotify(pIADOError->GetErrorDescribe(),Level_Exception);
	}

	return false;
}

//ģ��ر�
bool __cdecl CDataBaseSink::EndService(IUnknownEx * pIUnknownEx)
{
	try
	{
		if (m_UserDataBase.GetInterface()!=NULL) m_UserDataBase->CloseConnection();

		return true;
	}
	catch (IADOError * pIADOError)
	{
		m_pIEventService->ShowEventNotify(pIADOError->GetErrorDescribe(),Level_Exception);
	}

	return false;
}

//���ݲ�������
bool __cdecl CDataBaseSink::OnDataBaseRequest(const NTY_DataBaseEvent & DataBaseEvent, void * pDataBuffer, WORD wDataSize)
{
	switch (DataBaseEvent.wRequestID)
	{
	case DBR_GP_LOGON_BY_ACCOUNTS:		//�ʺŵ�¼
		{
			return OnRequestLogon(DataBaseEvent,pDataBuffer,wDataSize);
		}
	case DBR_GP_LOGON_BY_USERID:		//I D ��¼
		{
			return OnRequestLogon(DataBaseEvent,pDataBuffer,wDataSize);
		}
	case DBR_GP_REGISTER_ACCOUNTS:		//ע���ʺ�
		{
			return OnRequestLogon(DataBaseEvent,pDataBuffer,wDataSize);
		}
	}

	return false;
}

//�����¼�
bool CDataBaseSink::SetEventService(IUnknownEx * pIUnknownEx)
{
	ASSERT(pIUnknownEx!=NULL);
	m_pIEventService=GET_OBJECTPTR_INTERFACE(pIUnknownEx,IEventService);
	ASSERT(m_pIEventService!=NULL);
	return (m_pIEventService!=NULL);
}

//���ú���
bool CDataBaseSink::InitDataBaseSink(CInitParamter * pInitParamter, IUnknownEx * pIUnknownEx)
{
	//Ч�����
	ASSERT(pIUnknownEx!=NULL);
	ASSERT(pInitParamter!=NULL);

	//���ñ���
	m_pInitParamter=pInitParamter;

	//��ѯ�ӿ�
	IServiceEngine * pIServiceEngine=(IServiceEngine *)pIUnknownEx->QueryInterface(IID_IServiceEngine,VER_IServiceEngine);
	ASSERT(pIServiceEngine!=NULL);
	if (pIServiceEngine==NULL) throw TEXT("��������ӿڲ�ѯʧ��");

	//��ȡ�߼�����
	IAttemperEngine * pIAttemperEngine=(IAttemperEngine *)pIServiceEngine->GetAttemperEngine(IID_IAttemperEngine,VER_IAttemperEngine);
	ASSERT(pIAttemperEngine!=NULL);
	if (pIAttemperEngine==NULL) throw TEXT("��������ӿڲ�ѯʧ��");

	//����֪ͨ���
	IUnknownEx * pIQueueService=(IUnknownEx *)pIAttemperEngine->GetQueueService(IID_IQueueService,VER_IQueueService);
	if (m_AttemperEvent.SetQueueService(pIQueueService)==false) throw TEXT("�߼�����֪ͨ�ӿ�����ʧ��");

	return true;
}

//��¼������
bool CDataBaseSink::OnRequestLogon(const NTY_DataBaseEvent & DataBaseEvent, void * pDataBuffer, WORD wDataSize)
{
	try
	{
		//��¼����
		LONG lReturnValue=-1;
		LPCTSTR pszPassword=NULL;
		switch (DataBaseEvent.wRequestID)
		{
		case DBR_GP_LOGON_BY_ACCOUNTS:		//�ʺŵ�¼
			{
				//Ч�����
				ASSERT(wDataSize==sizeof(DBR_GP_LogonByAccounts));
				if (wDataSize!=sizeof(DBR_GP_LogonByAccounts)) return false;

				//ִ�в�ѯ
				DBR_GP_LogonByAccounts * pLogonByAccounts=(DBR_GP_LogonByAccounts *)pDataBuffer;
				lReturnValue=SPLogonByAccounts(pLogonByAccounts->szAccounts,pLogonByAccounts->szPassWord,pLogonByAccounts->dwClientIP,pLogonByAccounts->szComputerID);
				pszPassword=pLogonByAccounts->szPassWord;

				break;
			}
		case DBR_GP_LOGON_BY_USERID:		//I D ��¼
			{
				//Ч�����
				ASSERT(wDataSize==sizeof(DBR_GP_LogonByUserID));
				if (wDataSize!=sizeof(DBR_GP_LogonByUserID)) return false;

				//ִ�в�ѯ
				DBR_GP_LogonByUserID * pLogonByUserID=(DBR_GP_LogonByUserID *)pDataBuffer;
				lReturnValue=SPLogonByUserID(pLogonByUserID->dwUserID,pLogonByUserID->szPassWord,pLogonByUserID->dwClientIP,pLogonByUserID->szComputerID);
				pszPassword=pLogonByUserID->szPassWord;

				break;
			}
		case DBR_GP_REGISTER_ACCOUNTS:		//ע���ʺ�
			{
				//Ч�����
				ASSERT(wDataSize==sizeof(DBR_GP_RegisterAccounts));
				if (wDataSize!=sizeof(DBR_GP_RegisterAccounts)) return false;

				//ִ�в�ѯ
				DBR_GP_RegisterAccounts * pRegisterAccounts=(DBR_GP_RegisterAccounts *)pDataBuffer;
				lReturnValue=SPRegisterAccounts(pRegisterAccounts->szAccounts,pRegisterAccounts->szPassWord,pRegisterAccounts->szSpreader,
					pRegisterAccounts->wFaceID,pRegisterAccounts->cbGender,pRegisterAccounts->dwClientIP,pRegisterAccounts->szComputerID);
				pszPassword=pRegisterAccounts->szPassWord;

				break;
			}
		default :	//Ĭ�ϴ���
			{
				ASSERT(FALSE); 
				return false;
			}
		}

		//����ж�
		if (lReturnValue==0L)
		{
			//��¼�ɹ�
			DBR_GP_LogonSuccess LogonSuccess;
			memset(&LogonSuccess,0,sizeof(LogonSuccess));
			m_UserDataBase->GetFieldValue(TEXT("FaceID"),LogonSuccess.wFaceID);
			m_UserDataBase->GetFieldValue(TEXT("UserID"),LogonSuccess.dwUserID);
			m_UserDataBase->GetFieldValue(TEXT("GameID"),LogonSuccess.dwGameID);
			m_UserDataBase->GetFieldValue(TEXT("Gender"),LogonSuccess.cbGender);
			m_UserDataBase->GetFieldValue(TEXT("MemberOrder"),LogonSuccess.cbMember);
			m_UserDataBase->GetFieldValue(TEXT("Experience"),LogonSuccess.dwExperience);
			m_UserDataBase->GetFieldValue(TEXT("Accounts"),LogonSuccess.szAccounts,sizeof(LogonSuccess.szAccounts));
			m_UserDataBase->GetFieldValue(TEXT("UnderWrite"),LogonSuccess.szUnderWrite,sizeof(LogonSuccess.szUnderWrite));
			m_UserDataBase->GetFieldValue(TEXT("ErrorDescribe"),LogonSuccess.szDescribeString,sizeof(LogonSuccess.szDescribeString));
			CopyMemory(LogonSuccess.szPassword,pszPassword,sizeof(LogonSuccess.szPassword));
			m_AttemperEvent.PostDataBaseEvent(DBR_GP_LOGON_SUCCESS,DataBaseEvent.wIndex,DataBaseEvent.wRoundID,
				&LogonSuccess,sizeof(LogonSuccess));
		}
		else
		{
			//��¼ʧ��
			DBR_GP_LogonError LogonError;
			LogonError.lErrorCode=lReturnValue;
			m_UserDataBase->GetFieldValue(TEXT("ErrorDescribe"),LogonError.szErrorDescribe,sizeof(LogonError.szErrorDescribe));
			m_AttemperEvent.PostDataBaseEvent(DBR_GP_LOGON_ERROR,DataBaseEvent.wIndex,DataBaseEvent.wRoundID,
				&LogonError,sizeof(LogonError));
		}
	}
	catch (IADOError * pIADOError)
	{
		//�������
		UNREFERENCED_PARAMETER(pIADOError);
		m_pIEventService->ShowEventNotify(pIADOError->GetErrorDescribe(),Level_Exception);

		//����ʧ��
		DBR_GP_LogonError LogonError;
		LogonError.lErrorCode=-1;
		lstrcpyn(LogonError.szErrorDescribe,TEXT("�������ݿ�����쳣�������Ժ����Ի�ѡ����һ��������¼��"),
			sizeof(LogonError.szErrorDescribe));
		m_AttemperEvent.PostDataBaseEvent(DBR_GP_LOGON_ERROR,DataBaseEvent.wIndex,DataBaseEvent.wRoundID,
			&LogonError,sizeof(LogonError));
	}

	//�رռ�¼��
	m_UserDataBase->CloseRecordset();

	return true;
}

//�ʺŴ洢����
LONG CDataBaseSink::SPLogonByAccounts(LPCTSTR pszAccounts, LPCTSTR pszPassword, DWORD dwClientIP, LPCTSTR pszComputerID)
{
	//Ч�����
	ASSERT(pszAccounts!=NULL);
	ASSERT(pszPassword!=NULL);

	//ת����ַ
	TCHAR szClientIP[16]=TEXT("");
	BYTE * pClientIP=(BYTE *)&dwClientIP;
	_snprintf(szClientIP,sizeof(szClientIP),TEXT("%d.%d.%d.%d"),pClientIP[0],pClientIP[1],pClientIP[2],pClientIP[3]);

	//ִ�д洢����
	m_UserDataBase->ClearAllParameters();
	m_UserDataBase->SetSPName("GSP_GP_EfficacyAccounts");
	m_UserDataBase->AddParamter(TEXT("RETURN_VALUE"),adParamReturnValue,adInteger,4,_variant_t((long)0));
	m_UserDataBase->AddParamter(TEXT("@strAccounts"),adParamInput,adVarChar,CountString(pszAccounts),_variant_t(pszAccounts));
	m_UserDataBase->AddParamter(TEXT("@strPassword"),adParamInput,adChar,CountString(pszPassword),_variant_t(pszPassword));
	m_UserDataBase->AddParamter(TEXT("@strClientIP"),adParamInput,adVarChar,CountString(szClientIP),_variant_t(szClientIP));
	m_UserDataBase->AddParamter(TEXT("@strMachineSerial"),adParamInput,adVarChar,CountString(pszComputerID),_variant_t(pszComputerID));
	m_UserDataBase->ExecuteCommand(true);

	return m_UserDataBase->GetReturnValue();
}

//���´洢����
LONG CDataBaseSink::SPRegisterAccounts(LPCTSTR pszAccounts, LPCTSTR pszPassword, LPCTSTR pszSpreader, WORD wFaceID, BYTE cbGender, DWORD dwClientIP, LPCTSTR pszComputerID)
{
	//Ч�����
	ASSERT(pszAccounts!=NULL);
	ASSERT(pszPassword!=NULL);

	//ת����ַ
	TCHAR szClientIP[16]=TEXT("");
	BYTE * pClientIP=(BYTE *)&dwClientIP;
	_snprintf(szClientIP,sizeof(szClientIP),TEXT("%d.%d.%d.%d"),pClientIP[0],pClientIP[1],pClientIP[2],pClientIP[3]);

	//ִ�д洢����
	m_UserDataBase->ClearAllParameters();
	m_UserDataBase->SetSPName("GSP_GP_RegisterAccounts");
	m_UserDataBase->AddParamter(TEXT("RETURN_VALUE"),adParamReturnValue,adInteger,4,_variant_t((long)0));
	m_UserDataBase->AddParamter(TEXT("@strAccounts"),adParamInput,adVarChar,CountString(pszAccounts),_variant_t(pszAccounts));
	m_UserDataBase->AddParamter(TEXT("@strPassword"),adParamInput,adChar,CountString(pszPassword),_variant_t(pszPassword));
	m_UserDataBase->AddParamter(TEXT("@strSpreader"),adParamInput,adVarChar,CountString(pszSpreader),_variant_t(pszSpreader));
	m_UserDataBase->AddParamter(TEXT("@nFaceID"),adParamInput,adInteger,sizeof(long),_variant_t((long)wFaceID));
	m_UserDataBase->AddParamter(TEXT("@cbGender"),adParamInput,adInteger,sizeof(long),_variant_t((long)cbGender));
	m_UserDataBase->AddParamter(TEXT("@strClientIP"),adParamInput,adVarChar,CountString(szClientIP),_variant_t(szClientIP));
	m_UserDataBase->AddParamter(TEXT("@strMachineSerial"),adParamInput,adVarChar,CountString(pszComputerID),_variant_t(pszComputerID));
	m_UserDataBase->ExecuteCommand(true);

	return m_UserDataBase->GetReturnValue();
}

//I D �洢����
LONG CDataBaseSink::SPLogonByUserID(DWORD dwGameID, LPCTSTR pszPassword, DWORD dwClientIP, LPCTSTR pszComputerID)
{
	//Ч�����
	ASSERT(dwGameID!=0L);
	ASSERT(pszPassword!=NULL);

	//ת����ַ
	TCHAR szClientIP[16]=TEXT("");
	BYTE * pClientIP=(BYTE *)&dwClientIP;
	_snprintf(szClientIP,sizeof(szClientIP),TEXT("%d.%d.%d.%d"),pClientIP[0],pClientIP[1],pClientIP[2],pClientIP[3]);

	//ִ�д洢����
	m_UserDataBase->ClearAllParameters();
	m_UserDataBase->SetSPName("GSP_GP_EfficacyGameID");
	m_UserDataBase->AddParamter(TEXT("RETURN_VALUE"),adParamReturnValue,adInteger,sizeof(long),_variant_t((long)0));
	m_UserDataBase->AddParamter(TEXT("@dwGameID"),adParamInput,adInteger,sizeof(long),_variant_t((long)dwGameID));
	m_UserDataBase->AddParamter(TEXT("@strPassword"),adParamInput,adChar,CountString(pszPassword),_variant_t(pszPassword));
	m_UserDataBase->AddParamter(TEXT("@strClientIP"),adParamInput,adVarChar,CountString(szClientIP),_variant_t(szClientIP));
	m_UserDataBase->AddParamter(TEXT("@strMachineSerial"),adParamInput,adVarChar,CountString(pszComputerID),_variant_t(pszComputerID));
	m_UserDataBase->ExecuteCommand(true);

	return m_UserDataBase->GetReturnValue();
}

//////////////////////////////////////////////////////////////////////////
