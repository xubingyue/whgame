#include "StdAfx.h"
#include "GameService.h"

//////////////////////////////////////////////////////////////////////////

//���캯��
CGameService::CGameService()
{
	m_szModule[0]=0;
	m_hDllInstance=NULL;
	m_pIEventService=NULL;
	m_pIGameServiceManager=NULL;
	memset(&m_GameUserDBInfo,0,sizeof(m_GameUserDBInfo));
	memset(&m_GameScoreDBInfo,0,sizeof(m_GameScoreDBInfo));
	memset(&m_GameServiceAttrib,0,sizeof(m_GameServiceAttrib));
	memset(&m_GameServiceOption,0,sizeof(m_GameServiceOption));
}

//��������
CGameService::~CGameService()
{
	UnLoadGameServiceModule();
	return;
}

//�ӿڲ�ѯ
void * __cdecl CGameService::QueryInterface(const IID & Guid, DWORD dwQueryVer)
{
	QUERYINTERFACE(IGameService,Guid,dwQueryVer);
	QUERYINTERFACE_IUNKNOWNEX(IGameService,Guid,dwQueryVer);
	return NULL;
}

//��ʼ����
bool __cdecl CGameService::BeginService(tagGameServiceParameter * pGameServiceParameter)
{
	//Ч�����
	ASSERT(pGameServiceParameter!=NULL);
	if (pGameServiceParameter==NULL) return false;

	try
	{
		//���ñ���
		bool bSuccess=false;
		lstrcpyn(m_szModule,pGameServiceParameter->szModule,CountArray(m_szModule));
		CopyMemory(&m_GameUserDBInfo,&pGameServiceParameter->GameUserDBInfo,sizeof(m_GameUserDBInfo));
		CopyMemory(&m_GameScoreDBInfo,&pGameServiceParameter->GameScoreDBInfo,sizeof(m_GameScoreDBInfo));
		CopyMemory(&m_GameServiceOption,&pGameServiceParameter->GameServiceOption,sizeof(m_GameServiceOption));

		//�����������
		if (m_ServiceEngine.GetInterface()==NULL)
		{
			if (m_ServiceEngine.CreateInstance()==false) throw m_ServiceEngine.GetErrorMessage();
			if (m_pIEventService!=NULL) m_ServiceEngine->SetEventService(m_pIEventService);

			//ע�������ҷ���
			IUnknownEx * pIAttemperEngine=GET_OBJECT_INTERFACE(m_AttemperSink,IUnknownEx);
			if (m_ServiceEngine->SetAttemperEngineSink(pIAttemperEngine)==false) throw 0;

			//ע�����ݿ���ҷ���
			IUnknownEx * pIDataBaseSink=GET_OBJECT_INTERFACE(m_DataBaseSink,IUnknownEx);
			if (m_ServiceEngine->SetDataBaseSink(pIDataBaseSink)==false) throw 0;
		}

		//�ж�״̬
		if (m_ServiceEngine->IsService()==true)
		{
			ShowErrorMessasge(TEXT("��Ϸ�����Ѿ���������"),Level_Warning);
			return true;
		}

		//����ģ��
		ASSERT(m_szModule[0]!=0);
		if (LoadGameServiceModule(m_szModule)==false)
		{
			ShowErrorMessasge(TEXT("��Ϸ����ģ���������ʧ��"),Level_Exception);
			throw 0;
		}

		//��������
		WORD wLessConnect=m_GameServiceOption.wTableCount*m_GameServiceAttrib.wChairCount+50;
		m_GameServiceOption.wMaxConnect=__max(m_GameServiceOption.wMaxConnect,wLessConnect);

		//��������
		if (m_ServiceEngine->InitServiceEngine(m_GameServiceOption.wServerPort,m_GameServiceOption.wMaxConnect)==false) throw 0;

		//�������ݿ�
		tagDataBaseSinkParameter DataBaseSinkParameter;
		memset(&DataBaseSinkParameter,0,sizeof(DataBaseSinkParameter));
		DataBaseSinkParameter.pGameUserDBInfo=&m_GameUserDBInfo;
		DataBaseSinkParameter.pGameScoreDBInfo=&m_GameScoreDBInfo;
		DataBaseSinkParameter.pGameServiceAttrib=&m_GameServiceAttrib;
		DataBaseSinkParameter.pGameServiceOption=&m_GameServiceOption;
		if (m_DataBaseSink.InitDataBaseSink(&DataBaseSinkParameter,m_ServiceEngine.GetInterface())==false)
		{
			ShowErrorMessasge(TEXT("���ݿ�������ҷ�������ʧ��"),Level_Exception);
			throw 0;
		}

		//���õ���
		tagAttemperSinkParameter AttemperSinkParameter;
		memset(&AttemperSinkParameter,0,sizeof(AttemperSinkParameter));
		AttemperSinkParameter.pCenterSocket=&m_CenterSocket;
		AttemperSinkParameter.pGameServiceAttrib=&m_GameServiceAttrib;
		AttemperSinkParameter.pGameServiceOption=&m_GameServiceOption;
		AttemperSinkParameter.pIGameServiceManager=m_pIGameServiceManager;
		AttemperSinkParameter.dwCenterServer=pGameServiceParameter->dwCenterAddr;
		AttemperSinkParameter.pIAttemperEngine=(IAttemperEngine *)m_ServiceEngine->GetAttemperEngine(IID_IAttemperEngine,VER_IAttemperEngine);
		if (m_AttemperSink.InitAttemperSink(&AttemperSinkParameter,m_ServiceEngine.GetInterface())==false)
		{
			ShowErrorMessasge(TEXT("����������ҷ�������ʧ��"),Level_Exception);
			throw 0;
		}

		//��ȡ��������
		IAttemperEngine * pIAttemperEngine=(IAttemperEngine *)m_ServiceEngine->GetAttemperEngine(IID_IAttemperEngine,VER_IAttemperEngine);
		ASSERT(pIAttemperEngine!=NULL);
		if (pIAttemperEngine==NULL)
		{
			ShowErrorMessasge(TEXT("��������ӿڲ�ѯʧ��"),Level_Exception);
			throw 0;
		}

		//��ȡ���ȶ���
		IQueueService * pIQueueService=(IQueueService *)pIAttemperEngine->GetQueueService(IID_IQueueService,VER_IQueueService);
		ASSERT(pIQueueService!=NULL);
		if (pIQueueService==NULL) 
		{
			ShowErrorMessasge(TEXT("����������з���ӿڲ�ѯʧ��"),Level_Exception);
			throw 0;
		}

		//��ȡ�첽����
		IAsynchronismEngine * pIAsynchronismEngine=(IAsynchronismEngine *)m_ServiceEngine->GetAsynchronismEngine(IID_IAsynchronismEngine,VER_IAsynchronismEngine);
		ASSERT(pIAsynchronismEngine!=NULL);
		if (pIAsynchronismEngine==NULL) 
		{
			ShowErrorMessasge(TEXT("�첽�������ӿڲ�ѯʧ��"),Level_Exception);
			throw 0;
		}

		//��������
		if (m_CenterSocket.SetQueueService(pIQueueService)==false) throw 0;
		if (m_CenterSocket.SetAsynchronismEngine(pIAsynchronismEngine)==false) throw 0;

		//ע�����
		IAsynchronismEngineSink * pIAsynchronismEngineSink=GET_OBJECT_INTERFACE(m_CenterSocket,IAsynchronismEngineSink);
		if (pIAsynchronismEngine->RegisterAsynchronismEngineSink(pIAsynchronismEngineSink)==false) 
		{
			ShowErrorMessasge(TEXT("���������첽����ע��ʧ��"),Level_Exception);
			throw 0;
		}

		//��������
		if (m_ServiceEngine->BeginService()==false) throw 0;

		return true;
	}
	catch (LPCTSTR pszErrorMsg)
	{
		ShowErrorMessasge(pszErrorMsg,Level_Exception); 
		ShowErrorMessasge(TEXT("��Ϸ��������ʧ��"),Level_Exception); 
		EndService();
	}
	catch (...)
	{ 
		ShowErrorMessasge(TEXT("�����쳣������Ϸ��������ʧ��"),Level_Exception); 
		EndService();
	}

	return false;
}

//ֹͣ����
bool __cdecl CGameService::EndService()
{
	try
	{
		//ֹͣ����
		if (m_ServiceEngine.GetInterface()!=NULL) 
		{
			//ֹͣ����
			m_ServiceEngine->EndService();

			//ע������
			IAsynchronismEngine * pIAsynchronismEngine=(IAsynchronismEngine *)m_ServiceEngine->GetAsynchronismEngine(IID_IAsynchronismEngine,VER_IAsynchronismEngine);
			IAsynchronismEngineSink * pIAsynchronismEngineSink=GET_OBJECT_INTERFACE(m_CenterSocket,IAsynchronismEngineSink);
			if (pIAsynchronismEngine!=NULL) pIAsynchronismEngine->UnRegisterAsynchronismEngineSink(pIAsynchronismEngineSink);
		}

		//ж��ģ��
		UnLoadGameServiceModule();

		return true;
	}
	catch (LPCTSTR pszErrorMsg)
	{
		ShowErrorMessasge(pszErrorMsg,Level_Exception); 
		ShowErrorMessasge(TEXT("��Ϸ����ֹͣʧ��"),Level_Exception); 
	}
	catch (...)
	{ 
		ShowErrorMessasge(TEXT("��Ϸ����ֹͣʧ��"),Level_Exception); 
	}

	return false;
}

//����״̬
bool CGameService::IsService()
{
	if (m_ServiceEngine.GetInterface()!=NULL==false) return false;
	return m_ServiceEngine->IsService();
}

//�����¼�
bool CGameService::SetEventService(IUnknownEx * pIEventService)
{
	//��ȡ�ӿ�
	ASSERT(pIEventService!=NULL);
	m_pIEventService=(IEventService *)pIEventService->QueryInterface(IID_IEventService,VER_IEventService);
	ASSERT(m_pIEventService!=NULL);

	//���ýӿ�
	m_CenterSocket.SetEventService(pIEventService);
	m_DataBaseSink.SetEventService(pIEventService);
	m_AttemperSink.SetEventService(pIEventService);
	if (m_ServiceEngine.GetInterface()!=NULL) m_ServiceEngine->SetEventService(pIEventService);

	return (m_pIEventService!=NULL);
}

//�ͷ�ģ��
bool CGameService::UnLoadGameServiceModule()
{
	try
	{
		if (m_pIGameServiceManager!=NULL)
		{
			m_pIGameServiceManager->Release();
			m_pIGameServiceManager=NULL;
		}
		if (m_hDllInstance!=NULL)
		{
			AfxFreeLibrary(m_hDllInstance);
			m_hDllInstance=NULL;
		}
		return true;
	}
	catch (...) {}

	return false;
}

//����ģ��
bool CGameService::LoadGameServiceModule(LPCTSTR pszModuleName)
{
	//Ч�����
	ASSERT(pszModuleName!=NULL);
	ASSERT(m_hDllInstance==NULL);

	try
	{
		//����ģ��
		m_hDllInstance=AfxLoadLibrary(pszModuleName);
		if (m_hDllInstance==NULL) 
		{
			TCHAR szDescribe[256]=TEXT("");
			_snprintf(szDescribe,sizeof(szDescribe),TEXT("��%s��ģ�����ʧ��"),pszModuleName);
			ShowErrorMessasge(szDescribe,Level_Exception);
			throw 0;
		}
		ModuleCreateFunc * CreateFunc=(ModuleCreateFunc *)GetProcAddress(m_hDllInstance,TEXT("CreateGameServiceManager"));
		if (CreateFunc==NULL) 
		{
			TCHAR szDescribe[256]=TEXT("");
			_snprintf(szDescribe,sizeof(szDescribe),TEXT("��%s����������������"),pszModuleName);
			ShowErrorMessasge(szDescribe,Level_Exception);
			throw 0;
		}
		m_pIGameServiceManager=(IGameServiceManager *)CreateFunc(IID_IGameServiceManager,VER_IGameServiceManager);
		if (m_pIGameServiceManager==NULL) 
		{
			TCHAR szDescribe[256]=TEXT("");
			_snprintf(szDescribe,sizeof(szDescribe),TEXT("��%s����Ϸ����ӿڴ���ʧ��"),pszModuleName);
			ShowErrorMessasge(szDescribe,Level_Exception);
			throw 0;
		}

		//��ȡ����
		m_pIGameServiceManager->GetGameServiceAttrib(m_GameServiceAttrib);

		return true;
	}
	catch (...)	{ UnLoadGameServiceModule(); }

	return false;
}

//��ʾ����
void CGameService::ShowErrorMessasge(LPCTSTR pszString, enTraceLevel TraceLevel)
{
	if (m_pIEventService!=NULL) m_pIEventService->ShowEventNotify(pszString,TraceLevel);
	return;
}

//////////////////////////////////////////////////////////////////////////

//����������
extern "C" __declspec(dllexport) void * __cdecl CreateGameService(const GUID & Guid, DWORD dwInterfaceVer)
{
	//��������
	CGameService * pGameService=NULL;
	try
	{
		pGameService=new CGameService();
		if (pGameService==NULL) throw TEXT("����ʧ��");
		void * pObject=pGameService->QueryInterface(Guid,dwInterfaceVer);
		if (pObject==NULL) throw TEXT("�ӿڲ�ѯʧ��");
		return pObject;
	}
	catch (...) {}

	//�������
	SafeDelete(pGameService);
	return NULL;
}

//////////////////////////////////////////////////////////////////////////
