#include "Stdafx.h"
#include "Resource.h"
#include "Expression.h"

//ͼ���С
#define PIC_SPACE					6
#define EP_PIC_WHIDE				20								
#define EP_PIC_HIGHT				20		

//��ɫ����
#define COLOR_BORAD					RGB(0,75,151)						//�߿���ɫ
#define COLOR_FRAME					RGB(0,75,151)						//�߿���ɫ
#define COLOR_CHAR_BK				RGB(230,249,255)					//���챳��
#define COLOR_BACK_GROUND			RGB(250,250,250)					//������ɫ

WORD					CExpression::m_wMaxRow=10;							//�������Ŀ
WORD					CExpression::m_wMaxLine=7;							//�������Ŀ
CExpressionItem			CExpression::m_ExpreesionItem[MAX_EXPRESS_ITEM];	//��������

BEGIN_MESSAGE_MAP(CExpression, CDialog)
	ON_WM_PAINT()
	ON_WM_KILLFOCUS()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()

//////////////////////////////////////////////////////////////////////////

//���캯��
CExpressionItem::CExpressionItem() 
{ 
	m_wTranceLength=0;
	m_szTrancelate[0]=0;
	m_szChineseName[0]=0;
};

//��������
CExpressionItem::~CExpressionItem() 
{
}

//�������
void CExpressionItem::InitExpressItem(LPCTSTR pszChineseName, LPCTSTR pszTrancelate, UINT uIDResource)
{
	//���ñ���
	m_uImageID=uIDResource;
	lstrcpyn(m_szTrancelate,pszTrancelate,CountArray(m_szTrancelate));
	lstrcpyn(m_szChineseName,pszChineseName,CountArray(m_szChineseName));
	m_wTranceLength=lstrlen(m_szTrancelate);

	//����ͼƬ
	CSkinImage ImageFile;
	ImageFile.LoadFromResource(GetModuleHandle(CLIENT_SHARE_DLL_NAME),uIDResource);

	//��������
	CImage ImageExpression;
	ASSERT(ImageFile.GetWidth()==EP_PIC_WHIDE);
	ASSERT(ImageFile.GetHeight()==EP_PIC_HIGHT);
	ImageExpression.Create(EP_PIC_WHIDE,EP_PIC_HIGHT,32);

	//�滭����
	CDC * pDC=CDC::FromHandle(ImageExpression.GetDC());
	pDC->FillSolidRect(0,0,EP_PIC_WHIDE,EP_PIC_HIGHT,COLOR_CHAR_BK);
	ImageFile.AlphaDrawImage(pDC,0,0,RGB(255,0,255));

	//����ͼƬ
	ImageExpression.ReleaseDC();
	m_ImageDataObject.SetImage(ImageExpression.Detach());

	return;
};

//////////////////////////////////////////////////////////////////////////

//���캯��
CExpression::CExpression() : CDialog(IDD_EXPRESSION)
{
	m_pParentWnd=NULL;
	m_wSelectIndex=MAX_EXPRESS_ITEM;
	InitExpressItem();
}

//��������
CExpression::~CExpression()
{
}

//��ʼ����Դ
bool CExpression::InitExpressItem()
{
	static bool bInit=false;
	if (bInit==false)
	{
		//������Դ
		AfxSetResourceHandle(GetModuleHandle(CLIENT_SHARE_DLL_NAME));

		//������Ϣ
		m_ExpreesionItem[0].InitExpressItem(TEXT(""),TEXT("/:01"),IDB_EP_001);
		m_ExpreesionItem[1].InitExpressItem(TEXT(""),TEXT("/:02"),IDB_EP_002);
		m_ExpreesionItem[2].InitExpressItem(TEXT(""),TEXT("/:03"),IDB_EP_003);
		m_ExpreesionItem[3].InitExpressItem(TEXT(""),TEXT("/:04"),IDB_EP_004);
		m_ExpreesionItem[4].InitExpressItem(TEXT(""),TEXT("/:05"),IDB_EP_005);
		m_ExpreesionItem[5].InitExpressItem(TEXT(""),TEXT("/:06"),IDB_EP_006);
		m_ExpreesionItem[6].InitExpressItem(TEXT(""),TEXT("/:07"),IDB_EP_007);
		m_ExpreesionItem[7].InitExpressItem(TEXT(""),TEXT("/:08"),IDB_EP_008);
		m_ExpreesionItem[8].InitExpressItem(TEXT(""),TEXT("/:09"),IDB_EP_009);
		m_ExpreesionItem[9].InitExpressItem(TEXT(""),TEXT("/:10"),IDB_EP_010);

		m_ExpreesionItem[10].InitExpressItem(TEXT(""),TEXT("/:11"),IDB_EP_011);
		m_ExpreesionItem[11].InitExpressItem(TEXT(""),TEXT("/:12"),IDB_EP_012);
		m_ExpreesionItem[12].InitExpressItem(TEXT(""),TEXT("/:13"),IDB_EP_013);
		m_ExpreesionItem[13].InitExpressItem(TEXT(""),TEXT("/:14"),IDB_EP_014);
		m_ExpreesionItem[14].InitExpressItem(TEXT(""),TEXT("/:15"),IDB_EP_015);
		m_ExpreesionItem[15].InitExpressItem(TEXT(""),TEXT("/:16"),IDB_EP_016);
		m_ExpreesionItem[16].InitExpressItem(TEXT(""),TEXT("/:17"),IDB_EP_017);
		m_ExpreesionItem[17].InitExpressItem(TEXT(""),TEXT("/:18"),IDB_EP_018);
		m_ExpreesionItem[18].InitExpressItem(TEXT(""),TEXT("/:19"),IDB_EP_019);
		m_ExpreesionItem[19].InitExpressItem(TEXT(""),TEXT("/:20"),IDB_EP_020);

		m_ExpreesionItem[20].InitExpressItem(TEXT(""),TEXT("/:21"),IDB_EP_021);
		m_ExpreesionItem[21].InitExpressItem(TEXT(""),TEXT("/:22"),IDB_EP_022);
		m_ExpreesionItem[22].InitExpressItem(TEXT(""),TEXT("/:23"),IDB_EP_023);
		m_ExpreesionItem[23].InitExpressItem(TEXT(""),TEXT("/:24"),IDB_EP_024);
		m_ExpreesionItem[24].InitExpressItem(TEXT(""),TEXT("/:25"),IDB_EP_025);
		m_ExpreesionItem[25].InitExpressItem(TEXT(""),TEXT("/:26"),IDB_EP_026);
		m_ExpreesionItem[26].InitExpressItem(TEXT(""),TEXT("/:27"),IDB_EP_027);
		m_ExpreesionItem[27].InitExpressItem(TEXT(""),TEXT("/:28"),IDB_EP_028);
		m_ExpreesionItem[28].InitExpressItem(TEXT(""),TEXT("/:29"),IDB_EP_029);
		m_ExpreesionItem[29].InitExpressItem(TEXT(""),TEXT("/:30"),IDB_EP_030);

		m_ExpreesionItem[30].InitExpressItem(TEXT(""),TEXT("/:31"),IDB_EP_031);
		m_ExpreesionItem[31].InitExpressItem(TEXT(""),TEXT("/:32"),IDB_EP_032);
		m_ExpreesionItem[32].InitExpressItem(TEXT(""),TEXT("/:33"),IDB_EP_033);
		m_ExpreesionItem[33].InitExpressItem(TEXT(""),TEXT("/:34"),IDB_EP_034);
		m_ExpreesionItem[34].InitExpressItem(TEXT(""),TEXT("/:35"),IDB_EP_035);
		m_ExpreesionItem[35].InitExpressItem(TEXT(""),TEXT("/:36"),IDB_EP_036);
		m_ExpreesionItem[36].InitExpressItem(TEXT(""),TEXT("/:37"),IDB_EP_037);
		m_ExpreesionItem[37].InitExpressItem(TEXT(""),TEXT("/:38"),IDB_EP_038);
		m_ExpreesionItem[38].InitExpressItem(TEXT(""),TEXT("/:39"),IDB_EP_039);
		m_ExpreesionItem[39].InitExpressItem(TEXT(""),TEXT("/:40"),IDB_EP_040);

		m_ExpreesionItem[40].InitExpressItem(TEXT(""),TEXT("/:41"),IDB_EP_041);
		m_ExpreesionItem[41].InitExpressItem(TEXT(""),TEXT("/:42"),IDB_EP_042);
		m_ExpreesionItem[42].InitExpressItem(TEXT(""),TEXT("/:43"),IDB_EP_043);
		m_ExpreesionItem[43].InitExpressItem(TEXT(""),TEXT("/:44"),IDB_EP_044);
		m_ExpreesionItem[44].InitExpressItem(TEXT(""),TEXT("/:45"),IDB_EP_045);
		m_ExpreesionItem[45].InitExpressItem(TEXT(""),TEXT("/:46"),IDB_EP_046);
		m_ExpreesionItem[46].InitExpressItem(TEXT(""),TEXT("/:47"),IDB_EP_047);
		m_ExpreesionItem[47].InitExpressItem(TEXT(""),TEXT("/:48"),IDB_EP_048);
		m_ExpreesionItem[48].InitExpressItem(TEXT(""),TEXT("/:49"),IDB_EP_049);
		m_ExpreesionItem[49].InitExpressItem(TEXT(""),TEXT("/:50"),IDB_EP_050);

		m_ExpreesionItem[50].InitExpressItem(TEXT(""),TEXT("/:51"),IDB_EP_051);
		m_ExpreesionItem[51].InitExpressItem(TEXT(""),TEXT("/:52"),IDB_EP_052);
		m_ExpreesionItem[52].InitExpressItem(TEXT(""),TEXT("/:53"),IDB_EP_053);
		m_ExpreesionItem[53].InitExpressItem(TEXT(""),TEXT("/:54"),IDB_EP_054);
		m_ExpreesionItem[54].InitExpressItem(TEXT(""),TEXT("/:55"),IDB_EP_055);
		m_ExpreesionItem[55].InitExpressItem(TEXT(""),TEXT("/:56"),IDB_EP_056);
		m_ExpreesionItem[56].InitExpressItem(TEXT(""),TEXT("/:57"),IDB_EP_057);
		m_ExpreesionItem[57].InitExpressItem(TEXT(""),TEXT("/:58"),IDB_EP_058);
		m_ExpreesionItem[58].InitExpressItem(TEXT(""),TEXT("/:59"),IDB_EP_059);
		m_ExpreesionItem[59].InitExpressItem(TEXT(""),TEXT("/:60"),IDB_EP_060);

		m_ExpreesionItem[60].InitExpressItem(TEXT(""),TEXT("/:61"),IDB_EP_061);
		m_ExpreesionItem[61].InitExpressItem(TEXT(""),TEXT("/:62"),IDB_EP_062);
		m_ExpreesionItem[62].InitExpressItem(TEXT(""),TEXT("/:63"),IDB_EP_063);
		m_ExpreesionItem[63].InitExpressItem(TEXT(""),TEXT("/:64"),IDB_EP_064);
		m_ExpreesionItem[64].InitExpressItem(TEXT(""),TEXT("/:65"),IDB_EP_065);
		m_ExpreesionItem[65].InitExpressItem(TEXT(""),TEXT("/:66"),IDB_EP_066);
		m_ExpreesionItem[66].InitExpressItem(TEXT(""),TEXT("/:67"),IDB_EP_067);
		m_ExpreesionItem[67].InitExpressItem(TEXT(""),TEXT("/:68"),IDB_EP_068);
		m_ExpreesionItem[68].InitExpressItem(TEXT(""),TEXT("/:69"),IDB_EP_069);
		m_ExpreesionItem[69].InitExpressItem(TEXT(""),TEXT("/:70"),IDB_EP_070);

		//������Դ
		AfxSetResourceHandle(GetModuleHandle(NULL));

		bInit=true;
	}
	return bInit;
}

//��������
bool CExpression::CreateExpression(CWnd * pParentWnd)
{
	//���ñ���
	m_pParentWnd=pParentWnd;

	//��������
	AfxSetResourceHandle(GetModuleHandle(CLIENT_SHARE_DLL_NAME));
	Create(IDD_EXPRESSION,pParentWnd);
	AfxSetResourceHandle(GetModuleHandle(NULL));

	//���ô���
	SetClassLong(m_hWnd,GCL_HBRBACKGROUND,NULL);
	BringWindowToTop();

	return true;
}

//��ȡ�ʺϴ�С
bool CExpression::GetFixSize(CSize & Size)
{
	Size.cx=m_wMaxRow*(EP_PIC_WHIDE+PIC_SPACE)+PIC_SPACE;
	Size.cy=m_wMaxLine*(EP_PIC_HIGHT+PIC_SPACE)+PIC_SPACE;
	return true;
}

//��ȡ����
CExpressionItem * CExpression::GetExpressItem(WORD wIndex)
{
	if (wIndex<MAX_EXPRESS_ITEM) return &m_ExpreesionItem[wIndex];
	return NULL;
}

//ʧȥ������Ϣ
void CExpression::OnKillFocus(CWnd * pNewWnd)
{
	__super::OnKillFocus(pNewWnd);
	DestroyWindow();
}

//�滭ͷ��
void CExpression::DrawItem(CDC * pDC, int iXPos, int iYPos, bool bSelectec)
{
	CExpressionItem * pExpressionItem=GetExpressItem(iYPos*m_wMaxRow+iXPos);
	if (pExpressionItem!=NULL)
	{
		if (bSelectec)
		{
			pDC->FillSolidRect(iXPos*(EP_PIC_WHIDE+PIC_SPACE)+PIC_SPACE/2,iYPos*(EP_PIC_HIGHT+PIC_SPACE)+PIC_SPACE/2,
				EP_PIC_WHIDE+PIC_SPACE,EP_PIC_HIGHT+PIC_SPACE,RGB(255,255,255));
			pDC->Draw3dRect(iXPos*(EP_PIC_WHIDE+PIC_SPACE)+PIC_SPACE/2,iYPos*(EP_PIC_HIGHT+PIC_SPACE)+PIC_SPACE/2,
				EP_PIC_WHIDE+PIC_SPACE,EP_PIC_HIGHT+PIC_SPACE,RGB(28,57,208),RGB(28,57,208));
		}
		else
		{
			pDC->FillSolidRect(iXPos*(EP_PIC_WHIDE+PIC_SPACE)+PIC_SPACE/2,iYPos*(EP_PIC_HIGHT+PIC_SPACE)+PIC_SPACE/2,
				EP_PIC_WHIDE+PIC_SPACE,EP_PIC_HIGHT+PIC_SPACE,RGB(255,255,255));
		
		}

		//������Դ
		CSkinImage SkinImage;
		SkinImage.LoadFromResource(GetModuleHandle(CLIENT_SHARE_DLL_NAME),pExpressionItem->m_uImageID);
		SkinImage.AlphaDrawImage(pDC,iXPos*(EP_PIC_WHIDE+PIC_SPACE)+PIC_SPACE,iYPos*(EP_PIC_HIGHT+PIC_SPACE)+PIC_SPACE,RGB(255,0,255));
	}
	return;
}

//�ػ���Ϣ
void CExpression::OnPaint()
{
	CPaintDC dc(this);

	//�滭����
	CRect rcClient;
	GetClientRect(&rcClient);
	dc.FillSolidRect(&rcClient,RGB(255,255,255));
	dc.Draw3dRect(&rcClient,RGB(0,75,151),RGB(0,75,151));

	//�滭����ͷ��
	for (WORD i=0;i<m_wMaxLine*m_wMaxRow;i++) DrawItem(&dc,i%m_wMaxRow,i/m_wMaxRow,(m_wSelectIndex==i));

	return;
}

//����ƶ���Ϣ
void CExpression::OnMouseMove(UINT nFlags, CPoint point)
{
	WORD wSelectIndex=HitItemTest(point);
	if (wSelectIndex!=m_wSelectIndex)
	{
		CDC * pDC=GetDC();
		if (m_wSelectIndex!=MAX_EXPRESS_ITEM)
		{
			//�����ѡ��
			DrawItem(pDC,m_wSelectIndex%m_wMaxRow,m_wSelectIndex/m_wMaxRow,false);
			m_wSelectIndex=MAX_EXPRESS_ITEM;
		}
		m_wSelectIndex=wSelectIndex;
		if (m_wSelectIndex!=MAX_EXPRESS_ITEM)
		{
			//��ʾ��ѡ��
			CExpressionItem * pExpressionItem=GetExpressItem(m_wSelectIndex);
			if (pExpressionItem!=NULL) DrawItem(pDC,m_wSelectIndex%m_wMaxRow,m_wSelectIndex/m_wMaxRow,true);
		}
		ReleaseDC(pDC);
	}

	return;
}

//��갴����Ϣ
void CExpression::OnLButtonDown(UINT nFlags, CPoint point)
{
	if ((m_wSelectIndex!=MAX_EXPRESS_ITEM)&&(m_pParentWnd!=NULL))
	{
		m_pParentWnd->SendMessage(WM_HIT_EXPMESSTION,(WPARAM)m_wSelectIndex,(LPARAM)m_wSelectIndex);
		DestroyWindow();
	}
	return;
}

//��������
WORD CExpression::HitItemTest(CPoint MousePoint)
{
	WORD wXPos=(WORD)(MousePoint.x/(PIC_SPACE+EP_PIC_WHIDE));
	WORD wYPos=(WORD)(MousePoint.y/(PIC_SPACE+EP_PIC_HIGHT));
	wXPos=__min(m_wMaxRow-1,wXPos);
	wYPos=__min(m_wMaxLine-1,wYPos);
	return wYPos*m_wMaxRow+wXPos;
}

//////////////////////////////////////////////////////////////////////////
