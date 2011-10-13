#ifndef GAME_FRAME_HEAD_FILE
#define GAME_FRAME_HEAD_FILE

#pragma once

#include "Stdafx.h"
#include "Resource.h"
#include "DlgControlBar.h"
#include "PlazaViewItem.h"

/////////////////////////////////////////////////////////////////////////////

//热键定义
#define IDI_HOT_KEY_BOSS			0x0100								//老板热键

/////////////////////////////////////////////////////////////////////////////

//主框架类
class CGameFrame : public CFrameWnd
{
	//控件变量
public:
	CSkinButton							m_btMin;						//最小按钮
	CSkinButton							m_btMax;						//最大按钮
	CSkinButton							m_btClose;						//关闭按钮
	CWebBrowser							m_BrowerAD;						//浏览窗口
	CToolTipCtrl						m_ToolTipCtrl;					//提示控件
	CPlazaViewItem						m_DlgGamePlaza;					//游戏广场
	CDlgControlBar						m_DlgControlBar;				//控制条类

	//界面状态
protected:
	bool								m_bMaxShow;						//最大标志
	CRect								m_rcNormalSize;					//正常位置

	//导航按钮
public:
	CSkinButton							m_btButton1;					//功能按钮
	CSkinButton							m_btButton2;					//功能按钮
	CSkinButton							m_btButton3;					//功能按钮
	CSkinButton							m_btButton4;					//功能按钮
	CSkinButton							m_btButton5;					//功能按钮

	//资源变量
protected:
	CSkinImage							m_ImageL;						//资源图片
	CSkinImage							m_ImageR;						//资源图片
	CSkinImage							m_ImageTL;						//资源图片
	CSkinImage							m_ImageTM;						//资源图片
	CSkinImage							m_ImageTR;						//资源图片

	//函数定义	
public:
	//构造函数
	CGameFrame();
	//析构函数
	virtual ~CGameFrame();

	//重载函数
public:
	//消息解释
	virtual BOOL PreTranslateMessage(MSG * pMsg);

	//界面函数
protected:
	//最大窗口
	bool MaxSizeWindow();
	//还原窗口
	bool RestoreWindow();

	//消息函数
protected:
	//绘画消息
	afx_msg void OnPaint();
	//绘画背景
	afx_msg BOOL OnEraseBkgnd(CDC * pDC);
	//创建消息
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//大小消息
	afx_msg void OnGetMinMaxInfo(MINMAXINFO FAR * lpMMI);
	//位置消息
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//最小按钮
	afx_msg void OnBnClickedMin();
	//最小按钮
	afx_msg void OnBnClickedMax();
	//关闭按钮
	afx_msg void OnBnClickedClose();
	//按键测试
	afx_msg LRESULT OnNcHitTest(CPoint Point);
	//鼠标消息
	afx_msg void OnLButtonDown(UINT nFlags, CPoint Point);
	//鼠标消息
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint Point);
	//改变消息
	afx_msg void OnSettingChange(UINT uFlags, LPCTSTR lpszSection);
	//关闭消息
	afx_msg void OnClose();

	//导航按钮
protected:
	//功能按钮
	afx_msg void OnBnClickedButton1();
	//功能按钮
	afx_msg void OnBnClickedButton2();
	//功能按钮
	afx_msg void OnBnClickedButton3();
	//功能按钮
	afx_msg void OnBnClickedButton4();
	//功能按钮
	afx_msg void OnBnClickedButton5();

	//自定义消息
protected:
	//热键消息
	LRESULT OnHotKeyMessage(WPARAM wParam, LPARAM lParam);
	//安装完成
	LRESULT OnMessageSetupFinish(WPARAM wParam, LPARAM lParam);

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

#endif
