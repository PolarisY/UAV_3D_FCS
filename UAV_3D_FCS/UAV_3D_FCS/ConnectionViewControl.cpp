/***************************************************************
* Copyright (c) 2016, �µ���
* All rights reserved.
*
* �ļ����ƣ�ConnectionViewControl.cpp
* ժ    Ҫ�����ڱ���Ŀ��ͨ������ģ�����ͼ���cpp�ļ�
*
* ��ǰ�汾��1.0
* ��    �ߣ��µ���
* ������ڣ�2016-10-21
***************************************************************/

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
	if (m_TcpClient != nullptr)
	{
		delete[] m_TcpClient;
	}
}

void CConnectionViewControl::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CConnectionViewControl, CFormView)
	ON_BN_CLICKED(IDC_BTN_RESET, &CConnectionViewControl::OnBnClickedBtnReset)
	ON_BN_CLICKED(IDC_BTN_TCP_CONNECT, &CConnectionViewControl::OnBnClickedBtnTcpConnect)
END_MESSAGE_MAP()


// CConnectionViewControl ���

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


// CConnectionViewControl ��Ϣ�������


void CConnectionViewControl::OnBnClickedBtnReset()
{
	////��ȡ���õ�IP
	CString _ip;
	GetDlgItemText(IDC_TCP_IP, _ip);
	std::string ip;
	ip = (LPCSTR)CStringA(_ip);

	//��ȡ���õĶ˿�
	int port = GetDlgItemInt(IDC_TCP_PORT);

	//����ip��port
	m_TcpClient->SetConnectAddr(port, ip);
}


void CConnectionViewControl::OnBnClickedBtnTcpConnect()
{  
	//����TCP���� 

	m_TcpClient->StartTcpConnect();

	if (m_TcpClient->IsTcpConnecting())
	{
		MessageBox(_T("TCP is connecting!"));
	} 
}


void CConnectionViewControl::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	 
	/* ��ʼ����Ϊ127.0.0.1 : 10000 */
	SetDlgItemInt(IDC_TCP_PORT, 10002);
	GetDlgItem(IDC_TCP_IP)->SetWindowText(_T("192.168.16.107")); 
	
	m_TcpClient = new CTcpClient; 
}
