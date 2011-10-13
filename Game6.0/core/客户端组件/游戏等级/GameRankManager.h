
#pragma once

#include "Interface.h"

//////////////////////////////////////////////////////////////////////////

//游戏等级管理
class CGameRankManager : public IGameRankManager
{
	//函数定义
public:
	//构造函数
	CGameRankManager(void);
	//析构函数
	virtual ~CGameRankManager(void);

	//基础接口
public:
	//释放对象
	virtual bool __cdecl Release() { if (IsValid()) delete this; return true; }
	//是否有效
	virtual bool __cdecl IsValid() { return AfxIsValidAddress(this,sizeof(CGameRankManager))?true:false; }
	//接口查询
	virtual void * __cdecl QueryInterface(const IID & Guid, DWORD dwQueryVer);

	//组件接口
public:
	//获取等级
	virtual LPCTSTR __cdecl GetGameRank(WORD wKindID, LONG lScore, WORD wGameGenre);
};

//////////////////////////////////////////////////////////////////////////
