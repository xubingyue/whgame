#ifndef CLIENT_KERNEL_SINK_HEAD_FILE
#define CLIENT_KERNEL_SINK_HEAD_FILE

#pragma once

#include "Stdafx.h"

class CGameFrameDlg;

//////////////////////////////////////////////////////////////////////////

//�ں˹�����
class CClientKernelSink : public IClientKernelSink
{
	//��������
protected:
	CGameFrameDlg				& m_GameFrameDlg;						//��Ϸ���

	//��������
public:
	//���캯��
	CClientKernelSink(CGameFrameDlg & GameFrameDlg);
	//��������
	virtual ~CClientKernelSink();

	//�����ӿ�
public:
	//�ͷŶ���
	virtual bool __cdecl Release() { if (IsValid()) delete this; return true; }
	//�Ƿ���Ч
	virtual bool __cdecl IsValid() { return AfxIsValidAddress(this,sizeof(CClientKernelSink))?true:false; }
	//�ӿڲ�ѯ
	virtual void * __cdecl QueryInterface(const IID & Guid, DWORD dwQueryVer);

	//�����ӿ�
private:
	//��ȡ����
	virtual HWND __cdecl GetFrameWnd();
	//����״̬
	virtual void __cdecl ResetGameFrame();
	//�رմ���
	virtual void __cdecl CloseGameFrame(bool bForceClose);

	//�ں��¼�
private:
	//ʱ����Ϣ
	virtual bool __cdecl OnEventTimer(WORD wChairID, UINT nElapse, UINT nTimerID);
	//������Ϣ
	virtual bool __cdecl OnEventSocket(const CMD_Command & Command, const void * pBuffer, WORD wDataSize);
	//������Ϣ
	virtual bool __cdecl OnEventProcess(const IPC_Head & Head, const void * pBuffer, WORD wDataSize, HWND hWndSend);

	//��Ϸ�¼�
private:
	//��Ϸ״̬
	virtual bool __cdecl OnEventGameScene(BYTE cbGameStation, bool bLookonOther, void * pBuffer, WORD wDataSize);
	//������Ϣ
	virtual bool __cdecl OnUserChatMessage(tagUserData * pSendUserData, tagUserData * pRecvUserData, LPCTSTR pszChatMessage, COLORREF crColor);
	//ʱ�����
	virtual void __cdecl OnEventTimerKilled(WORD wChairID, UINT nTimerID);
	//�Թ�״̬
	virtual void __cdecl OnEventLookonChanged(bool bLookonUser, void * pBuffer, WORD wDataSize);

	//�û��¼�
public:
	//�û�����
	virtual void __cdecl OnEventUserEnter(tagUserData * pUserData, WORD wChairID, bool bLookonUser);
	//�û��뿪
	virtual void __cdecl OnEventUserLeave(tagUserData * pUserData, WORD wChairID, bool bLookonUser);
	//�û�����
	virtual void __cdecl OnEventUserScore(tagUserData * pUserData, WORD wChairID, bool bLookonUser);
	//�û�״̬
	virtual void __cdecl OnEventUserStatus(tagUserData * pUserData, WORD wChairID, bool bLookonUser);
};

//////////////////////////////////////////////////////////////////////////

#endif