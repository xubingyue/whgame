#include "StdAfx.h"
#include "GameRankManager.h"

//////////////////////////////////////////////////////////////////////////

//构造函数
CGameRankManager::CGameRankManager()
{
}

//析构函数
CGameRankManager::~CGameRankManager()
{
}

//接口查询
void * __cdecl CGameRankManager::QueryInterface(const IID & Guid, DWORD dwQueryVer)
{
	QUERYINTERFACE(IGameRankManager,Guid,dwQueryVer);
	QUERYINTERFACE_IUNKNOWNEX(IGameRankManager,Guid,dwQueryVer);
	return NULL;
}

//金币类型
LPCTSTR __cdecl CGameRankManager::GetGameRank(WORD wKindID, LONG lScore, WORD wGameGenre)
{
	return TEXT("");
}

//////////////////////////////////////////////////////////////////////////

//建立对象函数
extern "C" __declspec(dllexport) void * __cdecl CreateGameRankManager(const GUID & Guid, DWORD dwInterfaceVer)
{
	//建立对象
	CGameRankManager *pGameRankManager=NULL;
	try
	{
		pGameRankManager = new CGameRankManager();
		if(pGameRankManager==NULL) throw _T("创建失败");

		void *pObject = pGameRankManager->QueryInterface(Guid,dwInterfaceVer);
		if(pObject==NULL) throw _T("接口查询失败");

		return pObject;
	}
	catch (...) { }

	//清理对象
	SafeDelete(pGameRankManager);

	return NULL;
}

//////////////////////////////////////////////////////////////////////////
