/***************************************************************
* Copyright (c) 2016, �µ���
* All rights reserved.
*
* �ļ����ƣ�FlightSysViewControl.cpp
* ժ    Ҫ�����ڱ���Ŀ�ķ��п���ģ�����ͼ���cpp�ļ�
*
* ��ǰ�汾��1.0
* ��    �ߣ��µ���
* ������ڣ�2016-10-21
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


// CFlightSysViewControl ���

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


// CFlightSysViewControl ��Ϣ�������
