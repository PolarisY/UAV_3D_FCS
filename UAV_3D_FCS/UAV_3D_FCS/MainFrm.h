
// MainFrm.h : CMainFrame 类的接口
//

#pragma once

#include "MySplitterWnd.h"
#include "OSGViewControl.h"

class CMainFrame : public CFrameWnd
{
	
protected: // 仅从序列化创建
	CMainFrame();
	DECLARE_DYNCREATE(CMainFrame)

// 特性
public:

// 操作
public:

// 重写
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// 实现
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // 控件条嵌入成员
	CToolBar          m_wndToolBar;
	CStatusBar        m_wndStatusBar;

private:
	//将总窗口分为两行一列
	CMySplitterWnd m_splitter_wnd;   
	//将下面的一行分成一行两列
	CMySplitterWnd m_splitter_wnd_bottom;
	//将上面的一行分成一行两列
	CMySplitterWnd m_splitter_wnd_top;



// 生成的消息映射函数
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	DECLARE_MESSAGE_MAP()

	virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);
};


