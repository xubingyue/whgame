#pragma once

#include "StdAfx.h"
#include "Resource.h"
#include "Afxcmn.h"

//���Ͷ���Ϣ��
class CShortMessage : public CSkinDialogEx
{
	//��������
public:
	CWnd								* m_pParentWnd;						//������
	
	//��Ϣ����
	long int							m_dwTargetUserID;					//�Ի��û�
	__int64								m_dwTargerAccID;					//ACC ����
	CString								m_strTargerName;					//�û�����
	CString								m_strRoomName;						//��������
	IUserItem							* m_pTargetUserItem;				//Ŀ���û�

	//�ؼ�����
public:
	CEdit								m_SendMessage;						//���ʹ���
	CSkinRichEdit						m_RecvMessage;						//���ܴ���
	CSkinButton							m_BtSend;							//���Ͱ�ť
	CSkinButton							m_BtExpression;						//���鰴ť
	CSkinButton							m_BtClose;							//�˳���ť
	CMessageProxyHelper					m_MessageProxyHelper;				//��Ϣ����
	CExpression							m_ExpressWnd;						//���鴰��

	DECLARE_MESSAGE_MAP()

	//��������
public:
	//���캯��
	CShortMessage(CWnd * pParentWnd);
	//��������
	virtual ~CShortMessage();
	//��ʼ������
	virtual BOOL OnInitDialog();

	//���غ���
protected:
	//�ؼ��󶨺���
	virtual void DoDataExchange(CDataExchange * pDX); 
	//ȷ����ť
	virtual void OnOK();
	//ȡ����ť
	virtual void OnCancel();
	//��Ϣ���ͺ���
	virtual BOOL PreTranslateMessage(MSG * pMsg);

	//���ܺ��� 
public:
	//������Ϣ
	void SetTalkInfo(IUserItem * pTargerUserItem, TCHAR * szRoomName);
	//�յ���Ϣ
	void OnRecvMessage(TCHAR * szSendName, TCHAR * szMessage, COLORREF crColor, bool bMeMessage);

	//��ť����
public:
	//���鰴ť
	void OnBnClickedExpression();

	//��Ϣ����
public:
	//���Ͱ�ť
	afx_msg void OnBnClickedSendShort();
	//�˳���ť
	afx_msg void OnBnClickedClose();
	//��ȡλ��
	afx_msg void OnGetMinMaxInfo(MINMAXINFO * lpMMI);
	//������Ϣ
	LRESULT OnExpression(WPARAM wparam, LPARAM lparam);
};
