#ifndef GAME_FRAME_HEAD_FILE
#define GAME_FRAME_HEAD_FILE

#pragma once

#include "Stdafx.h"
#include "Resource.h"
#include "DlgControlBar.h"
#include "PlazaViewItem.h"

/////////////////////////////////////////////////////////////////////////////

//�ȼ�����
#define IDI_HOT_KEY_BOSS			0x0100								//�ϰ��ȼ�

/////////////////////////////////////////////////////////////////////////////

//�������
class CGameFrame : public CFrameWnd
{
	//�ؼ�����
public:
	CSkinButton							m_btMin;						//��С��ť
	CSkinButton							m_btMax;						//���ť
	CSkinButton							m_btClose;						//�رհ�ť
	CWebBrowser							m_BrowerAD;						//�������
	CToolTipCtrl						m_ToolTipCtrl;					//��ʾ�ؼ�
	CPlazaViewItem						m_DlgGamePlaza;					//��Ϸ�㳡
	CDlgControlBar						m_DlgControlBar;				//��������

	//����״̬
protected:
	bool								m_bMaxShow;						//����־
	CRect								m_rcNormalSize;					//����λ��

	//������ť
public:
	CSkinButton							m_btButton1;					//���ܰ�ť
	CSkinButton							m_btButton2;					//���ܰ�ť
	CSkinButton							m_btButton3;					//���ܰ�ť
	CSkinButton							m_btButton4;					//���ܰ�ť
	CSkinButton							m_btButton5;					//���ܰ�ť

	//��Դ����
protected:
	CSkinImage							m_ImageL;						//��ԴͼƬ
	CSkinImage							m_ImageR;						//��ԴͼƬ
	CSkinImage							m_ImageTL;						//��ԴͼƬ
	CSkinImage							m_ImageTM;						//��ԴͼƬ
	CSkinImage							m_ImageTR;						//��ԴͼƬ

	//��������	
public:
	//���캯��
	CGameFrame();
	//��������
	virtual ~CGameFrame();

	//���غ���
public:
	//��Ϣ����
	virtual BOOL PreTranslateMessage(MSG * pMsg);

	//���溯��
protected:
	//��󴰿�
	bool MaxSizeWindow();
	//��ԭ����
	bool RestoreWindow();

	//��Ϣ����
protected:
	//�滭��Ϣ
	afx_msg void OnPaint();
	//�滭����
	afx_msg BOOL OnEraseBkgnd(CDC * pDC);
	//������Ϣ
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//��С��Ϣ
	afx_msg void OnGetMinMaxInfo(MINMAXINFO FAR * lpMMI);
	//λ����Ϣ
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//��С��ť
	afx_msg void OnBnClickedMin();
	//��С��ť
	afx_msg void OnBnClickedMax();
	//�رհ�ť
	afx_msg void OnBnClickedClose();
	//��������
	afx_msg LRESULT OnNcHitTest(CPoint Point);
	//�����Ϣ
	afx_msg void OnLButtonDown(UINT nFlags, CPoint Point);
	//�����Ϣ
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint Point);
	//�ı���Ϣ
	afx_msg void OnSettingChange(UINT uFlags, LPCTSTR lpszSection);
	//�ر���Ϣ
	afx_msg void OnClose();

	//������ť
protected:
	//���ܰ�ť
	afx_msg void OnBnClickedButton1();
	//���ܰ�ť
	afx_msg void OnBnClickedButton2();
	//���ܰ�ť
	afx_msg void OnBnClickedButton3();
	//���ܰ�ť
	afx_msg void OnBnClickedButton4();
	//���ܰ�ť
	afx_msg void OnBnClickedButton5();

	//�Զ�����Ϣ
protected:
	//�ȼ���Ϣ
	LRESULT OnHotKeyMessage(WPARAM wParam, LPARAM lParam);
	//��װ���
	LRESULT OnMessageSetupFinish(WPARAM wParam, LPARAM lParam);

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

#endif
