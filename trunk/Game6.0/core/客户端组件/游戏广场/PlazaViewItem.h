#pragma once

#include "Stdafx.h"
#include "DlgLogon.h"
#include "UserInfoView.h"
#include "ServerItemView.h"

//////////////////////////////////////////////////////////////////////////

//��Ϸ�㳡
class CPlazaViewItem : public CDialog, public IPlazaViewItem,public IClientSocketSink,
	public ISplitterSink, public ITreeCtrlSink
{
	//״̬����
protected:
	bool						m_bRectify;				//������־
	bool						m_bInitDialog;			//��ʼ��־
	bool						m_bLogonPlaza;			//��¼��־

	//�ؼ�����
public:
	CDlgLogon					m_DlgLogon;				//��¼�Ի���
	CUserInfoView				m_UserInfoView;			//��Ϸ��ͼ
	CSkinSplitter				m_Splitter;				//��ִ���
	CServerItemView				m_ServerItemView;		//��������ͼ
	CClientSocketHelper			m_ClientSocket;			//��������

	//������ť
public:
	CSkinButton					m_WEB_BEFORE;
	CSkinButton					m_WEB_BRUSH;
	CSkinButton					m_WEB_HOME;
	CSkinButton					m_WEB_NEXT;
	CSkinButton					m_WEB_STOP;

	//�ؼ�����
public:
	CHtmlBrower *				m_pHtmlBrower;			//�������
	CToolTipCtrl				m_ToolTipCtrl;			//��ʾ�ؼ�

	//��Ϸ�б�
protected:
	CSkinImage					m_ImageServerBL;		
	CSkinImage					m_ImageServerBM;		
	CSkinImage					m_ImageServerBR;		
	CSkinImage					m_ImageServerLM;		
	CSkinImage					m_ImageServerRM;		
	CSkinImage					m_ImageServerTL;		
	CSkinImage					m_ImageServerTM;		
	CSkinImage					m_ImageServerTR;		

	//��ҳ���
protected:
	CSkinImage					m_ImageWebBL;			
	CSkinImage					m_ImageWebBM;			
	CSkinImage					m_ImageWebBR;			
	CSkinImage					m_ImageWebLM;			
	CSkinImage					m_ImageWebRM;			
	CSkinImage					m_ImageWebTL;			
	CSkinImage					m_ImageWebTM;			
	CSkinImage					m_ImageWebTR;			

	//��������
public:
	CPlazaViewItem();
	virtual ~CPlazaViewItem();

	//���غ���
protected:
	//�ؼ���
	virtual void DoDataExchange(CDataExchange * pDX);
	//��Ϣ����
	virtual BOOL PreTranslateMessage(MSG * pMsg);
	//��ʼ������
	virtual BOOL OnInitDialog();
	//ȷ������
	virtual void OnOK() { return; };
	//ȡ������
	virtual void OnCancel() { return; };

	//�����ӿ�
public:
	//�ͷŶ���
	virtual bool __cdecl Release() { if (IsValid()) delete this; return true; }
	//�Ƿ���Ч
	virtual bool __cdecl IsValid() { return AfxIsValidAddress(this,sizeof(CPlazaViewItem))?true:false; }
	//�ӿڲ�ѯ
	virtual void * __cdecl QueryInterface(const IID & Guid, DWORD dwQueryVer);

	//��ͼ�ӿ�
public:
	//��ȡ���
	virtual HWND __cdecl GetWindowHandle() { return GetSafeHwnd(); }

	//������ӿ�
public:
	//��ť��Ϣ
	virtual bool __cdecl OnSplitterButton(CSkinSplitter * pSkinSplitter, CSkinButton * pSplitterButton);
	//�������Ϣ
	virtual bool __cdecl OnSplitterEvent(CSkinSplitter * pSkinSplitter, UINT uSplitID, int nXPos, int nYPos);

	//����ӿ�
public:
	//�������
	virtual void __cdecl OnTreeLeftClick(CListItem * pListItem, HTREEITEM hTreeItem, CTreeCtrl * pTreeCtrl);
	//�Ҽ�����
	virtual void __cdecl OnTreeRightClick(CListItem * pListItem, HTREEITEM hTreeItem, CTreeCtrl * pTreeCtrl);
	//���˫��
	virtual void __cdecl OnTreeLeftDBClick(CListItem * pListItem, HTREEITEM hTreeItem, CTreeCtrl * pTreeCtrl);
	//�Ҽ�˫��
	virtual void __cdecl OnTreeRightDBClick(CListItem * pListItem, HTREEITEM hTreeItem, CTreeCtrl * pTreeCtrl);
	//ѡ��ı�
	virtual void __cdecl OnTreeSelectChanged(CListItem * pListItem, HTREEITEM hTreeItem, CTreeCtrl * pTreeCtrl);
	//����չ��
	virtual void __cdecl OnTreeItemexpanded(CListItem * pListItem, HTREEITEM hTreeItem, CTreeCtrl * pTreeCtrl);

	//����ӿ�
public:
	//����������Ϣ
	virtual bool __cdecl OnSocketConnect(int iErrorCode, LPCTSTR pszErrorDesc, IClientSocket * pIClientSocke);
	//�����ȡ��Ϣ
	virtual bool __cdecl OnSocketRead(CMD_Command Command, void * pBuffer, WORD wDataSize, IClientSocket * pIClientSocke);
	//����ر���Ϣ
	virtual bool __cdecl OnSocketClose(IClientSocket * pIClientSocke, bool bCloseByServer);

	//��Ϣ����
protected:
	//��¼��Ϣ
	bool OnSocketMainLogon(CMD_Command Command, void * pBuffer, WORD wDataSize, IClientSocket * pIClientSocke);
	//�б���Ϣ
	bool OnSocketMainServerList(CMD_Command Command, void * pBuffer, WORD wDataSize, IClientSocket * pIClientSocke);
	//ϵͳ��Ϣ
	bool OnSocketMainSystem(CMD_Command Command, void * pBuffer, WORD wDataSize, IClientSocket * pIClientSocke);

	//�㳡�ӿ�
public:
	//��¼��Ϣ
	virtual bool __cdecl SendLogonMessage();
	//������Ϣ
	virtual bool __cdecl SendConnectMessage();

	//���ܺ���
public:
	//��ʾ��ҳ
	void WebBrowse(LPCTSTR lpszUrl, bool bForceBrowse);
	//��ʾ��Ϣ
    int ShowMessageBox(LPCTSTR pszMessage, UINT nType);

	//�ڲ�����
private:
	//���±���
	void UpdateTitleText();
	//�滭��ҳ
	void DrawWebFrame(CDC * pDC);
	//�滭�б�
	void DrawListFrame(CDC * pDC);
	//�����ؼ�
	void RectifyControl(int nWidth, int nHeight);

	//��Ϣ����
protected:
	//�滭��Ϣ
	afx_msg void OnPaint();
	//�滭����
	afx_msg BOOL OnEraseBkgnd(CDC * pDC);
	//��¼�㳡
	afx_msg void OnCommandLogon();
	//���ӷ�����
	afx_msg void OnCommandConnect();
	//ȡ������
	afx_msg void OnCommandCancelConnect();
	//λ����Ϣ
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//��ʾ��Ϣ
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);

	//������ť
	afx_msg void OnBnClickedBEFORE();
	afx_msg void OnBnClickedNEXT();
	afx_msg void OnBnClickedMBRUSH();
	afx_msg void OnBnClickedSTOP();
	afx_msg void OnBnClickedHOME();
	afx_msg void OnBnClickedBBS();

	DECLARE_MESSAGE_MAP()
};

//////////////////////////////////////////////////////////////////////////
