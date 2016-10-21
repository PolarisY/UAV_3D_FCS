#pragma once
/***************************************************************
* Copyright (c) 2016, 陈登龙
* All rights reserved.
*
* 文件名称：FlightSysViewControl.h
* 摘    要：用于本项目的飞行控制模块的视图类的头文件
*
* 当前版本：1.0
* 作    者：陈登龙
* 完成日期：2016-10-21
***************************************************************/


// CFlightSysViewControl 窗体视图

class CFlightSysViewControl : public CFormView
{
	DECLARE_DYNCREATE(CFlightSysViewControl)

protected:
	CFlightSysViewControl();           // 动态创建所使用的受保护的构造函数
	virtual ~CFlightSysViewControl();

public:
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_FCS };
#endif
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
};


