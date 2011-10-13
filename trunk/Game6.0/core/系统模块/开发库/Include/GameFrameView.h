#ifndef GAME_FRAME_VIEW_HEAD_FILE
#define GAME_FRAME_VIEW_HEAD_FILE

#pragma once

#include "GameFrame.h"
#include "ThreadDraw.h"

//////////////////////////////////////////////////////////////////////////

//�滭ģʽ
enum enImageMode 
{
	enMode_Spread,					//ƽ��ģʽ
	enMode_Centent,					//����ģʽ
	enMode_ElongGate,				//����ģʽ
};

//��˵��
class CClientKernelSink;

//////////////////////////////////////////////////////////////////////////

//��Ϸ��ͼ���
class GAME_FRAME_CLASS CGameFrameView : public CWnd, public IGameFrameView
{
	//��Ԫ����
	friend class CGameFrameDlg;
	friend class CClientKernelSink;

	//λ�ñ���
protected:
	POINT							m_ptName[MAX_CHAIR];				//����λ��
	POINT							m_ptFace[MAX_CHAIR];				//ͷ��λ��
	POINT							m_ptTimer[MAX_CHAIR];				//ʱ��λ��
	POINT							m_ptReady[MAX_CHAIR];				//׼��λ��

	//�û�����
private:
	WORD							m_wTimer[MAX_CHAIR];				//�û�ʱ��
	tagUserData						* m_pUserItem[MAX_CHAIR];			//�û���Ϣ

	//���ָ��
private:
	void							* m_pReserve;						//����ָ��
	IUserFaceRes					* m_pIUserFaceRes;					//ͷ��ӿ�

	//��ͼ����
private:
	bool							m_bReDraw;							//�Ƿ��ػ�
	CSize							m_ImageSize;						//�����С
	CImage							m_ImageBuffer;						//����λͼ
	const bool						m_bDoubleBuf;						//�����ͼ
	const UINT						m_uColorCount;						//����ɫ��
	CThreadDraw						* const m_pThreadDraw;				//��ͼ��Ϣ

	//ֻ������
public:
	static const int				m_nXFace;							//ͷ��߶�
	static const int				m_nYFace;							//ͷ����
	static const int				m_nXTimer;							//��ʱ����
	static const int				m_nYTimer;							//��ʱ����
	static const int				m_nXBorder;							//��ܿ��
	static const int				m_nYBorder;							//��ܸ߶�

	//��������
public:
	//���캯��
	CGameFrameView(bool bDoubleBuf=true ,UINT uColorCount=16, CThreadDraw * pThreadDraw=NULL);
	//��������
	virtual ~CGameFrameView();

	//�����ӿ�
public:
	//�ͷŶ���
	virtual bool __cdecl Release() { if (IsValid()) delete this; return true; }
	//�Ƿ���Ч
	virtual bool __cdecl IsValid() { return AfxIsValidAddress(this,sizeof(CGameFrameView))?true:false; }
	//�ӿڲ�ѯ
	virtual void * __cdecl QueryInterface(const IID & Guid, DWORD dwQueryVer);

	//�̳к���
private:
	//���ý���
	virtual void ResetGameView()=NULL;
	//�����ؼ�
	virtual void RectifyGameView(int nWidth, int nHeight)=NULL;
	//�滭����
	virtual void DrawGameView(CDC * pDC, int nWidth, int nHeight)=NULL;

	//���ܺ���
public:
	//��ȡʱ��
	WORD GetUserTimer(WORD wChairID);
	//��ȡ���
	const tagUserData * GetUserInfo(WORD wChairID);
	//���½���
	void UpdateGameView(const CRect * pRect);
	//��ȡ����
	bool GetGameViewImage(CImage & ImageBuffer, int nXPos, int nYPos, int nWidth, int nHeight);

	//��ͼ����
public:
	//�滭����
	void DrawViewImage(CDC * pDC, CSkinImage & SkinImage, enImageMode ImageMode);
	//�滭ͷ��
	void DrawUserFace(CDC * pDC, WORD wFaceID, int nXPos, int nYPos, bool bOffLine);
	//�滭׼��
	void DrawUserReady(CDC * pDC, int nXPos, int nYPos);
	//�滭ʱ��
	void DrawUserTimer(CDC * pDC, int nXPos, int nYPos, WORD wTime, WORD wTimerArea=99);
	//͸���滭
	void AlphaDrawImage(CDC * pDesDC, int nXDes, int nYDes, int nDesWidth, int nDesHeight, CDC * pScrDC, int nXScr, int nYScr, COLORREF crTransColor);
	//͸���滭
	void AlphaDrawImage(CDC * pDesDC, int nXDes, int nYDes, int nDesWidth, int nDesHeight, HBITMAP hBitBmp, int nXScr, int nYScr, COLORREF crTransColor);

	//�ڲ�����
private:
	//���ý���
	void ResetData();
	//���ýӿ�
	bool SetUserFaceRes(IUnknownEx * pIUnknownEx);
	//����ʱ��
	bool SetUserTimer(WORD wChairID, WORD wTimer);
	//�����û�
	bool SetUserInfo(WORD wChairID, tagUserData * pUserData);

	//��Ϣӳ��
protected:
	//�滭����
	afx_msg void OnPaint();
	//λ�ñ仯
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//������Ϣ
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//�����Ϣ
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	//������Ϣ
	afx_msg void OnDestroy();

	DECLARE_MESSAGE_MAP()
};

//////////////////////////////////////////////////////////////////////////

#endif