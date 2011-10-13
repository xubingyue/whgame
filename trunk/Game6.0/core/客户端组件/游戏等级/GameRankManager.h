
#pragma once

#include "Interface.h"

//////////////////////////////////////////////////////////////////////////

//��Ϸ�ȼ�����
class CGameRankManager : public IGameRankManager
{
	//��������
public:
	//���캯��
	CGameRankManager(void);
	//��������
	virtual ~CGameRankManager(void);

	//�����ӿ�
public:
	//�ͷŶ���
	virtual bool __cdecl Release() { if (IsValid()) delete this; return true; }
	//�Ƿ���Ч
	virtual bool __cdecl IsValid() { return AfxIsValidAddress(this,sizeof(CGameRankManager))?true:false; }
	//�ӿڲ�ѯ
	virtual void * __cdecl QueryInterface(const IID & Guid, DWORD dwQueryVer);

	//����ӿ�
public:
	//��ȡ�ȼ�
	virtual LPCTSTR __cdecl GetGameRank(WORD wKindID, LONG lScore, WORD wGameGenre);
};

//////////////////////////////////////////////////////////////////////////
