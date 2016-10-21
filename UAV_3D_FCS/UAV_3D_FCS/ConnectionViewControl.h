#pragma once
/***************************************************************
* Copyright (c) 2016, �µ���
* All rights reserved.
*
* �ļ����ƣ�ConnectionViewControl.h
* ժ    Ҫ�����ڱ���Ŀ��ͨ������ģ�����ͼ��ͷ�ļ�
*
* ��ǰ�汾��1.0
* ��    �ߣ��µ���
* ������ڣ�2016-10-21
***************************************************************/



#include "TcpClient.h"
#include "resource.h"

// CConnectionViewControl ������ͼ

class CConnectionViewControl : public CFormView
{
	DECLARE_DYNCREATE(CConnectionViewControl)

protected:
	CConnectionViewControl();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
	virtual ~CConnectionViewControl();

public:
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_COMMUNICATION };
#endif
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

private:
	/* TCPͨ�ſͻ��˶��� */
	CTcpClient m_TcpClient;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedBtnReset();
	afx_msg void OnBnClickedBtnTcpConnect();
	virtual void OnInitialUpdate();
};


