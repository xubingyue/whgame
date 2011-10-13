#include "StdAfx.h"
#include "LogonService.h"

//////////////////////////////////////////////////////////////////////////

//���캯��
CLogonService::CLogonService(void)
{
	m_pIEventService=NULL;
}

//��������
CLogonService::~CLogonService(void)
{
}

//����״̬
bool CLogonService::IsService()
{
	if (m_ServiceEngine.GetInterface()!=NULL==false) return false;
	return m_ServiceEngine->IsService();
}

//��ʼ����
bool CLogonService::BeginService()
{
	try
	{
		//��������
		bool bSuccess=false;

		//�����������
		if (m_ServiceEngine.GetInterface()==false)
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
			TraceEventString(TEXT("��¼�����Ѿ���������"),Level_Warning);
			return true;
		}

		//���÷���
		m_InitParamter.LoadInitParamter();
		if (m_DataBaseSink.InitDataBaseSink(&m_InitParamter,m_ServiceEngine.GetInterface())==false) throw 0;
		if (m_AttemperSink.InitAttemperSink(&m_InitParamter,&m_CenterSocket,m_ServiceEngine.GetInterface())==false) throw 0;
		if (m_ServiceEngine->InitServiceEngine(m_InitParamter.m_wListenPort,m_InitParamter.m_wMaxConnect)==false) throw 0;

		//��ȡ��������
		IAttemperEngine * pIAttemperEngine=(IAttemperEngine *)m_ServiceEngine->GetAttemperEngine(IID_IAttemperEngine,VER_IAttemperEngine);
		ASSERT(pIAttemperEngine!=NULL);
		if (pIAttemperEngine==NULL) throw TEXT("��������ӿڲ�ѯʧ��");

		//��ȡ���ȶ���
		IQueueService * pIQueueService=(IQueueService *)pIAttemperEngine->GetQueueService(IID_IQueueService,VER_IQueueService);
		ASSERT(pIQueueService!=NULL);
		if (pIQueueService==NULL) throw TEXT("����������з���ӿڲ�ѯʧ��");

		//��ȡ�첽����
		IAsynchronismEngine * pIAsynchronismEngine=(IAsynchronismEngine *)m_ServiceEngine->GetAsynchronismEngine(IID_IAsynchronismEngine,VER_IAsynchronismEngine);
		ASSERT(pIAsynchronismEngine!=NULL);
		if (pIAsynchronismEngine==NULL) throw TEXT("�첽�������ӿڲ�ѯʧ��");

		//��������
		if (m_CenterSocket.SetQueueService(pIQueueService)==false) throw 0;
		if (m_CenterSocket.SetAsynchronismEngine(pIAsynchronismEngine)==false) throw 0;

		//ע�����
		IAsynchronismEngineSink * pIAsynchronismEngineSink=GET_OBJECT_INTERFACE(m_CenterSocket,IAsynchronismEngineSink);
		if (pIAsynchronismEngine->RegisterAsynchronismEngineSink(pIAsynchronismEngineSink)==false) throw TEXT("���������첽����ע��ʧ��");

		//��������
		if (m_ServiceEngine->BeginService()==false) throw 0;

		return true;
	}
	catch (LPCTSTR pszErrorMsg)
	{
		TraceEventString(pszErrorMsg,Level_Exception); 
		TraceEventString(TEXT("��¼��������ʧ��"),Level_Exception); 
		EndService();
	}
	catch (...)
	{ 
		TraceEventString(TEXT("��¼��������ʧ��"),Level_Exception); 
		EndService();
	}

	return false;
}

//ֹͣ����
bool CLogonService::EndService()
{
	try
	{
		if (m_ServiceEngine.GetInterface()!=NULL) 
		{
			//ֹͣ����
			m_ServiceEngine->EndService();
		
			//��ȡ�첽����
			IAsynchronismEngine * pIAsynchronismEngine=(IAsynchronismEngine *)m_ServiceEngine->GetAsynchronismEngine(IID_IAsynchronismEngine,VER_IAsynchronismEngine);
			ASSERT(pIAsynchronismEngine!=NULL);
			if (pIAsynchronismEngine==NULL) return false;

			//ע�����
			IAsynchronismEngineSink * pIAsynchronismEngineSink=GET_OBJECT_INTERFACE(m_CenterSocket,IAsynchronismEngineSink);
			pIAsynchronismEngine->UnRegisterAsynchronismEngineSink(pIAsynchronismEngineSink);
		}

		return true;
	}
	catch (LPCTSTR pszErrorMsg)
	{
		TraceEventString(pszErrorMsg,Level_Exception); 
		TraceEventString(TEXT("��¼����ֹͣʧ��"),Level_Exception); 
	}
	catch (...)
	{ 
		TraceEventString(TEXT("��¼����ֹͣʧ��"),Level_Exception); 
	}

	return false;
}

//�����¼�
bool CLogonService::SetEventService(IUnknownEx * pIEventService)
{
	//��ȡ�ӿ�
	ASSERT(pIEventService!=NULL);
	m_pIEventService=(IEventService *)pIEventService->QueryInterface(IID_IEventService,VER_IEventService);
	ASSERT(m_pIEventService!=NULL);

	//���ýӿ�
	m_CenterSocket.SetEventService(pIEventService);
	m_DataBaseSink.SetEventService(pIEventService);
	m_AttemperSink.SetEventService(pIEventService);
	if (m_ServiceEngine.GetInterface()) m_ServiceEngine->SetEventService(pIEventService);

	return (m_pIEventService!=NULL);
}

//��ʾ����
void CLogonService::TraceEventString(LPCTSTR pszString, enTraceLevel TraceLevel)
{
	if (m_pIEventService!=NULL) m_pIEventService->ShowEventNotify(pszString,TraceLevel);
	return;
}

//////////////////////////////////////////////////////////////////////////
