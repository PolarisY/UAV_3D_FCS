/***************************************************************
* Copyright (c) 2016, �µ���
* All rights reserved.
*
* �ļ����ƣ�MySplitterWnd.h
* ժ    Ҫ�����ļ���Ϊһ�����MFC���Զ��崰�ڷָ���ͷ�ļ���
* ��һ�汾������������������¡�����ƶ���Ϣ�Ĺ��ܡ�
*
* ��ǰ�汾��1.0
* ��    �ߣ��µ���
* ������ڣ�2016��10��14��
***************************************************************/
#pragma once
#include "afxext.h"// Graphic.cpp : ʵ���ļ�

 

class CMySplitterWnd :
	public CSplitterWnd
{
public:
	CMySplitterWnd(void);
	~CMySplitterWnd(void);
	DECLARE_MESSAGE_MAP()
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
};

