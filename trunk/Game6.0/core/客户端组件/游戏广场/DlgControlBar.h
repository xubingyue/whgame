#ifndef DLG_CONTROL_BAR_HEAD_FILE
#define DLG_CONTROL_BAR_HEAD_FILE

#pragma once

#include "Stdafx.h"
#include "Resource.h"
#include "RoomViewItem.h"
#include "PlazaViewItem.h"

//////////////////////////////////////////////////////////////////////////
//�궨��

#define MAX_SERVER						3								//��󷿼�
#define CONTROL_BAR_HEIGHT				39								//��������

//////////////////////////////////////////////////////////////////////////

//�������Ի���
class CDlgControlBar : public CDialog
{
	//״̬����
public:
	CRect								m_rcViewItem;					//����λ��
	IViewItem							* m_pActiveViewItem;			//��ǰ��ͼ
	CPlazaViewItem						* m_pPlazaViewItem;				//�㳡��ͼ
	CRoomViewItem						* m_pRoomViewItemCreate;		//��������
	CRoomViewItem						* m_pRoomViewItem[MAX_SERVER];	//����ӿ�
	
	//��Դ����
protected:
	CSkinImage							m_ImageLeft;					//ͼƬ��Դ
	CSkinImage							m_ImageMin;						//ͼƬ��Դ
	CSkinImage							m_ImageRight;					//ͼƬ��Դ

	//������ť
public:
	CSkinButton							m_btGamePlaza;					//��Ϸ�㳡
	CSkinButton							m_btViewItem[MAX_SERVER];		//���䰴ť

	//���ܰ�ť
public:
	CSkinButton							m_btQuitGame;					//�˳���Ϸ
	CSkinButton							m_btCompanion;					//��ϵ����
	CSkinButton							m_btSwitchUser;					//�л��ʺ�
	CSkinButton							m_btGlobalOption;				//ϵͳ����

	//�Ի�������
	enum { IDD = IDD_CONTROL_BAR };

	//��������
public:
	//���캯��
	CDlgControlBar();
	//��������
	virtual ~CDlgControlBar();

	//���غ���
protected:
	//�ؼ���
	virtual void DoDataExchange(CDataExchange * pDX);
	//��ʼ������
	virtual BOOL OnInitDialog();
	//�����
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);

	//���ܺ���
public:
	//����λ��
	void SetViewItemRect(int nXPos, int nYPos, int nWidth, int nHeight);
	//��ȡ�㳡
	CPlazaViewItem * GetPlazaViewItem() { return m_pPlazaViewItem; }
	//���ù㳡
	void SetPlazaViewItem(CPlazaViewItem * pPlazaViewItem) { m_pPlazaViewItem=pPlazaViewItem; }

	//���ܺ���
public:
	//��ʾ��ҳ
	void WebBrowse(LPCTSTR lpszUrl, bool bForceBrowse);
	//��ʾ��Ϣ
    int ShowMessageBox(LPCTSTR pszMessage, UINT nType);

	//���亯��
public:
	//����㳡
	void ActivePlazaViewItem();
	//�����
	void ActiveRoomViewItem(CRoomViewItem * pRoomViewItem);
	//���ҷ���
	CRoomViewItem * SearchRoomViewItem(WORD wKindID, WORD wServerID);
	//���뷿��
	CRoomViewItem * CreateRoomViewItem(CListServer * pListServer);
	//�رշ���
	void CloseRoomViewItem(IRoomViewItem * pIRoomViewItem);
	//�رշ���
	void CloseAllRoomViewItem();
	//�رյ�ǰ
	void CloseCurrentViewItem();

	//�ڲ�����
private:
	//���¿���
	void UpdateControlButton();

	//��Ϣ����
protected:
	//�ػ�����
	afx_msg void OnPaint();
	//��Ϸ�㳡
	afx_msg void OnBnClickedPlaza();
	//��Ϸ����
	afx_msg void OnBnClickedViewItem1();
	//��Ϸ����
	afx_msg void OnBnClickedViewItem2();
	//��Ϸ����
	afx_msg void OnBnClickedViewItem3();
	//��Ϸ����
	afx_msg void OnBnClickedViewItem4();
	//�л���ť
	afx_msg void OnBnClickedSwitchAccounts();
	//��ϵ��ť
	afx_msg void OnBnClickedCompanion();
	//���ð�ť
	afx_msg void OnBnClickedGlobalOption();
	//�˳���ť
	afx_msg void OnBnClickedQuitGame();
	//�滭����
	afx_msg BOOL OnEraseBkgnd(CDC * pDC);
	//λ����Ϣ
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//�رշ���
	LRESULT OnCloseRoomViewItem(WPARAM wParam, LPARAM lParam);

	DECLARE_MESSAGE_MAP()
};

//////////////////////////////////////////////////////////////////////////

//������ָ��
extern CDlgControlBar * g_pControlBar;

//////////////////////////////////////////////////////////////////////////

#endif