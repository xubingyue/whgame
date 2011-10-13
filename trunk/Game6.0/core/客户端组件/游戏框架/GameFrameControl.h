#ifndef GAME_FRAME_CONTROL_HEAD_FILE
#define GAME_FRAME_CONTROL_HEAD_FILE

#pragma once

#include "GameFrame.h"
#include "UserListView.h"
#include "GameFrameDlg.h"

//��˵��
class CClientKernelSink;

//////////////////////////////////////////////////////////////////////////

//��ܿ�����ͼ
class GAME_FRAME_CLASS CGameFrameControl : public CDialog
{
	//��������
protected:
	bool								m_bRectify;						//������־
	bool								m_bInitDialog;					//������־
	tagUserData *						m_pUserData;					//�û�ָ��

	//�������
protected:
	CGameFrameDlg						* m_pGameFrameDlg;				//�Ի���
	IClientKernel						* m_pIClientKernel;				//�ں˽ӿ�

	//����ͼ��
protected:
	CSkinImage							m_ImageLeftViewLM;				//��ԴͼƬ
	CSkinImage							m_ImageLeftViewMM;				//��ԴͼƬ
	CSkinImage							m_ImageLeftViewRM;				//��ԴͼƬ
	CSkinImage							m_ImageLeftViewLTM;				//��ԴͼƬ
	CSkinImage							m_ImageLeftViewRTM;				//��ԴͼƬ
	CSkinImage							m_ImageLeftViewLT;				//��ԴͼƬ
	CSkinImage							m_ImageLeftViewMT;				//��ԴͼƬ
	CSkinImage							m_ImageLeftViewRT;				//��ԴͼƬ
	CSkinImage							m_ImageLeftViewLB;				//��ԴͼƬ
	CSkinImage							m_ImageLeftViewMB;				//��ԴͼƬ
	CSkinImage							m_ImageLeftViewRB;				//��ԴͼƬ
	CSkinImage							m_ImageLeftViewLBM;				//��ԴͼƬ
	CSkinImage							m_ImageLeftViewRBM;				//��ԴͼƬ

	//����ؼ�
public:
	CComboBox							m_ChatInput;					//��������
	CComboBox							m_ChatObject;					//�������
	CWebBrowser							m_BrowerAD;						//�������
	CSkinButton							m_btPhrase;						//���ﰴť
	CSkinButton							m_btColorSet;					//��ɫ����
	CSkinButton							m_btCleanScreen;				//������ť
	CSkinButton							m_btSendChat;					//���Ͱ�ť
	CSkinButton							m_btExpression;					//���鰴ť
	CExpression							m_Expression;					//���鴰��
	CSkinRichEdit						m_ChatMessage;					//�������

	//��������
public:
	CSkinButton							m_btSound;						//��Ϸ����
	CSkinButton							m_btLookOn;						//�Թ�����
	CSkinButton							m_btGameRule;					//��Ϸ����
	CSkinButton							m_btGameOption;					//��Ϸ����

	//�ؼ�����
public:
	CToolTipCtrl						m_ToolTipCtrl;					//��ʾ�ؼ�
	CUserListView						m_UserListView;					//�û��б�

	//��������
public:
	//���캯��
	CGameFrameControl(CGameFrameDlg * pGameFrameDlg); 
	//��������
	virtual ~CGameFrameControl();

	//���غ���
protected:
	//�ؼ���
	virtual void DoDataExchange(CDataExchange * pDX);
	//��ʼ������
	virtual BOOL OnInitDialog();
	//ȷ������
	virtual void OnOK() { return; };
	//ȡ������
	virtual void OnCancel() { return; };
	//��Ϣ����
	virtual BOOL PreTranslateMessage(MSG * pMsg);
	//�˵�����
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);

	//���ú���
public:
	//�����ں�
	void SetClientKernel(IClientKernel * pIClientKernel);

	//���ܺ���
public:
	//���ÿ���
	void ResetGameFrameControl();
	//�����û�
	bool InsertUserItem(tagUserData * pUserData);
	//�����û�
	bool UpdateUserItem(tagUserData * pUserData);
	//ɾ���û�
	bool DeleteUserItem(tagUserData * pUserData);

	//�ڲ�����
protected:
	//����ͼ��
	void DrawLeftViewFrame(CDC * pDC);
	//�����ؼ�
	void RectifyControl(int nWidth, int nHeight);

	//��Ϣ����
protected:
	//�滭��Ϣ
	afx_msg void OnPaint();
	//��Ϸ����
	afx_msg void OnBnClickedRule();
	//��Ϸ����
	afx_msg void OnBnClickedSound();
	//��Ϸ�Թ�
	afx_msg void OnBnClickedLookon();
	//��Ϸ����
	afx_msg void OnBnClickedOption();
	//�滭����
	afx_msg BOOL OnEraseBkgnd(CDC * pDC);
	//λ����Ϣ
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//���Ͱ�ť
	afx_msg void OnBnClickedSendChat();
	//���鰴ť
	afx_msg void OnBnClickedExpression();
	//��ɫ��ť
	afx_msg void OnBnClickedColorSet();
	//������ť
	afx_msg void OnBnClickedCleanScreen();
	//������Ϣ
	LRESULT OnHitExpression(WPARAM wParam, LPARAM lParam);
	//�Ҽ��б�
	afx_msg void OnNMRclickUserList(NMHDR * pNMHDR, LRESULT * pResult);

	DECLARE_MESSAGE_MAP()
};

//////////////////////////////////////////////////////////////////////////

#endif