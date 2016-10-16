
// MainFrm.h : CMainFrame 类的接口
//

#pragma once

#include "MySplitterWnd.h"
#include "OSGViewControl.h"
#include "ConnectionViewControl.h"
#include "FlightSysViewControl.h"
#include "PlayBackViewControl.h"

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
	CMySplitterWnd m_SplitterWnd;   

	CMySplitterWnd m_SplitterChild;

	//将下面的一行分成一行两列
	//CMySplitterWnd m_SplitterWndBottom;
	//将上面的一行分成一行两列
	//CMySplitterWnd m_SplitterWndTop;



// 生成的消息映射函数
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	DECLARE_MESSAGE_MAP()

	virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);
};


