// HUDViewControl.cpp : 实现文件
//

#include "stdafx.h"
#include "UAV_3D_FCS.h"
#include "HUDViewControl.h"


// CHUDViewControl

IMPLEMENT_DYNCREATE(CHUDViewControl, CFormView)

CHUDViewControl::CHUDViewControl()
	: CFormView(CHUDViewControl::IDD)
{

}

CHUDViewControl::~CHUDViewControl()
{
}

void CHUDViewControl::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CHUDViewControl, CFormView)
END_MESSAGE_MAP()


// CHUDViewControl 诊断

#ifdef _DEBUG
void CHUDViewControl::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CHUDViewControl::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CHUDViewControl 消息处理程序
