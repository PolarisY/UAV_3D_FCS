/***************************************************************
* Copyright (c) 2016, �µ���
* All rights reserved.
*
* �ļ����ƣ�MySplitterWnd.cpp
* ժ    Ҫ�����ļ���Ϊһ�����MFC���Զ��崰�ڷָ����ʵ���ļ���
*
* ��ǰ�汾��1.0
* ��    �ߣ��µ���
* ������ڣ�2016��10��14��
***************************************************************/
#include "stdafx.h"
#include "MySplitterWnd.h"

CMySplitterWnd::CMySplitterWnd(void)
{
}


CMySplitterWnd::~CMySplitterWnd(void)
{
}

BEGIN_MESSAGE_MAP(CMySplitterWnd, CSplitterWnd)
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()


void CMySplitterWnd::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	//�������������Ϣ
	CWnd::OnLButtonDown(nFlags, point);
}


void CMySplitterWnd::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	//��������ƶ���Ϣ
	CWnd::OnMouseMove(nFlags, point);
}
