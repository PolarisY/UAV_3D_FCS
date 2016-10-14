
// MainFrm.cpp : CMainFrame 类的实现
//

#include "stdafx.h"
#include "UAV_3D_FCS.h"

#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	ON_WM_CREATE()
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // 状态行指示器
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

// CMainFrame 构造/析构

CMainFrame::CMainFrame()
{
	// TODO: 在此添加成员初始化代码
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	//if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP | CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
	//	!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	//{
	//	TRACE0("未能创建工具栏\n");
	//	return -1;      // 未能创建
	//}

	//if (!m_wndStatusBar.Create(this))
	//{
	//	TRACE0("未能创建状态栏\n");
	//	return -1;      // 未能创建
	//}
	//m_wndStatusBar.SetIndicators(indicators, sizeof(indicators)/sizeof(UINT));

	// TODO: 如果不需要可停靠工具栏，则删除这三行
	/*m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBar);*/

	SetMenu(NULL);

	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	//修改项目名称
	cs.lpszName = _T("UAV_3D_FCS");
	cs.style &= ~FWS_ADDTOTITLE;

	return TRUE;
}

// CMainFrame 诊断

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}
#endif //_DEBUG


// CMainFrame 消息处理程序



BOOL CMainFrame::OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext)
{
	// TODO: 在此添加专用代码和/或调用基类
#if 0
	CRect rect;
	GetClientRect(&rect);

	int cx = GetSystemMetrics(SM_CXSCREEN);
	int	cy = GetSystemMetrics(SM_CYSCREEN);
	SetWindowPos(NULL, 0, 0, cx, cy, SWP_NOMOVE);



	//整体分成2行一列
	if (!m_splitter_wnd.CreateStatic(this, 2, 1, WS_CHILD | WS_VISIBLE | WS_BORDER))
	{
		return FALSE;
	}

	//将下面的一行分成一行两列
	if (!m_splitter_wnd_bottom.CreateStatic(this, 1, 2, WS_CHILD | WS_VISIBLE | WS_BORDER))
	{
		return FALSE;
	}

	//将上面的一行分成一行两列
	if (!m_splitter_wnd_top.CreateStatic(this, 1, 2, WS_CHILD | WS_VISIBLE | WS_BORDER))
	{
		return FALSE;
	}
	//下面进行 行和列 的长度设置
	m_splitter_wnd.SetRowInfo(0, (int)(rect.Height() * 0.9), 0);

	m_splitter_wnd_bottom.SetColumnInfo(0, (int)(rect.Width() * 0.7), 0);
	m_splitter_wnd_bottom.SetColumnInfo(1, (int)(rect.Width() * 0.3), 0);

	m_splitter_wnd_top.SetColumnInfo(0, (int)(rect.Width() * 0.7), 0);
	m_splitter_wnd_top.SetColumnInfo(1, (int)(rect.Width() * 0.3), 0);
	
	//3D
	if (!m_splitter_wnd.CreateView(0, 0, RUNTIME_CLASS(COSGViewControl), CSize((int)rect.Width() * 0.7, (int)(rect.Height() * 0.9)), pContext))
	{
		return FALSE;
	}

	//飞控
	if (!m_splitter_wnd_top.CreateView(0, 1, nullptr, CSize((int)rect.Width() * 0.3, (int)(rect.Height() * 0.9)), pContext))
	{
		return FALSE;
	}

	//MySQL
	if (!m_splitter_wnd_bottom.CreateView(1, 0, nullptr, CSize((int)rect.Width() * 0.7, (int)(rect.Height() * 0.1)), pContext))
	{
		return FALSE;
	}

	//connect
	if (!m_splitter_wnd_bottom.CreateView(1, 1, nullptr, CSize((int)rect.Width() * 0.3, (int)(rect.Height() * 0.1)), pContext))
	{
		return FALSE;
	} 

#endif


	return true;
}
