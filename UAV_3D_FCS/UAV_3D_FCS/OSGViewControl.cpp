/***************************************************************
* Copyright (c) 2016, �µ���
* All rights reserved.
*
* �ļ����ƣ�OSGViewControl.cpp
* ժ    Ҫ��3Dģ��Ŀ�������
*
* ��ǰ�汾��1.0
* ��    �ߣ��µ���
* ������ڣ�2016��10����
***************************************************************/
// OSGViewControl.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "UAV_3D_FCS.h"
#include "OSGViewControl.h"


// COSGViewControl

IMPLEMENT_DYNCREATE(COSGViewControl, CFormView)

COSGViewControl::COSGViewControl()
	: CFormView(IDD_BASE_VIEW_CONTROL)
{

}

COSGViewControl::~COSGViewControl()
{
}

void COSGViewControl::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(COSGViewControl, CFormView)
END_MESSAGE_MAP()


// COSGViewControl ���

#ifdef _DEBUG
void COSGViewControl::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void COSGViewControl::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// COSGViewControl ��Ϣ�������
