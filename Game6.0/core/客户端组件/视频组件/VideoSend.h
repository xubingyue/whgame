// CVideoSend.h  : Declaration of ActiveX Control wrapper class(es) created by Microsoft Visual C++

#pragma once

/////////////////////////////////////////////////////////////////////////////
// CVideoSend

class CVideoSend : public CWnd
{
public:
	CLSID const& GetClsid()
	{
		static CLSID const clsid
			= { 0x66AFD800, 0x48, 0x4D4E, { 0xB4, 0x74, 0x4, 0x6C, 0x4, 0x30, 0x48, 0x4E } };
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

	unsigned char OpenSend()
	{
		unsigned char result;
		InvokeHelper(0xdb, DISPATCH_METHOD, VT_UI1, (VOID*)&result, NULL);
		return result;
	}
	VOID CloseSend()
	{
		InvokeHelper(0xdc, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	VOID InsertP2PSocket(long SenderID, long ReceiverID, unsigned long ServerIP, unsigned short ServerPort)
	{
		static BYTE parms[] = VTS_I4 VTS_I4 VTS_UI4 VTS_UI2 ;
		InvokeHelper(0xd9, DISPATCH_METHOD, VT_EMPTY, NULL, parms, SenderID, ReceiverID, ServerIP, ServerPort);
	}
	VOID DeleteP2PSocket(long ReceiverID)
	{
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0xda, DISPATCH_METHOD, VT_EMPTY, NULL, parms, ReceiverID);
	}
	unsigned char GetP2PInfo(long ReceiverID, unsigned long * LocalIP, unsigned short * LocalPort, unsigned long * NatIP, unsigned short * NatPort)
	{
		unsigned char result;
		static BYTE parms[] = VTS_I4 VTS_PUI4 VTS_PUI2 VTS_PUI4 VTS_PUI2 ;
		InvokeHelper(0xde, DISPATCH_METHOD, VT_UI1, (VOID*)&result, parms, ReceiverID, LocalIP, LocalPort, NatIP, NatPort);
		return result;
	}
	VOID SetVideoMode(unsigned short NewMode)
	{
		static BYTE parms[] = VTS_UI2 ;
		InvokeHelper(0xc9, DISPATCH_METHOD, VT_EMPTY, NULL, parms, NewMode);
	}
	VOID SetVideoRate(unsigned short NewRate)
	{
		static BYTE parms[] = VTS_UI2 ;
		InvokeHelper(0xca, DISPATCH_METHOD, VT_EMPTY, NULL, parms, NewRate);
	}
	VOID SetVideoFrameRate(unsigned short NewFrameRate)
	{
		static BYTE parms[] = VTS_UI2 ;
		InvokeHelper(0xcb, DISPATCH_METHOD, VT_EMPTY, NULL, parms, NewFrameRate);
	}
	VOID EnableAudio(unsigned char IsEnable)
	{
		static BYTE parms[] = VTS_UI1 ;
		InvokeHelper(0xcc, DISPATCH_METHOD, VT_EMPTY, NULL, parms, IsEnable);
	}
	VOID EnableVideo(unsigned char IsEnable)
	{
		static BYTE parms[] = VTS_UI1 ;
		InvokeHelper(0xcd, DISPATCH_METHOD, VT_EMPTY, NULL, parms, IsEnable);
	}
	VOID ScaleVideo()
	{
		InvokeHelper(0xce, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	VOID Capture(LPCTSTR Path)
	{
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0xcf, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Path);
	}
	unsigned char HasVideoDrv()
	{
		unsigned char result;
		InvokeHelper(0xd0, DISPATCH_METHOD, VT_UI1, (VOID*)&result, NULL);
		return result;
	}


};
