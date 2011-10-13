// CVideoRece.h  : Declaration of ActiveX Control wrapper class(es) created by Microsoft Visual C++

#pragma once

/////////////////////////////////////////////////////////////////////////////
// CVideoRece

class CVideoRece : public CWnd
{
public:
	CLSID const& GetClsid()
	{
		static CLSID const clsid
			= { 0x81885605, 0xAE2C, 0x4635, { 0xB1, 0xC6, 0x21, 0xE8, 0x1A, 0xFD, 0x7F, 0xA7 } };
		return clsid;
	}
	virtual BOOL Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle,
						const RECT& rect, CWnd* pParentWnd, UINT nID, 
						CCreateContext* pContext = NULL)
	{ 
		return CreateControl(GetClsid(), lpszWindowName, dwStyle, rect, pParentWnd, nID); 
	}

    BOOL Create(LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, 
				UINT nID, CFile* pPersist = NULL, BOOL bStorage = FALSE,
				BSTR bstrLicKey = NULL)
	{ 
		return CreateControl(GetClsid(), lpszWindowName, dwStyle, rect, pParentWnd, nID,
		pPersist, bStorage, bstrLicKey); 
	}

// Attributes
public:

// Operations
public:

	unsigned char OpenRece()
	{
		unsigned char result;
		InvokeHelper(0xdb, DISPATCH_METHOD, VT_UI1, (VOID*)&result, NULL);
		return result;
	}
	VOID CloseRece()
	{
		InvokeHelper(0xdc, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	unsigned char CreateP2P(long SenderID, long ReceiverID, unsigned long ServerIP, unsigned short ServerPort, unsigned long LocalIP, unsigned short LocalPort, unsigned long NatIP, unsigned short NatPort)
	{
		unsigned char result;
		static BYTE parms[] = VTS_I4 VTS_I4 VTS_UI4 VTS_UI2 VTS_UI4 VTS_UI2 VTS_UI4 VTS_UI2 ;
		InvokeHelper(0xda, DISPATCH_METHOD, VT_UI1, (VOID*)&result, parms, SenderID, ReceiverID, ServerIP, ServerPort, LocalIP, LocalPort, NatIP, NatPort);
		return result;
	}
	VOID SetAudioCache(long CacheTime)
	{
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0xc9, DISPATCH_METHOD, VT_EMPTY, NULL, parms, CacheTime);
	}
	VOID SetVideoCache(long CacheTime)
	{
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0xca, DISPATCH_METHOD, VT_EMPTY, NULL, parms, CacheTime);
	}
	VOID EnableAudio(unsigned char IsEnable)
	{
		static BYTE parms[] = VTS_UI1 ;
		InvokeHelper(0xcb, DISPATCH_METHOD, VT_EMPTY, NULL, parms, IsEnable);
	}
	VOID EnableVideo(unsigned char IsEnable)
	{
		static BYTE parms[] = VTS_UI1 ;
		InvokeHelper(0xcc, DISPATCH_METHOD, VT_EMPTY, NULL, parms, IsEnable);
	}
	VOID ScaleVideo()
	{
		InvokeHelper(0xcd, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	VOID Capture(LPCTSTR Path)
	{
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0xce, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Path);
	}


};
