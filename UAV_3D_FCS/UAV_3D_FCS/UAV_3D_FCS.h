
// UAV_3D_FCS.h : UAV_3D_FCS Ӧ�ó������ͷ�ļ�
//
#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"       // ������


// CUAV_3D_FCSApp:
// �йش����ʵ�֣������ UAV_3D_FCS.cpp
//

class CUAV_3D_FCSApp : public CWinApp
{
public:
	CUAV_3D_FCSApp();


// ��д
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// ʵ��
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CUAV_3D_FCSApp theApp;
