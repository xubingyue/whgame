#include "Stdafx.h"
#include "GameFrame.h"
#include "DlgOption.h"
#include "GlobalUnits.h"
#include "SystemOption.h"
#include "DlgControlBar.h"

//////////////////////////////////////////////////////////////////////////

//�ؼ���ʶ
#define IDC_VIEW_ITEM					100								//�ؼ���ʶ

//��Ϣ����
#define WM_CLOSE_ROOM_VIEW_ITEM			WM_USER+10						//�ر���Ϣ

//////////////////////////////////////////////////////////////////////////

//������ָ��
CDlgControlBar		* g_pControlBar=NULL;

//////////////////////////////////////////////////////////////////////////

BEGIN_MESSAGE_MAP(CDlgControlBar, CDialog)
	ON_WM_SIZE()
	ON_WM_PAINT()
	ON_WM_ERASEBKGND()
	ON_BN_CLICKED(IDC_PLAZA, OnBnClickedPlaza)
	ON_BN_CLICKED(IDC_QUIT_GAME, OnBnClickedQuitGame)
	ON_BN_CLICKED(IDC_SYSTEM_OPTION, OnBnClickedGlobalOption)
	ON_BN_CLICKED(IDC_COMPANION_MANAGER, OnBnClickedCompanion)
	ON_BN_CLICKED(IDC_SWITCH_ACCOUNTS, OnBnClickedSwitchAccounts)
	ON_MESSAGE(WM_CLOSE_ROOM_VIEW_ITEM,OnCloseRoomViewItem)
END_MESSAGE_MAP()

//////////////////////////////////////////////////////////////////////////

//��������
CDlgControlBar::CDlgControlBar() : CDialog(IDD_CONTROL_BAR)
{
	//���ñ���
	g_pControlBar=this;
	m_pPlazaViewItem=NULL;
	m_pActiveViewItem=NULL;
	m_pRoomViewItemCreate=NULL;
	memset(m_pRoomViewItem,0,sizeof(m_pRoomViewItem));

	return;
}

//��������
CDlgControlBar::~CDlgControlBar()
{
	//ɾ������
	for (int i=0;i<CountArray(m_pRoomViewItem);i++)
	{
		if (m_pRoomViewItem[i]==NULL) break;
		SafeDelete(m_pRoomViewItem[i]);
		m_pRoomViewItem[i]=NULL;
	}

	return;
}

//�ؼ���
void CDlgControlBar::DoDataExchange(CDataExchange * pDX)
{
	__super::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_PLAZA, m_btGamePlaza);
	DDX_Control(pDX, IDC_SWITCH_ACCOUNTS, m_btSwitchUser);
	DDX_Control(pDX, IDC_SYSTEM_OPTION, m_btGlobalOption);
	DDX_Control(pDX, IDC_COMPANION_MANAGER, m_btCompanion);
	DDX_Control(pDX, IDC_QUIT_GAME, m_btQuitGame);
}

//��ʼ������
BOOL CDlgControlBar::OnInitDialog()
{
	__super::OnInitDialog();

	//����λͼ
	HINSTANCE hInstance=AfxGetInstanceHandle();
	m_ImageLeft.SetLoadInfo(IDB_BAR_LEFT,hInstance);
	m_ImageMin.SetLoadInfo(IDB_BAR_MIN,hInstance);
	m_ImageRight.SetLoadInfo(IDB_BAR_RIGHT,hInstance);

	//���ð�ť
	m_btGamePlaza.SetButtonImage(IDB_BAR_ITEM_HOME,hInstance,false);
	m_btSwitchUser.SetButtonImage(IDB_BAR_BUTTON_NUMBER,hInstance,false);
	m_btGlobalOption.SetButtonImage(IDB_BAR_BUTTON_SET,hInstance,false);
	m_btCompanion.SetButtonImage(IDB_BAR_BUTTON_FRIEND,hInstance,false);
	m_btQuitGame.SetButtonImage(IDB_BAR_BUTTON_QUIT,hInstance,false);

	//������ť
	for (WORD i=0;i<CountArray(m_btViewItem);i++)
	{
		CRect rcCreate(0,0,0,0);
		m_btViewItem[i].Create(NULL,WS_CHILD,rcCreate,this,IDC_VIEW_ITEM+i);
		m_btViewItem[i].SetButtonImage(IDB_BAR_ITEM,AfxGetInstanceHandle(),false);
	}

	return TRUE;
}

//�����
BOOL CDlgControlBar::OnCommand(WPARAM wParam, LPARAM lParam)
{
	//��������
	UINT nCommandID=LOWORD(wParam);

	//�л���ť
	if ((nCommandID>=IDC_VIEW_ITEM)&&(nCommandID<(IDC_VIEW_ITEM+CountArray(m_btViewItem))))
	{
		ActiveRoomViewItem(m_pRoomViewItem[nCommandID-IDC_VIEW_ITEM]);
		return TRUE;
	}

	return __super::OnCommand(wParam,lParam);
}

//�ػ�����
void CDlgControlBar::OnPaint()
{
	CPaintDC dc(this);

	//��ȡλ��
	CRect rcClientRect;
	GetClientRect(&rcClientRect);

	//����λͼ
	CImageHandle ImageLHandle(&m_ImageLeft);
	CImageHandle ImageMHandle(&m_ImageMin);
	CImageHandle ImageRHandle(&m_ImageRight);

	//��������ͼ
	CImage ImageBuffer;
	ImageBuffer.Create(rcClientRect.Width(),rcClientRect.Height(),16);
	HDC hDCBuffer=ImageBuffer.GetDC();

	//�滭����
	m_ImageLeft.BitBlt(hDCBuffer,0,0);
	for (int nXPos=m_ImageLeft.GetWidth();nXPos<rcClientRect.Width();nXPos+=m_ImageMin.GetWidth())
	{
		m_ImageMin.BitBlt(hDCBuffer,nXPos,0);
	}
	m_ImageRight.BitBlt(hDCBuffer,rcClientRect.Width()-m_ImageRight.GetWidth(),0);
	ImageBuffer.ReleaseDC();

	//�滭����
	ImageBuffer.BitBlt(dc,0,0);

	return;
}

//λ����Ϣ
void CDlgControlBar::OnSize(UINT nType, int cx, int cy)
{
	__super::OnSize(nType, cx, cy);

	//�ж�״̬
	if (m_btGamePlaza.GetSafeHwnd()==NULL) return;

	//��ȡλ��
	CRect rcItemRect,rcButtonRect;
	m_btGamePlaza.GetWindowRect(&rcItemRect);
	m_btQuitGame.GetWindowRect(&rcButtonRect);

	//��������
	const UINT uFlags=SWP_NOACTIVATE|SWP_NOZORDER|SWP_NOSIZE|SWP_NOCOPYBITS;
	CButton * pButton[]={&m_btQuitGame,&m_btCompanion,&m_btGlobalOption,&m_btSwitchUser};

	//�ƶ��ؼ�
	HDWP hDwp=BeginDeferWindowPos(32);
	DeferWindowPos(hDwp,m_btGamePlaza,NULL,8,6,0,0,uFlags);
	for (int i=0;i<CountArray(m_btViewItem);i++) DeferWindowPos(hDwp,m_btViewItem[i],NULL,85+rcItemRect.Width()*i+10,3,0,0,uFlags);
	for (int i=0;i<CountArray(pButton);i++) DeferWindowPos(hDwp,pButton[i]->m_hWnd,NULL,cx-(rcButtonRect.Width()+6)*(i+1)-8,8,0,0,uFlags);

	EndDeferWindowPos(hDwp);

	return;
}

//�رշ���
LRESULT CDlgControlBar::OnCloseRoomViewItem(WPARAM wParam, LPARAM lParam)
{
	//�ͷŷ���
	IRoomViewItem * pIRoomViewItem=(IRoomViewItem *)wParam;
	if (pIRoomViewItem!=NULL) pIRoomViewItem->Release();

	return 0;
}

//�滭����
BOOL CDlgControlBar::OnEraseBkgnd(CDC * pDC)
{
	Invalidate(FALSE);
	UpdateWindow();
	return TRUE;
}

//����λ��
void CDlgControlBar::SetViewItemRect(int nXPos, int nYPos, int nWidth, int nHeight)
{
	//���ñ���
	m_rcViewItem.SetRect(nXPos,nYPos,nXPos+nWidth,nYPos+nHeight);

	//�ƶ��ؼ�
	if (m_pActiveViewItem!=NULL) 
	{
		HWND hWndActive=m_pActiveViewItem->GetWindowHandle();
		if (hWndActive!=NULL)
		{
			int nXPos=m_rcViewItem.left,nYPos=m_rcViewItem.top;
			int nWidth=m_rcViewItem.Width(),nHeight=m_rcViewItem.Height();
			::MoveWindow(hWndActive,nXPos,nYPos,nWidth,nHeight,TRUE);
		}
	}

	return;
}

//���ҷ���
CRoomViewItem * CDlgControlBar::SearchRoomViewItem(WORD wKindID, WORD wServerID)
{
	tagGameServer * pGameServer=NULL;
	for (int i=0;i<CountArray(m_pRoomViewItem);i++)
	{
		if (m_pRoomViewItem[i]==NULL) return NULL;
		pGameServer=m_pRoomViewItem[i]->GetServerInfo();
		if ((pGameServer->wKindID==wKindID)&&(pGameServer->wServerID==wServerID)) return m_pRoomViewItem[i];
	}

	return NULL;
}

//���뷿��
CRoomViewItem * CDlgControlBar::CreateRoomViewItem(CListServer * pListServer)
{
	//�ж�״̬
	tagGlobalUserData & GlobalUserData=g_GlobalUnits.GetGolbalUserData();
	if (GlobalUserData.dwUserID==0L)
	{
		ShowMessageBox(TEXT("�㻹û�е�¼�����ȵ�¼��Ϸ�㳡��"),MB_ICONQUESTION);
		return NULL;
	}

	//Ч�����
	ASSERT(pListServer!=NULL);
	CListKind * pListKind=pListServer->GetListKind();
	tagGameKind * pGameKind=pListKind->GetItemInfo();
	tagGameServer * pGameServer=pListServer->GetItemInfo();

	//�ж�����
	if (m_pRoomViewItemCreate!=NULL)
	{
		tagGameServer * pGameServerCreate=m_pRoomViewItemCreate->GetServerInfo();
		if ((pGameServer->wKindID==pGameServerCreate->wKindID)&&
			(pGameServer->wServerID==pGameServerCreate->wServerID))
			return NULL;
	}

	//Ѱ�ҷ���
	CRoomViewItem * pRoomViewItem=SearchRoomViewItem(pGameServer->wKindID,pGameServer->wServerID);
	if (pRoomViewItem!=NULL) 
	{
		ActiveRoomViewItem(pRoomViewItem);
		return pRoomViewItem;
	}

	//���뷿����Ŀ
	if (m_pRoomViewItem[CountArray(m_pRoomViewItem)-1]!=NULL)
	{
		ShowMessageBox(TEXT("�������Ϸ����̫���ˣ���رղ�����Ϸ�������ԣ�"),MB_ICONINFORMATION);
		return NULL;
	}

	//��ȡ�汾
	CWinFileInfo WinFileInfo;
	if (WinFileInfo.OpenWinFile(pGameKind->szProcessName)==false)
	{
		TCHAR szBuffer[512]=TEXT("");
		_snprintf(szBuffer,sizeof(szBuffer),TEXT("��%s����û�а�װ�������Ƿ����أ�"),pGameKind->szKindName);
		int nResult=ShowMessageBox(szBuffer,MB_ICONQUESTION|MB_YESNO|MB_DEFBUTTON1);
		if (nResult==IDYES) g_GlobalAttemper.DownLoadClient(pGameKind->szKindName,pGameKind->wKindID,true);
		return NULL;
	}

	//��ȡ�汾
	DWORD dwFileVerMS=0L,dwFileVerLS=0L;
	WinFileInfo.GetFileVersion(dwFileVerMS,dwFileVerLS);

	//�汾����
	BYTE cbFileVer1=(BYTE)(HIWORD(dwFileVerMS));
	BYTE cbFileVer2=(BYTE)(LOWORD(dwFileVerMS));
	BYTE cbFileVer3=(BYTE)(HIWORD(dwFileVerLS));
	BYTE cbFileVer4=(BYTE)(LOWORD(dwFileVerLS));
	BYTE cbListVer1=(BYTE)(LOWORD(LOWORD(pGameKind->dwMaxVersion)));
	BYTE cbListVer2=(BYTE)(HIBYTE(LOWORD(pGameKind->dwMaxVersion)));
	BYTE cbListVer3=(BYTE)(LOBYTE(HIWORD(pGameKind->dwMaxVersion)));
	BYTE cbListVer4=(BYTE)(HIBYTE(HIWORD(pGameKind->dwMaxVersion)));

	//�жϰ汾
	if ((cbFileVer1!=cbListVer1)||(cbFileVer2!=cbListVer2)||(cbFileVer3!=cbListVer3))
	{
		TCHAR szBuffer[512]=TEXT("");
		_snprintf(szBuffer,sizeof(szBuffer),TEXT("��%s���Ѿ�����Ϊ %ld.%ld.%ld.%ld �汾����İ汾���ܼ���ʹ�ã������Ƿ����أ�"),pGameKind->szKindName,
			cbListVer1,cbListVer2,cbListVer3,cbListVer4);
		int nResult=ShowMessageBox(szBuffer,MB_ICONQUESTION|MB_YESNO|MB_DEFBUTTON1);
		if (nResult==IDYES) g_GlobalAttemper.DownLoadClient(pGameKind->szKindName,pGameKind->wKindID,true);
		return NULL;
	}

	//���ݰ汾
	if (cbFileVer4!=cbListVer4)
	{
		TCHAR szBuffer[512]=TEXT("");
		_snprintf(szBuffer,sizeof(szBuffer),TEXT("��%s���Ѿ�����Ϊ %ld.%ld.%ld.%ld �汾�������Ƿ�����������"),pGameKind->szKindName,
			cbListVer1,cbListVer2,cbListVer3,cbListVer4);
		int nResult=ShowMessageBox(szBuffer,MB_ICONQUESTION|MB_YESNO|MB_DEFBUTTON1);
		if (nResult==IDYES) 
		{
			g_GlobalAttemper.DownLoadClient(pGameKind->szKindName,pGameKind->wKindID,true);
			return NULL;
		}
	}

	//��������
	try
	{
		pRoomViewItem=new CRoomViewItem;
		if (pRoomViewItem==NULL) return NULL;
		pRoomViewItem->Create(IDD_GAME_ROOM,AfxGetMainWnd());
		if (pRoomViewItem->InitRoomViewItem(pListServer)==false) throw TEXT("��Ϸ�����ʼ��ʧ�ܣ�");
	}
	catch (...) { SafeDelete(pRoomViewItem); }
	if (pRoomViewItem==NULL)
	{
		ShowMessageBox(TEXT("��Ϸ���䴴��ʧ��"),MB_ICONQUESTION);
		return NULL;
	}

	//������Ϸ
	bool bSuccess=pRoomViewItem->ConnectGameServer();
	if (bSuccess==false)
	{
		pRoomViewItem->DestroyWindow();
		SafeDelete(pRoomViewItem);
		return NULL;
	}

	//���ñ���
	m_pRoomViewItemCreate=pRoomViewItem;

	//������ʾ
	CString strBuffer;
	strBuffer.Format(TEXT("�������ӷ��䣬���Ժ�..."));
	g_GlobalAttemper.ShowStatusMessage(strBuffer,pRoomViewItem);
	
	return m_pRoomViewItemCreate;
}

//��ʾ��ҳ
void CDlgControlBar::WebBrowse(LPCTSTR lpszUrl, bool bForceBrowse)
{
	//����㳡
	ActivePlazaViewItem();

	//����ҳ
	if (m_pPlazaViewItem!=NULL) m_pPlazaViewItem->WebBrowse(lpszUrl,bForceBrowse);

	return;
}

//��ʾ��Ϣ
int CDlgControlBar::ShowMessageBox(LPCTSTR pszMessage, UINT nType)
{
	int nResult=MessageBox(pszMessage,TEXT("��Ϸ����"),nType);
	return nResult;
}

//����㳡
void CDlgControlBar::ActivePlazaViewItem()
{
	//��ȡ����
	HWND hWndActive=NULL;
	if (m_pActiveViewItem!=NULL) hWndActive=m_pActiveViewItem->GetWindowHandle();
	if (m_pPlazaViewItem->GetSafeHwnd()!=hWndActive)
	{
		m_pActiveViewItem=m_pPlazaViewItem;
		m_pPlazaViewItem->MoveWindow(&m_rcViewItem);
		m_pPlazaViewItem->ShowWindow(SW_SHOW);
		if (hWndActive!=NULL) ::ShowWindow(hWndActive,SW_HIDE);
	}

	return;
}

//�����
void CDlgControlBar::ActiveRoomViewItem(CRoomViewItem * pRoomViewItem)
{
	//Ч�����
	ASSERT(pRoomViewItem!=NULL);
	if (pRoomViewItem==NULL) return;

	//�жϴ���
	if (m_pRoomViewItemCreate==pRoomViewItem)
	{
		m_pRoomViewItemCreate=NULL;
		MoveMemory(m_pRoomViewItem+1,m_pRoomViewItem,sizeof(m_pRoomViewItem[0])*(CountArray(m_pRoomViewItem)-1));
		m_pRoomViewItem[0]=pRoomViewItem;
	}

	//�����
	HWND hWndActive=NULL;
	if (m_pActiveViewItem!=NULL) hWndActive=m_pActiveViewItem->GetWindowHandle();
	if (pRoomViewItem->GetSafeHwnd()!=hWndActive)
	{
		m_pActiveViewItem=pRoomViewItem;
		pRoomViewItem->MoveWindow(&m_rcViewItem);
		pRoomViewItem->ShowWindow(SW_SHOW);
		if (hWndActive!=NULL) ::ShowWindow(hWndActive,SW_HIDE);
	}

	//���¿���
	UpdateControlButton();

	return;
}

//�رշ���
void CDlgControlBar::CloseRoomViewItem(IRoomViewItem * pIRoomViewItem)
{
	//Ч�����
	ASSERT(pIRoomViewItem!=NULL);
	if (pIRoomViewItem==NULL) return;

	//���ñ���
	if (m_pRoomViewItemCreate!=pIRoomViewItem)
	{
		for (int i=0;i<CountArray(m_pRoomViewItem);i++)
		{
			if (m_pRoomViewItem[i]==NULL) break;
			if (m_pRoomViewItem[i]==pIRoomViewItem) 
			{
				//�ƶ�����
				if ((i+1)!=CountArray(m_pRoomViewItem))
				{
					int nMoveSize=(CountArray(m_pRoomViewItem)-i-1)*sizeof(m_pRoomViewItem[0]);
					MoveMemory(m_pRoomViewItem+i,m_pRoomViewItem+i+1,nMoveSize);
				}
				m_pRoomViewItem[CountArray(m_pRoomViewItem)-1]=NULL;

				//������ͼ
				if (m_pActiveViewItem==pIRoomViewItem)
				{
					int nActivePos=CountArray(m_pRoomViewItem);
					for (int i=CountArray(m_pRoomViewItem)-1;i>=0;i--)
					{
						if (m_pRoomViewItem[i]!=NULL)
						{
							nActivePos=i;
							break;
						}
					}
					if (nActivePos==CountArray(m_pRoomViewItem)) ActivePlazaViewItem();
					else ActiveRoomViewItem(m_pRoomViewItem[nActivePos]);
				}

				//���¿���
				UpdateControlButton();

				break;
			}
		}
	}
	else m_pRoomViewItemCreate=NULL;

	//�رշ���
	pIRoomViewItem->CloseRoomViewItem();
	PostMessage(WM_CLOSE_ROOM_VIEW_ITEM,(WPARAM)pIRoomViewItem,(LPARAM)pIRoomViewItem);

	return;
}

//�رշ���
void CDlgControlBar::CloseAllRoomViewItem()
{
	//�رշ���
	IRoomViewItem * pIRoomViewItem=NULL;
	for (int i=0;i<CountArray(m_pRoomViewItem);i++)
	{
		if (m_pRoomViewItem[i]==NULL) break;

		//�رշ���
		pIRoomViewItem=GET_OBJECTPTR_INTERFACE(m_pRoomViewItem[i],IRoomViewItem);
		pIRoomViewItem->CloseRoomViewItem();
		PostMessage(WM_CLOSE_ROOM_VIEW_ITEM,(WPARAM)pIRoomViewItem,(LPARAM)pIRoomViewItem);

		//���ñ���
		m_pRoomViewItem[i]=NULL;
	}

	//�رմ�������
	if (m_pRoomViewItemCreate!=NULL) 
	{
		//�رշ���
		g_GlobalAttemper.DestroyStatusWnd(NULL);
		m_pRoomViewItemCreate->CloseRoomViewItem();
		pIRoomViewItem=GET_OBJECTPTR_INTERFACE(m_pRoomViewItemCreate,IRoomViewItem);
		PostMessage(WM_CLOSE_ROOM_VIEW_ITEM,(WPARAM)pIRoomViewItem,(LPARAM)pIRoomViewItem);

		//���ñ���
		m_pRoomViewItemCreate=NULL;
	}

	//���¿���
	UpdateControlButton();

	return;
}

//�رյ�ǰ
void CDlgControlBar::CloseCurrentViewItem()
{
	//�����ж�
	ASSERT(m_pActiveViewItem!=NULL);
	if (m_pActiveViewItem!=m_pPlazaViewItem)
	{
		IRoomViewItem * pIRoomViewItem=GET_OBJECTPTR_INTERFACE(m_pActiveViewItem,IRoomViewItem);
		ASSERT(pIRoomViewItem!=NULL);
		CloseRoomViewItem(pIRoomViewItem);
	}
	else AfxGetMainWnd()->PostMessage(WM_CLOSE,0,0); 

	return;
}

//���¿���
void CDlgControlBar::UpdateControlButton()
{
	//���°�ť
	for (int i=0;i<CountArray(m_btViewItem);i++)
	{
		if (m_pRoomViewItem[i]!=NULL)
		{
			tagGameKind * pGameKind=m_pRoomViewItem[i]->GetKindInfo();
			m_btViewItem[i].ShowWindow(SW_SHOW);
			m_btViewItem[i].SetWindowText(pGameKind->szKindName);
		}
		else m_btViewItem[i].ShowWindow(SW_HIDE);
	}

	return;
}

//��Ϸ�㳡
void CDlgControlBar::OnBnClickedPlaza()
{
	ActivePlazaViewItem();
	return;
}

//��Ϸ����
void CDlgControlBar::OnBnClickedViewItem1()
{
	ActiveRoomViewItem(m_pRoomViewItem[0]);
	return;
}

//��Ϸ����
void CDlgControlBar::OnBnClickedViewItem2()
{
	ActiveRoomViewItem(m_pRoomViewItem[1]);
	return;
}

//��Ϸ����
void CDlgControlBar::OnBnClickedViewItem3()
{
	ActiveRoomViewItem(m_pRoomViewItem[2]);
	return;
}

//��Ϸ����
void CDlgControlBar::OnBnClickedViewItem4()
{
	ActiveRoomViewItem(m_pRoomViewItem[3]);
	return;
}

//�л���ť
void CDlgControlBar::OnBnClickedSwitchAccounts()
{
	//״̬�ж�
	tagGlobalUserData & GlobalUserData=g_GlobalUnits.GetGolbalUserData();
	if (GlobalUserData.dwUserID==0L) return;

	//�л�ѯ��
	if (m_pRoomViewItem[0]!=NULL)
	{
		const TCHAR szMessage[]=TEXT("�л��û��ʺţ�����ر�������Ϸ���䣬ȷʵҪ�л��û��ʺ��� ");
		int iResult=ShowMessageBox(szMessage,MB_ICONQUESTION|MB_YESNO|MB_DEFBUTTON2);
		if (iResult!=IDYES) return;
	}
	else
	{
		const TCHAR szMessage[]=TEXT("ȷʵҪע����ǰ�û����л��û��ʺ��� ");
		int iResult=ShowMessageBox(szMessage,MB_ICONQUESTION|MB_YESNO|MB_DEFBUTTON2);
		if (iResult!=IDYES) return;
	}

	//�رշ���
	ActivePlazaViewItem();
	CloseAllRoomViewItem();

	//���ñ���
	memset(&GlobalUserData,0,sizeof(GlobalUserData));

	//Ͷ����Ϣ
	m_pPlazaViewItem->SendLogonMessage();

	return;
}

//��ϵ��ť
void CDlgControlBar::OnBnClickedCompanion()
{
	g_GlobalUnits.m_CompanionManager->ShowCompanionManager();
	return;
}

//���ð�ť
void CDlgControlBar::OnBnClickedGlobalOption()
{
	//��ȡ����
	CGameOption * pGameOption=NULL;
	CServerOption * pServerOption=NULL;
	if (m_pActiveViewItem!=m_pPlazaViewItem)
	{
		for (int i=0;i<CountArray(m_pRoomViewItem);i++)
		{
			if (m_pRoomViewItem[i]==NULL) break;
			if (m_pActiveViewItem==m_pRoomViewItem[i])
			{
				pGameOption=m_pRoomViewItem[i]->GetGameOption();
				pServerOption=m_pRoomViewItem[i]->GetServerOption();
				break;
			}
		}
	}

	//��ʾ����
	CDlgOption DlgOption(pGameOption,pServerOption);
	INT_PTR iResult=DlgOption.DoModal();
	if (iResult==IDOK)
	{
		for (int i=0;i<CountArray(m_pRoomViewItem);i++)
		{
			if (m_pRoomViewItem[i]==NULL) break;
			m_pRoomViewItem[i]->SendUserRule();
		}
	}

	return;
}

//�˳���ť
void CDlgControlBar::OnBnClickedQuitGame()
{
	CloseCurrentViewItem();
	return;
}

//////////////////////////////////////////////////////////////////////////
