/***************************************************************
* Copyright (c) 2016, �µ���
* All rights reserved.
*
* �ļ����ƣ�OSGViewControl.h
* ժ    Ҫ��3Dģ�������ͷ�ļ���
*
* ��ǰ�汾��1.0
* ��    �ߣ��µ���
* ������ڣ�2016��10����
***************************************************************/
#pragma once



// COSGViewControl ������ͼ

class COSGViewControl : public CFormView
{
	DECLARE_DYNCREATE(COSGViewControl)

protected:
	COSGViewControl();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
	virtual ~COSGViewControl();

public:
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_OSG };
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


