// PlayBackViewControl.cpp : 实现文件
//

#include "stdafx.h"
#include "UAV_3D_FCS.h"
#include "PlayBackViewControl.h"


// CPlayBackViewControl

IMPLEMENT_DYNCREATE(CPlayBackViewControl, CFormView)

CPlayBackViewControl::CPlayBackViewControl()
	: CFormView(IDD_PLAY_BACK)
{

}

CPlayBackViewControl::~CPlayBackViewControl()
{
}

void CPlayBackViewControl::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CPlayBackViewControl, CFormView)
END_MESSAGE_MAP()


// CPlayBackViewControl 诊断

#ifdef _DEBUG
void CPlayBackViewControl::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CPlayBackViewControl::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CPlayBackViewControl 消息处理程序
