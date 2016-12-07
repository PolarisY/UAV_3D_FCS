#pragma once

#include "HUD.h"

// CHUDViewControl 窗体视图

class CHUDViewControl : public CFormView
{
	DECLARE_DYNCREATE(CHUDViewControl)

protected:
	CHUDViewControl();           // 动态创建所使用的受保护的构造函数
	virtual ~CHUDViewControl();

public:
	enum { IDD = IDD_HUD };
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

private:
	CHUD m_HUD;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
};


