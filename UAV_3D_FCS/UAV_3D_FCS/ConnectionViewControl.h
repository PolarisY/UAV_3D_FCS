#pragma once

#include "TcpClient.h"
#include "resource.h"

// CConnectionViewControl 窗体视图

class CConnectionViewControl : public CFormView
{
	DECLARE_DYNCREATE(CConnectionViewControl)

protected:
	CConnectionViewControl();           // 动态创建所使用的受保护的构造函数
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
	/* TCP通信客户端对象 */
	CTcpClient m_TcpClient;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedBtnReset();
	afx_msg void OnBnClickedBtnTcpConnect();
	virtual void OnInitialUpdate();
};


