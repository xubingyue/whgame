#ifndef GameRank_HEAD_FILE
#define GameRank_HEAD_FILE

//////////////////////////////////////////////////////////////////////////

//ƽ̨ͷ�ļ�
#include "..\..\ģ���\Template.h"

//ȫ��ͷ�ļ�
#include "..\..\�����ļ�\GlobalDef.h"

//���ͷ�ļ�
#include "..\..\����ӿ�\IUnknownEx.h"

//////////////////////////////////////////////////////////////////////////
//�����궨��

//��������
#ifndef GAMERANK_CLASS
	#ifdef  GAMERANK_DLL
		#define GAMERANK_CLASS _declspec(dllexport)
	#else
		#define GAMERANK_CLASS _declspec(dllimport)
	#endif
#endif

//ģ�鶨��
#ifdef _DEBUG
	#define GAMERANK_DLL_NAME	TEXT("GameRankD.dll")					//��� DLL ����
#else
	#define GAMERANK_DLL_NAME	TEXT("GameRank.dll")					//��� DLL ����
#endif

//////////////////////////////////////////////////////////////////////////

#define VER_IGameRankManager INTERFACE_VERSION(1,1)
static const GUID IID_IGameRankManager={0x850e5617,0x4eab,0x4f2e,0xae,0x11,0xef,0xa3,0x22,0x65,0xe0,0xc2};

//��Ϸ�ȼ��ӿ�
interface IGameRankManager : public IUnknownEx
{
	//��ȡ�ȼ�
	virtual LPCTSTR __cdecl GetGameRank(WORD wKindID, LONG lScore, WORD wGameGenre)=NULL;
};

//////////////////////////////////////////////////////////////////////////

//��ϵ��������
class CGameRankManagerHelper : public CTempldateHelper<IGameRankManager>
{
	//��������
public:
	//���캯��
	CGameRankManagerHelper(void) : CTempldateHelper<IGameRankManager>(IID_IGameRankManager,
		VER_IGameRankManager,GAMERANK_DLL_NAME,TEXT("CreateGameRankManager")) { }
};

//////////////////////////////////////////////////////////////////////////

#endif