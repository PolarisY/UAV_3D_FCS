
// MainFrm.h : CMainFrame ��Ľӿ�
//

#pragma once

#include "MySplitterWnd.h"
#include "OSGViewControl.h"

class CMainFrame : public CFrameWnd
{
	
protected: // �������л�����
	CMainFrame();
	DECLARE_DYNCREATE(CMainFrame)

// ����
public:

// ����
public:

// ��д
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// ʵ��
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // �ؼ���Ƕ���Ա
	CToolBar          m_wndToolBar;
	CStatusBar        m_wndStatusBar;

private:
	//���ܴ��ڷ�Ϊ����һ��
	CMySplitterWnd m_splitter_wnd;   
	//�������һ�зֳ�һ������
	CMySplitterWnd m_splitter_wnd_bottom;
	//�������һ�зֳ�һ������
	CMySplitterWnd m_splitter_wnd_top;



// ���ɵ���Ϣӳ�亯��
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	DECLARE_MESSAGE_MAP()

	virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);
};


