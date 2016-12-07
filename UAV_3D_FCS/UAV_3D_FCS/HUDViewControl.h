#pragma once

#include "HUD.h"

// CHUDViewControl ������ͼ

class CHUDViewControl : public CFormView
{
	DECLARE_DYNCREATE(CHUDViewControl)

protected:
	CHUDViewControl();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
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
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
};


