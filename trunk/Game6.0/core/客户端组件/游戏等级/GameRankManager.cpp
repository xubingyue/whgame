#include "StdAfx.h"
#include "GameRankManager.h"

//////////////////////////////////////////////////////////////////////////

//���캯��
CGameRankManager::CGameRankManager()
{
}

//��������
CGameRankManager::~CGameRankManager()
{
}

//�ӿڲ�ѯ
void * __cdecl CGameRankManager::QueryInterface(const IID & Guid, DWORD dwQueryVer)
{
	QUERYINTERFACE(IGameRankManager,Guid,dwQueryVer);
	QUERYINTERFACE_IUNKNOWNEX(IGameRankManager,Guid,dwQueryVer);
	return NULL;
}

//�������
LPCTSTR __cdecl CGameRankManager::GetGameRank(WORD wKindID, LONG lScore, WORD wGameGenre)
{
	return TEXT("");
}

//////////////////////////////////////////////////////////////////////////

//����������
extern "C" __declspec(dllexport) void * __cdecl CreateGameRankManager(const GUID & Guid, DWORD dwInterfaceVer)
{
	//��������
	CGameRankManager *pGameRankManager=NULL;
	try
	{
		pGameRankManager = new CGameRankManager();
		if(pGameRankManager==NULL) throw _T("����ʧ��");

		void *pObject = pGameRankManager->QueryInterface(Guid,dwInterfaceVer);
		if(pObject==NULL) throw _T("�ӿڲ�ѯʧ��");

		return pObject;
	}
	catch (...) { }

	//�������
	SafeDelete(pGameRankManager);

	return NULL;
}

//////////////////////////////////////////////////////////////////////////
