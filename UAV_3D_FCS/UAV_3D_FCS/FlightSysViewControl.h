#pragma once
/***************************************************************
* Copyright (c) 2016, �µ���
* All rights reserved.
*
* �ļ����ƣ�FlightSysViewControl.h
* ժ    Ҫ�����ڱ���Ŀ�ķ��п���ģ�����ͼ���ͷ�ļ�
*
* ��ǰ�汾��1.0
* ��    �ߣ��µ���
* ������ڣ�2016-10-21
***************************************************************/


// CFlightSysViewControl ������ͼ

class CFlightSysViewControl : public CFormView
{
	DECLARE_DYNCREATE(CFlightSysViewControl)

protected:
	CFlightSysViewControl();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
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
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
};


