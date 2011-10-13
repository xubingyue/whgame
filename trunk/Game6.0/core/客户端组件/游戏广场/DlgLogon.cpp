#include "Stdafx.h"
#include "Resource.h"
#include "DlgLogon.h"
#include "GlobalUnits.h"
#include "DlgControlBar.h"

//登录方式
#define LOGON_BY_ACCOUNTS				0						//帐号登录
#define LOGON_BY_USERID					1						//ID 登录

//颜色定义
#define SELECT_COLOR		RGB(37,56,220)						//选择颜色

//////////////////////////////////////////////////////////////////////////

BEGIN_MESSAGE_MAP(CTabCtrlLogon, CTabCtrl)
	ON_WM_PAINT()
END_MESSAGE_MAP()

BEGIN_MESSAGE_MAP(CDlgRegister, CSkinDialogEx)
END_MESSAGE_MAP()

BEGIN_MESSAGE_MAP(CDlgLogon, CSkinDialogEx)
	ON_EN_CHANGE(IDC_PASSWORD, OnEnChangePassword)
	ON_CBN_SELCHANGE(IDC_USER_ID, OnSelchangeUserID)
	ON_CBN_SELCHANGE(IDC_ACCOUNTS, OnSelchangeAccounts)
	ON_BN_CLICKED(IDC_REGISTER, OnRegisterAccounts)
	ON_BN_CLICKED(IDC_DELETE_RECORD, OnDeleteAccounts)
END_MESSAGE_MAP()

//////////////////////////////////////////////////////////////////////////

//构造函数
CTabCtrlLogon::CTabCtrlLogon()
{
}

//析够函数
CTabCtrlLogon::~CTabCtrlLogon()
{
}

//重画消息
void CTabCtrlLogon::OnPaint()
{
	//变量定义
	CPaintDC dc(this);
	CSkinWndAttribute * pSkinAttribute=CSkinDialog::GetSkinAttribute();

	//绘画背景
	CRect ClipRect,ClientRect;
	dc.GetClipBox(&ClipRect);
	dc.FillSolidRect(&ClipRect,pSkinAttribute->m_crBackGround);

	//设置 DC
	dc.SetBkMode(TRANSPARENT);
	dc.SelectObject(pSkinAttribute->GetDefaultFont());
	
	//绘画边框
	GetClientRect(&ClientRect);
	ClientRect.top+=18;
	dc.Draw3dRect(&ClientRect,pSkinAttribute->m_crInsideBorder,pSkinAttribute->m_crInsideBorder);

	//获取信息
	TCITEM ItemInfo;
	TCHAR szBuffer[100];
	memset(&ItemInfo,0,sizeof(ItemInfo));
	ItemInfo.mask=TCIF_TEXT|TCIF_IMAGE;
	ItemInfo.pszText=szBuffer;
	ItemInfo.cchTextMax=sizeof(szBuffer);

	//绘画按钮
	CRect rcItem;
	int iCursel=GetCurSel();
	CPen LinePen(PS_SOLID,1,pSkinAttribute->m_crInsideBorder);
	CPen * pOldPen=dc.SelectObject(&LinePen);
	for (int i=0;i<GetItemCount();i++)
	{
		GetItem(i,&ItemInfo);
		GetItemRect(i,&rcItem);
		dc.FillSolidRect(&rcItem,pSkinAttribute->m_crBackGround);
		dc.MoveTo(rcItem.left,rcItem.bottom-1);
		dc.LineTo(rcItem.left,rcItem.top+2);
		dc.LineTo(rcItem.left+2,rcItem.top);
		dc.LineTo(rcItem.right-2,rcItem.top);
		dc.LineTo(rcItem.right,rcItem.top+2);
		dc.LineTo(rcItem.right,rcItem.bottom-1);
		
		if (iCursel!=i)
		{
			rcItem.top+=2;
			dc.MoveTo(rcItem.left,rcItem.bottom-1);
			dc.LineTo(rcItem.right,rcItem.bottom-1);
			dc.SetTextColor(pSkinAttribute->m_crControlTXColor);
			DrawText(dc,szBuffer,lstrlen(szBuffer),&rcItem,DT_VCENTER|DT_SINGLELINE|DT_CENTER);
		}
		else 
		{
			rcItem.top+=3;
			dc.SetTextColor(SELECT_COLOR);
			DrawText(dc,szBuffer,lstrlen(szBuffer),&rcItem,DT_VCENTER|DT_SINGLELINE|DT_CENTER);
		}
	}

	//清理资源
	dc.SelectObject(pOldPen);
	LinePen.DeleteObject();

	return;
}

//////////////////////////////////////////////////////////////////////////

//构造函数
CDlgRegister::CDlgRegister() : CSkinDialogEx(IDD_REGISTER)
{
	//登录信息
	m_wFaceID=0;
	m_cbGender=0;
	m_szSpreader[0]=0;
	m_szAccounts[0]=0;
	m_szPassword[0]=0;

	return;
}

//析构函数
CDlgRegister::~CDlgRegister()
{
}

//控件绑定
void CDlgRegister::DoDataExchange(CDataExchange * pDX)
{
	__super::DoDataExchange(pDX);
	DDX_Control(pDX, IDOK, m_btLogon);
	DDX_Control(pDX, IDCANCEL, m_btCancel);
	DDX_Control(pDX, IDC_USER_FACE, m_FaceSelect);
	DDX_Control(pDX, IDC_REG_WEB, m_LineRegWeb);
	DDX_Control(pDX, IDC_MAIN_PAGE, m_LineMainPage);
	DDX_Control(pDX, IDC_PASSWORD_PROTECT, m_LinePassWord);
}

//初始化函数
BOOL CDlgRegister::OnInitDialog()
{
	__super::OnInitDialog();

	//设置标题
	SetWindowText(TEXT("帐号注册"));

	//限制输入
	((CComboBox *)(GetDlgItem(IDC_ACCOUNTS)))->LimitText(NAME_LEN-1);
	((CEdit *)(GetDlgItem(IDC_PASSWORD)))->LimitText(PASS_LEN-1);
	((CEdit *)(GetDlgItem(IDC_PASSWORD2)))->LimitText(PASS_LEN-1);
	m_LineRegWeb.SetHyperLinkUrl(TEXT("http://www.dreamlib.com/register/"));
	m_LineMainPage.SetHyperLinkUrl(TEXT("http://www.dreamlib.com/game/"));
	m_LinePassWord.SetHyperLinkUrl(TEXT("http://www.dreamlib.com/service/"));

	//加载头像
	g_GlobalUnits.m_UserFaceRes->FillImageList(m_ImageList);
	m_FaceSelect.SetImageList(&m_ImageList);

	//插入头像
	COMBOBOXEXITEM Item;
	ZeroMemory(&Item,sizeof(Item));
	Item.mask=CBEIF_IMAGE|CBEIF_SELECTEDIMAGE;
	for (int i=g_GlobalUnits.m_UserFaceRes->GetFaceCount()-1;i>=0;i--) 
	{
		Item.lParam=i;
		Item.iImage=i;
		Item.iSelectedImage=i;
		m_FaceSelect.InsertItem(&Item);
	}

	//用户性别
	BYTE cbGender[]={GENDER_NULL,GENDER_BOY,GENDER_GIRL};
	LPCTSTR pszGender[]={TEXT("保密"),TEXT("男性"),TEXT("女性")};
	CComboBox * pComboBox=(CComboBox *)GetDlgItem(IDC_GENDER);

	//用户性别
	for (int i=0;i<CountArray(cbGender);i++)
	{
		int nItem=pComboBox->InsertString(i,pszGender[i]);
		pComboBox->SetItemData(nItem,cbGender[i]);
	}
	pComboBox->SetCurSel(0);

	//设置头像
	m_wFaceID=rand()%g_GlobalUnits.m_UserFaceRes->GetFaceCount();
	m_FaceSelect.SetCurSel(m_wFaceID);

	//获取目录
	TCHAR szPath[MAX_PATH]=TEXT("");
	GetCurrentDirectory(sizeof(szPath),szPath);

	//读取配置
	TCHAR szFileName[MAX_PATH]=TEXT("");
	_snprintf(szFileName,sizeof(szFileName),TEXT("%s\\Spreader.ini"),szPath);

	//读取推荐人
	TCHAR szSpreader[NAME_LEN]=TEXT("");
	GetPrivateProfileString(TEXT("SpreaderInfo"),TEXT("SpreaderName"),TEXT(""),szSpreader,CountArray(szSpreader),szFileName);

	//设置名字
	if (szSpreader[0]!=0)
	{
		SetDlgItemText(IDC_SPREADER,szSpreader);
		((CEdit *)GetDlgItem(IDC_SPREADER))->SetReadOnly();
	}

	return TRUE;
}

//确定函数
void CDlgRegister::OnOK()
{
	CString strBuffer;

	//用户帐号
	GetDlgItemText(IDC_ACCOUNTS,strBuffer);
	strBuffer.TrimLeft();
	strBuffer.TrimRight();
	if (strBuffer.GetLength()<5)
	{
		AfxMessageBox(TEXT("帐号名字的长度最短为 5 位字符，请重新输入注册帐号！"),MB_ICONQUESTION);
		GetDlgItem(IDC_ACCOUNTS)->SetFocus();
		return;
	}
	lstrcpyn(m_szAccounts,strBuffer,CountArray(m_szAccounts));

	//用户密码
	GetDlgItemText(IDC_PASSWORD,strBuffer);
	if (strBuffer.GetLength()<6)
	{
		AfxMessageBox(TEXT("游戏密码长度最短为 6 位字符，请重新输入游戏密码！"),MB_ICONQUESTION);
		GetDlgItem(IDC_PASSWORD)->SetFocus();
		return;
	}

	//确认密码
	GetDlgItemText(IDC_PASSWORD2,m_szPassword,CountArray(m_szPassword));
	if (lstrcmp(m_szPassword,m_szPassword)!=0)
	{
		AfxMessageBox(TEXT("游戏密码与确认密码不一致，请重新输入确认密码！"),MB_ICONQUESTION);
		GetDlgItem(IDC_PASSWORD2)->SetFocus();
		return;
	}

	//推广员名
	GetDlgItemText(IDC_SPREADER,strBuffer);
	strBuffer.TrimLeft();
	strBuffer.TrimRight();
	lstrcpyn(m_szSpreader,strBuffer,CountArray(m_szSpreader));

	//用户性别
	int nCurSel=((CComboBox *)GetDlgItem(IDC_GENDER))->GetCurSel();
	m_cbGender=(BYTE)((CComboBox *)GetDlgItem(IDC_GENDER))->GetItemData(nCurSel);

	//用户头像
	m_wFaceID=m_FaceSelect.GetCurSel();

	__super::OnOK();
}

//取消消息
void CDlgRegister::OnCancel()
{
	__super::OnCancel();
}

//////////////////////////////////////////////////////////////////////////

//构造函数
CDlgLogon::CDlgLogon() : CSkinDialogEx(IDD_LOGON)
{
	//登录信息
	m_wFaceID=0;
	m_cbGender=0;
	m_dwUserID=0;
	m_szSpreader[0]=0;
	m_szAccounts[0]=0;
	m_szPassword[0]=0;
	m_LogonMode=LogonMode_Accounts;

	//辅助信息
	m_bRegister=false;
	m_bChangePassWord=false;

	return;
}

//析构函数
CDlgLogon::~CDlgLogon()
{
}

//控件绑定
void CDlgLogon::DoDataExchange(CDataExchange * pDX)
{
	__super::DoDataExchange(pDX);
	DDX_Control(pDX, IDOK, m_btLogon);
	DDX_Control(pDX, IDCANCEL, m_btCancel);
	DDX_Control(pDX, IDC_REGISTER, m_btRegister);
	DDX_Control(pDX, IDC_DELETE_RECORD, m_btDelete);
	DDX_Control(pDX, IDC_MAIN_PAGE, m_LineMainPage);
	DDX_Control(pDX, IDC_PASSWORD_PROTECT, m_LinePassWord);
	DDX_Control(pDX, IDC_GET_PASSWORD, m_LineGetPassWord);
}

//初始化函数
BOOL CDlgLogon::OnInitDialog()
{
	__super::OnInitDialog();

	//设置标题
	SetWindowText(TEXT("游戏登录"));

	//加入标签
	//m_TabLogonMode.InsertItem(LOGON_BY_ACCOUNTS,TEXT("帐号登录"));
	//m_TabLogonMode.InsertItem(LOGON_BY_USERID,TEXT("ＩＤ登录"));

	
	//设置控件
	m_LineMainPage.SetHyperLinkUrl(TEXT("127.0.0.1"));
	m_LinePassWord.SetHyperLinkUrl(TEXT("127.0.0.1"));
	m_LineGetPassWord.SetHyperLinkUrl(TEXT("127.0.0.1"));
	m_LineMainPage.BringWindowToTop();
	m_LinePassWord.BringWindowToTop();
	m_LineGetPassWord.BringWindowToTop();

	//限制输入
	((CComboBox *)(GetDlgItem(IDC_USER_ID)))->LimitText(11);
	((CComboBox *)(GetDlgItem(IDC_ACCOUNTS)))->LimitText(NAME_LEN-1);
	((CEdit *)(GetDlgItem(IDC_PASSWORD)))->LimitText(PASS_LEN-1);

	//登录模式
	m_LogonMode=LogonMode_Accounts;
	SetLogonMode(m_LogonMode);

	//记录密码
	if (g_GlobalOption.m_enAcountsRule==enAcountsRule_AccountsAndPass)
		((CButton *)GetDlgItem(IDC_REM_PASSWORD))->SetCheck(BST_CHECKED);

	//加载信息
	LoadLogonServer();
	LoadAccountsInfo();

	//设置焦点
	UINT uControlID=IDC_ACCOUNTS;
	if (m_LogonMode==LogonMode_UserID) uControlID=IDC_USER_ID;
	if (GetDlgItem(uControlID)->GetWindowTextLength()==0)
	{
		GetDlgItem(uControlID)->SetFocus();
		((CComboBox *)GetDlgItem(uControlID))->SetEditSel(0,-1);
	}
	else 
	{
		GetDlgItem(IDC_PASSWORD)->SetFocus();
		((CEdit *)GetDlgItem(IDC_PASSWORD))->SetSel(0,-1);
	}

	//设置顶层
	::SetWindowPos(m_hWnd,HWND_TOPMOST,0,0,0,0,SWP_NOSIZE|SWP_NOMOVE);

	return FALSE;
}

//消息解释
BOOL CDlgLogon::PreTranslateMessage(MSG * pMsg)
{
	return __super::PreTranslateMessage(pMsg);
}

//确定函数
void CDlgLogon::OnOK()
{
	//效验输入
	if (CheckLogonInput(true)==false) return;

	//设置变量
	m_bRegister=false;

	//登录广场
	ShowWindow(SW_HIDE);
	IPlazaViewItem * pIPlazaViewItem=g_pControlBar->GetPlazaViewItem();
	ASSERT(pIPlazaViewItem!=NULL);
	pIPlazaViewItem->SendConnectMessage();

	return;
}

//取消消息
void CDlgLogon::OnCancel()
{
	DestroyWindow();
	AfxGetMainWnd()->PostMessage(WM_CLOSE,0,0);
	return;
}

//发送登录包
bool CDlgLogon::SendLogonPacket(IClientSocket * pIClientSocke)
{
	//变量定义
	TCHAR szPassword[33];
	BYTE cbBuffer[SOCKET_PACKAGE];
	CMD5Encrypt::EncryptData(m_szPassword,szPassword);

	//发送数据
	switch (m_LogonMode)
	{
	case LogonMode_Accounts:		//帐号登录
		{
			if (m_bRegister==false)
			{
				//构造数据
				CMD_GP_LogonByAccounts * pLogonByAccounts=(CMD_GP_LogonByAccounts *)cbBuffer;
				memset(pLogonByAccounts,0,sizeof(CMD_GP_LogonByAccounts));
				pLogonByAccounts->dwPlazaVersion=g_GlobalUnits.GetPlazaVersion();
				CopyMemory(pLogonByAccounts->szPassWord,szPassword,sizeof(pLogonByAccounts->szPassWord));
				lstrcpyn(pLogonByAccounts->szAccounts,m_szAccounts,CountArray(pLogonByAccounts->szAccounts));

				//机器序列号
				tagClientSerial ClientSerial;
				g_GlobalUnits.GetClientSerial(ClientSerial);

				//发送数据包
				CSendPacketHelper Packet(cbBuffer+sizeof(CMD_GP_LogonByAccounts),sizeof(cbBuffer)-sizeof(CMD_GP_LogonByAccounts));
				Packet.AddPacket(&ClientSerial,sizeof(ClientSerial),DTP_COMPUTER_ID);
				pIClientSocke->SendData(MDM_GP_LOGON,SUB_GP_LOGON_ACCOUNTS,cbBuffer,sizeof(CMD_GP_LogonByAccounts)+Packet.GetDataSize());
			}
			else
			{
				//构造数据
				CMD_GP_RegisterAccounts * pRegisterAccounts=(CMD_GP_RegisterAccounts *)cbBuffer;
				memset(pRegisterAccounts,0,sizeof(CMD_GP_RegisterAccounts));
				pRegisterAccounts->wFaceID=m_wFaceID;
				pRegisterAccounts->cbGender=m_cbGender;
				pRegisterAccounts->dwPlazaVersion=g_GlobalUnits.GetPlazaVersion();
				lstrcpyn(pRegisterAccounts->szPassWord,szPassword,CountArray(pRegisterAccounts->szPassWord));
				lstrcpyn(pRegisterAccounts->szSpreader,m_szSpreader,CountArray(pRegisterAccounts->szSpreader));
				lstrcpyn(pRegisterAccounts->szAccounts,m_szAccounts,CountArray(pRegisterAccounts->szAccounts));

				//机器序列号
				tagClientSerial ClientSerial;
				g_GlobalUnits.GetClientSerial(ClientSerial);

				//发送数据包
				CSendPacketHelper Packet(cbBuffer+sizeof(CMD_GP_RegisterAccounts),sizeof(cbBuffer)-sizeof(CMD_GP_RegisterAccounts));
				Packet.AddPacket(&ClientSerial,sizeof(ClientSerial),DTP_COMPUTER_ID);
				pIClientSocke->SendData(MDM_GP_LOGON,SUB_GP_REGISTER_ACCOUNTS,cbBuffer,sizeof(CMD_GP_RegisterAccounts)+Packet.GetDataSize());
			}

			break;
		}
	case LogonMode_UserID:			//I D 登录
		{
			//构造数据
			CMD_GP_LogonByUserID * pLogonByUserID=(CMD_GP_LogonByUserID *)cbBuffer;
			memset(pLogonByUserID,0,sizeof(CMD_GP_LogonByUserID));
			pLogonByUserID->dwUserID=m_dwUserID;
			pLogonByUserID->dwPlazaVersion=g_GlobalUnits.GetPlazaVersion();
			CopyMemory(pLogonByUserID->szPassWord,szPassword,sizeof(pLogonByUserID->szPassWord));
			
			//机器序列号
			tagClientSerial ClientSerial;
			g_GlobalUnits.GetClientSerial(ClientSerial);

			//发送数据包
			CSendPacketHelper Packet(cbBuffer+sizeof(CMD_GP_LogonByUserID),sizeof(cbBuffer)-sizeof(CMD_GP_LogonByUserID));
			Packet.AddPacket(&ClientSerial,sizeof(ClientSerial),DTP_COMPUTER_ID);
			pIClientSocke->SendData(MDM_GP_LOGON,SUB_GP_LOGON_USERID,cbBuffer,sizeof(CMD_GP_LogonByUserID)+Packet.GetDataSize());

			break;
		}
	}

	return true;
}

//登录成功处理
bool CDlgLogon::OnLogonSuccess()
{
	//登录配置
	BOOL bRemPassword=(((CButton *)GetDlgItem(IDC_REM_PASSWORD))->GetCheck()==BST_CHECKED);
	AfxGetApp()->WriteProfileInt(REG_OPTION_LOGON,TEXT("LogonMode"),m_LogonMode);
	AfxGetApp()->WriteProfileString(REG_OPTION_LOGON,TEXT("LogonServer"),m_strLogonServer);

	//配置信息
	if (bRemPassword) g_GlobalOption.m_enAcountsRule=enAcountsRule_AccountsAndPass;

	//用户信息
	tagGlobalUserData & UserData=g_GlobalUnits.GetGolbalUserData();
	AfxGetApp()->WriteProfileInt(REG_OPTION_LOGON,TEXT("LastUserID"),UserData.dwUserID);

	//写入用户记录
	if (g_GlobalOption.m_enAcountsRule!=enAcountsRule_None)
	{
		//构造信息
		TCHAR szBuffer[256];
		_snprintf(szBuffer,sizeof(szBuffer),TEXT("%s\\%ld"),REG_USER_INFO,UserData.dwUserID);

		//写入信息
		CRegKey RegUserInfo;
		if (RegUserInfo.Create(HKEY_CURRENT_USER,szBuffer)==ERROR_SUCCESS)
		{
			TCHAR szPassBuffer[256]=TEXT("");
			if (bRemPassword) CXOREncrypt::EncryptData(m_szPassword,szPassBuffer,CountArray(szPassBuffer));
			RegUserInfo.SetKeyValue(TEXT(""),UserData.szAccounts,TEXT("UserAccount"));
			RegUserInfo.SetKeyValue(TEXT(""),UserData.szPassWord,TEXT("UserPassToken"));
			RegUserInfo.SetKeyValue(TEXT(""),szPassBuffer,TEXT("UserPassword"));
			if (UserData.dwGameID!=0L) RegUserInfo.SetDWORDValue(TEXT("GameID"),UserData.dwGameID);
		}
	}
	else
	{
		//构造信息
		TCHAR szBuffer[256];
		_snprintf(szBuffer,sizeof(szBuffer),TEXT("%ld"),UserData.dwUserID);

		//写入信息
		CRegKey RegUserID;
		if (RegUserID.Open(HKEY_CURRENT_USER,REG_USER_INFO)==ERROR_SUCCESS)	RegUserID.RecurseDeleteKey(szBuffer);
	}

	//关闭窗口
	DestroyWindow();

	

	return true;
}

//读取帐号
void CDlgLogon::LoadAccountsInfo()
{
	//变量定义
	CComboBox * pComBoxAccounts=(CComboBox *)GetDlgItem(IDC_ACCOUNTS);
	CComboBox * pComBoxUserID=(CComboBox *)GetDlgItem(IDC_USER_ID);

	//读取信息
	CRegKey RegUserInfo;
	RegUserInfo.Open(HKEY_CURRENT_USER,REG_USER_INFO,KEY_READ);
	if (RegUserInfo!=NULL)
	{
		int iInsertItem=CB_ERR;
		LONG lErrorCode=ERROR_SUCCESS;
		DWORD dwType=REG_SZ,dwIndex=0,dwUserDBID=0;
		TCHAR szUserIDBuffer[32]=TEXT(""),szTempBuffer[256]=TEXT("");
		do
		{
			//设置变量
			dwUserDBID=0;
			szTempBuffer[0]=0;
			szUserIDBuffer[0]=0;

			//读取游戏 ID
			DWORD dwBufferSize=sizeof(szUserIDBuffer);
			if (RegUserInfo.EnumKey(dwIndex++,szUserIDBuffer,&dwBufferSize,NULL)!=ERROR_SUCCESS) break;
			dwUserDBID=atol(szUserIDBuffer);
			if (dwUserDBID==0) continue;

			//加载其他信息
			CRegKey RegUserAccount;
			_snprintf(szTempBuffer,sizeof(szTempBuffer),TEXT("%s\\%ld"),REG_USER_INFO,dwUserDBID);
			RegUserAccount.Open(HKEY_CURRENT_USER,szTempBuffer,KEY_READ);
			if (RegUserAccount!=NULL)
			{
				//游戏帐号
				dwBufferSize=sizeof(szTempBuffer);
				lErrorCode=RegUserAccount.QueryValue(TEXT("UserAccount"),&dwType,szTempBuffer,&dwBufferSize);
				if ((lErrorCode==ERROR_SUCCESS)&&(szTempBuffer[0]!=0)&&(ComboBoxFindString(pComBoxAccounts,szTempBuffer)==LB_ERR))
				{
					iInsertItem=pComBoxAccounts->AddString(szTempBuffer);
					pComBoxAccounts->SetItemData(iInsertItem,dwUserDBID);
				}

				//游戏 ID
				DWORD dwGameID=0L;
				dwBufferSize=sizeof(dwGameID);
				if ((RegUserAccount.QueryValue(TEXT("GameID"),&dwType,&dwGameID,&dwBufferSize)==ERROR_SUCCESS)&&(dwGameID!=0L))
				{
					_sntprintf(szTempBuffer,CountArray(szTempBuffer),TEXT("%ld"),dwGameID);
					iInsertItem=pComBoxUserID->AddString(szTempBuffer);
					pComBoxUserID->SetItemData(iInsertItem,dwUserDBID);
				}
			}
		} while (true);
	}

	//最近用户
	DWORD dwLastUserID=AfxGetApp()->GetProfileInt(REG_OPTION_LOGON,TEXT("LastUserID"),0L);
	if (dwLastUserID!=0L)
	{
		for (int i=0;i<pComBoxUserID->GetCount();i++)
		{
			DWORD dwComboBoxID=(DWORD)pComBoxUserID->GetItemData(i);
			if ((dwComboBoxID!=0L)&&(dwComboBoxID==dwLastUserID))
			{
				pComBoxUserID->SetCurSel(i);
				UpdateUserComboBox(IDC_USER_ID);
				break;
			}
		}
	}

	//设置选择
	if ((pComBoxUserID->GetCurSel()==LB_ERR)&&(pComBoxUserID->GetCount()>0))
	{
		pComBoxUserID->SetCurSel(0);
		UpdateUserComboBox(IDC_USER_ID);
	}

	//设置选择
	if ((pComBoxAccounts->GetCurSel()==LB_ERR)&&(pComBoxAccounts->GetCount()>0))
	{
		pComBoxAccounts->SetCurSel(0);
		UpdateUserComboBox(IDC_ACCOUNTS);
	}

	return;
}

//加载服务器
void CDlgLogon::LoadLogonServer()
{
	//读取最近登录服务器
	CComboBox * pComBoxServer=(CComboBox *)GetDlgItem(IDC_SERVER);
	m_strLogonServer=AfxGetApp()->GetProfileString(REG_OPTION_LOGON,TEXT("LogonServer"),NULL);
	if (m_strLogonServer.IsEmpty()==FALSE)
	{
		pComBoxServer->AddString(m_strLogonServer);
		pComBoxServer->SetWindowText(m_strLogonServer);
	}

	//读取服务器列表
	CRegKey RegLogonServer;
	RegLogonServer.Open(HKEY_CURRENT_USER,REG_LOGON_SERVER,KEY_READ);
	if (RegLogonServer!=NULL)
	{
		TCHAR szLogonServer[128]=TEXT("");
		DWORD dwIndex=0,dwBufferSize=sizeof(szLogonServer);
		do
		{
			dwBufferSize=sizeof(szLogonServer);
			if (RegLogonServer.EnumKey(dwIndex++,szLogonServer,&dwBufferSize,NULL)!=ERROR_SUCCESS) break;
			if (szLogonServer[0]!=0)
			{
				if (m_strLogonServer.IsEmpty()) m_strLogonServer=szLogonServer;
				if (ComboBoxFindString(pComBoxServer,szLogonServer)==LB_ERR) pComBoxServer->AddString(szLogonServer);
			}
		} while (true);
	}

	//设置选择
	if ((pComBoxServer->GetWindowTextLength()==0)&&(pComBoxServer->GetCount()>0)) pComBoxServer->SetCurSel(0);
	if (pComBoxServer->GetCount()==0)
	{
		pComBoxServer->AddString(TEXT("127.0.0.1"));
		pComBoxServer->SetCurSel(0);
	}

	return;
}

//查找数据
int CDlgLogon::ComboBoxFindString(CComboBox * pComboBox, LPCTSTR pszFindString)
{
	CString strBuffer;
	int iItemHandle=LB_ERR,iItemFind=LB_ERR;
	int nStringLen=lstrlen(pszFindString);
	do 
	{
		iItemFind=pComboBox->FindString((iItemHandle==LB_ERR)?0:(iItemHandle+1),pszFindString);
		if ((iItemFind==LB_ERR)||(iItemHandle==iItemFind)||(iItemFind<iItemHandle)) return LB_ERR;
		iItemHandle=iItemFind;
		pComboBox->GetLBText(iItemHandle,strBuffer);
		if (pComboBox->GetLBTextLen(iItemHandle)==nStringLen) return iItemHandle;
	} while (true);
	return LB_ERR;
}

//效验输入
bool CDlgLogon::CheckLogonInput(bool bShowError)
{
	//定义变量
	UINT uControlID=0;
	CString strBuffer;

	try
	{
		//登录服务器
		GetDlgItemText(IDC_SERVER,m_strLogonServer);
		m_strLogonServer.TrimLeft();
		m_strLogonServer.TrimRight();
		if (m_strLogonServer.IsEmpty())
		{
			uControlID=IDC_SERVER;
			throw TEXT("登录服务器不能为空，请重新选择或者输入登录服务器！");
		}

		//登录帐号
		switch (m_LogonMode)
		{
		case LogonMode_Accounts:		//帐号登录
			{
				GetDlgItemText(IDC_ACCOUNTS,strBuffer);
				strBuffer.TrimLeft();
				strBuffer.TrimRight();
				if (strBuffer.IsEmpty())
				{
					uControlID=IDC_ACCOUNTS;
					throw TEXT("用户登录帐号不能为空，请重新输入登录帐号！");
				}
				lstrcpyn(m_szAccounts,strBuffer,CountArray(m_szAccounts));
				break;
			}
		case LogonMode_UserID:			//ID 登录
			{
				GetDlgItemText(IDC_USER_ID,strBuffer);
				strBuffer.TrimLeft();
				strBuffer.TrimRight();
				m_dwUserID=atoi(strBuffer);
				if (m_dwUserID==0L)
				{
					uControlID=IDC_USER_ID;
					throw TEXT("用户登录 ID 不能为空，请重新输入登录 ID ！");
				}
				break;
			}
		}

		//用户密码
		if (m_bChangePassWord==true)
		{
			m_bChangePassWord=false;
			GetDlgItemText(IDC_PASSWORD,m_szPassword,CountArray(m_szPassword));
		}
		if (m_szPassword[0]==0)
		{
			uControlID=IDC_PASSWORD;
			throw TEXT("登录密码不能为空，请重新输入登录密码！");
		}

		return true;
	}
	catch (LPCTSTR pszError)
	{
		if (bShowError)
		{
			ShowWindow(SW_SHOW);
			BringWindowToTop();
			AfxMessageBox(pszError,MB_ICONQUESTION);
			if (uControlID!=0) GetDlgItem(uControlID)->SetFocus();
		}

	}
	return false;
}

//更新选择
void CDlgLogon::UpdateUserComboBox(UINT uComboBoxID)
{
	//获取 ID
	CComboBox * pComboBox=(CComboBox *)GetDlgItem(uComboBoxID);
	DWORD dwUserDBID=(DWORD)pComboBox->GetItemData(pComboBox->GetCurSel());

	//更新信息
	UpdateUserPassWord(dwUserDBID);
	UINT uComboBoxIDs[]={IDC_ACCOUNTS,IDC_USER_ID};
	for (int i=0;i<CountArray(uComboBoxIDs);i++)
	{
		pComboBox=(CComboBox *)GetDlgItem(uComboBoxIDs[i]);
		for (int j=0;j<pComboBox->GetCount();j++)
		{
			DWORD dwComboBoxID=(DWORD)pComboBox->GetItemData(j);
			if ((dwComboBoxID!=0L)&&(dwComboBoxID==dwUserDBID))
			{
				pComboBox->SetCurSel(j);
				break;
			}
		}
	}

	return;
}

//更新密码
void CDlgLogon::UpdateUserPassWord(DWORD dwUserDBID)
{
	if (dwUserDBID!=0L)
	{
		//注册表字符
		CString strRegKey;
		strRegKey.Format(TEXT("%s\\%ld"),REG_USER_INFO,dwUserDBID);

		//打开注册表
		CRegKey RegPassWord;
		RegPassWord.Open(HKEY_CURRENT_USER,strRegKey,KEY_READ);
		if (RegPassWord!=NULL)
		{
			DWORD dwType=REG_SZ;
			TCHAR szPassBuffer[256]=TEXT("");
			DWORD dwBufferLength=sizeof(szPassBuffer);
			if (RegPassWord.QueryValue(TEXT("UserPassword"),&dwType,szPassBuffer,&dwBufferLength)==ERROR_SUCCESS)
			{
				m_szPassword[0]=0;
				CXOREncrypt::CrevasseData(szPassBuffer,m_szPassword,CountArray(m_szPassword));
				if (m_szPassword[0]==0) SetDlgItemText(IDC_PASSWORD,TEXT(""));
				else SetDlgItemText(IDC_PASSWORD,TEXT("**********"));
				m_bChangePassWord=false;
				return;
			}
		}
	}

	//设置信息
	m_szPassword[0]=0;
	SetDlgItemText(IDC_PASSWORD,TEXT(""));
	m_bChangePassWord=false;
	
	return;
}

//设置模式
void CDlgLogon::SetLogonMode(enLogonMode LogonMode)
{
	m_LogonMode=LogonMode;
	switch (m_LogonMode)
	{
	case LogonMode_Accounts:	//帐号登录
		{
			SetDlgItemText(IDC_TYPE_NAME,TEXT("游戏帐号："));
			GetDlgItem(IDC_ACCOUNTS)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_USER_ID)->ShowWindow(SW_HIDE);
			break;
		}
	case LogonMode_UserID:		//I D 登录
		{
			SetDlgItemText(IDC_TYPE_NAME,TEXT("游戏 I D："));
			GetDlgItem(IDC_ACCOUNTS)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_USER_ID)->ShowWindow(SW_SHOW);
			break;
		}
	}
	return;
}

//密码改变
void CDlgLogon::OnEnChangePassword()
{
	m_bChangePassWord=true;
}

//选择改变
void CDlgLogon::OnSelchangeAccounts()
{
	UpdateUserComboBox(IDC_ACCOUNTS);
	return;
}

//选择改变
void CDlgLogon::OnSelchangeUserID()
{
	UpdateUserComboBox(IDC_USER_ID);
	return;
}



//注册帐号
void CDlgLogon::OnRegisterAccounts()
{
	CDlgRegister DlgRegister;
	ShowWindow(SW_HIDE);
	if (DlgRegister.DoModal()!=IDOK) 
	{
		ShowWindow(SW_SHOW);
		return;
	}

	//设置变量
	m_bRegister=true;
	m_wFaceID=DlgRegister.m_wFaceID;
	m_cbGender=DlgRegister.m_cbGender;
	lstrcpy(m_szSpreader,DlgRegister.m_szSpreader);
	lstrcpy(m_szAccounts,DlgRegister.m_szAccounts);
	lstrcpy(m_szPassword,DlgRegister.m_szPassword);

	//服务器
	GetDlgItemText(IDC_SERVER,m_strLogonServer);
	if (m_strLogonServer.IsEmpty()) m_strLogonServer=TEXT("127.0.0.1");

	//登录广场
	ShowWindow(SW_HIDE);
	IPlazaViewItem * pIPlazaViewItem=g_pControlBar->GetPlazaViewItem();
	ASSERT(pIPlazaViewItem!=NULL);
	pIPlazaViewItem->SendConnectMessage();

	return;
}

//删除用户
void CDlgLogon::OnDeleteAccounts() 
{
	//获取窗口
	UINT uComboBoxID=0;
	switch (m_LogonMode)
	{
	case LogonMode_Accounts: { uComboBoxID=IDC_ACCOUNTS; break;	}
	case LogonMode_UserID: { uComboBoxID=IDC_USER_ID; break; }
	default: ASSERT(FALSE);
	}
	CComboBox * pComboBox=(CComboBox *)GetDlgItem(uComboBoxID);

	//删除信息
	CString strBuffer;
	pComboBox->GetWindowText(strBuffer);
	pComboBox->SetWindowText(TEXT(""));
	if (strBuffer.IsEmpty()) return;
	int iSelectItem=ComboBoxFindString(pComboBox,strBuffer);
	if (iSelectItem!=LB_ERR)
	{
		CRegKey RegUserID;
		CString strUserID;
		DWORD dwUserDBID=(DWORD)pComboBox->GetItemData(iSelectItem);
		strUserID.Format(TEXT("%ld"),dwUserDBID);
		RegUserID.Open(HKEY_CURRENT_USER,REG_USER_INFO);
		if (RegUserID!=NULL) RegUserID.RecurseDeleteKey(strUserID);

		//删除选择信息
		CComboBox * pOtherComboBox=NULL;
		UINT uComboBoxIDs[]={IDC_ACCOUNTS,IDC_USER_ID};
		for (int i=0;i<CountArray(uComboBoxIDs);i++)
		{
			pOtherComboBox=(CComboBox *)GetDlgItem(uComboBoxIDs[i]);
			for (int j=0;j<pOtherComboBox->GetCount();j++)
			{
				DWORD dwUserIDRead=(DWORD)pOtherComboBox->GetItemData(j);
				if (dwUserIDRead==dwUserDBID)
				{
					if (pOtherComboBox->GetCurSel()==j) pOtherComboBox->SetWindowText(TEXT(""));
					pOtherComboBox->DeleteString(j);
					break;
				}
			}
		}
	}

	//更新选择
	pComboBox->SetFocus();
	if (pComboBox->GetCount()>0)
	{
		pComboBox->SetCurSel(0);
		DWORD dwUserDBID=(DWORD)pComboBox->GetItemData(0);
		UpdateUserPassWord(dwUserDBID);
		UpdateUserComboBox(uComboBoxID);
	}
	else UpdateUserPassWord(0L);

	return;
}

//////////////////////////////////////////////////////////////////////////
