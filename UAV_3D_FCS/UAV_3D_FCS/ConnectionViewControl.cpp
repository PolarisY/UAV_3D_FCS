// ConnectionViewControl.cpp : 实现文件
//

#include "stdafx.h"
#include "UAV_3D_FCS.h"
#include "ConnectionViewControl.h"


// CConnectionViewControl

IMPLEMENT_DYNCREATE(CConnectionViewControl, CFormView)

CConnectionViewControl::CConnectionViewControl()
	: CFormView(IDD_COMMUNICATION)
{

}

CConnectionViewControl::~CConnectionViewControl()
{
}

void CConnectionViewControl::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CConnectionViewControl, CFormView)
	ON_BN_CLICKED(IDC_BTN_RESET, &CConnectionViewControl::OnBnClickedBtnReset)
	ON_BN_CLICKED(IDC_BTN_TCP_CONNECT, &CConnectionViewControl::OnBnClickedBtnTcpConnect)
END_MESSAGE_MAP()


// CConnectionViewControl 诊断

#ifdef _DEBUG
void CConnectionViewControl::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CConnectionViewControl::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CConnectionViewControl 消息处理程序


void CConnectionViewControl::OnBnClickedBtnReset()
{
	//获取设置的IP
	CString _ip;
	GetDlgItemText(IDC_TCP_IP, _ip);
	std::string ip;
	ip = (LPCSTR)CStringA(_ip);

	//获取设置的端口
	int port = GetDlgItemInt(IDC_TCP_PORT);

	//设置ip和port
	m_TcpClient.SetConnectAddr(port, ip);
}


void CConnectionViewControl::OnBnClickedBtnTcpConnect()
{  
	//开启TCP连接
	m_TcpClient.StartTcpConnect();

	/*if (m_TcpClient.IsTcpConnecting())
	{
		SetDlgItemText(IDC_BTN_TCP_CONNECT, _T("Disconnect"));
	}
	else
	{
		SetDlgItemText(IDC_BTN_TCP_CONNECT, _T("Connect"));
	}*/
}


void CConnectionViewControl::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	 
	/* 初始设置为127.0.0.1 : 10000 */
	SetDlgItemInt(IDC_TCP_PORT, 10000);
	GetDlgItem(IDC_TCP_IP)->SetWindowText(_T("127.0.0.1"));
}
