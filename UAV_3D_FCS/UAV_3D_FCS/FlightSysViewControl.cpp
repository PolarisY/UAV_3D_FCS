/***************************************************************
* Copyright (c) 2016, 陈登龙
* All rights reserved.
*
* 文件名称：FlightSysViewControl.cpp
* 摘    要：用于本项目的飞行控制模块的视图类的cpp文件
*
* 当前版本：1.0
* 作    者：陈登龙
* 完成日期：2016-10-21
***************************************************************/

#include "stdafx.h"
#include "UAV_3D_FCS.h"
#include "FlightSysViewControl.h"


// CFlightSysViewControl

IMPLEMENT_DYNCREATE(CFlightSysViewControl, CFormView)

CFlightSysViewControl::CFlightSysViewControl()
	: CFormView(IDD_FCS)
{

}

CFlightSysViewControl::~CFlightSysViewControl()
{
}

void CFlightSysViewControl::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CFlightSysViewControl, CFormView)
END_MESSAGE_MAP()


// CFlightSysViewControl 诊断

#ifdef _DEBUG
void CFlightSysViewControl::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CFlightSysViewControl::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CFlightSysViewControl 消息处理程序
