
// MainFrm.cpp : CMainFrame ���ʵ��
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
	ID_SEPARATOR,           // ״̬��ָʾ��
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

// CMainFrame ����/����

CMainFrame::CMainFrame()
{
	// TODO: �ڴ���ӳ�Ա��ʼ������
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
	//	TRACE0("δ�ܴ���������\n");
	//	return -1;      // δ�ܴ���
	//}

	//if (!m_wndStatusBar.Create(this))
	//{
	//	TRACE0("δ�ܴ���״̬��\n");
	//	return -1;      // δ�ܴ���
	//}
	//m_wndStatusBar.SetIndicators(indicators, sizeof(indicators)/sizeof(UINT));

	// TODO: �������Ҫ��ͣ������������ɾ��������
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
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	//�޸���Ŀ����
	cs.lpszName = _T("UAV_3D_FCS");
	cs.style &= ~FWS_ADDTOTITLE;

	return TRUE;
}

// CMainFrame ���

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


// CMainFrame ��Ϣ�������



BOOL CMainFrame::OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext)
{
	// TODO: �ڴ����ר�ô����/����û���
#if 0
	CRect rect;
	GetClientRect(&rect);

	int cx = GetSystemMetrics(SM_CXSCREEN);
	int	cy = GetSystemMetrics(SM_CYSCREEN);
	SetWindowPos(NULL, 0, 0, cx, cy, SWP_NOMOVE);



	//����ֳ�2��һ��
	if (!m_splitter_wnd.CreateStatic(this, 2, 1, WS_CHILD | WS_VISIBLE | WS_BORDER))
	{
		return FALSE;
	}

	//�������һ�зֳ�һ������
	if (!m_splitter_wnd_bottom.CreateStatic(this, 1, 2, WS_CHILD | WS_VISIBLE | WS_BORDER))
	{
		return FALSE;
	}

	//�������һ�зֳ�һ������
	if (!m_splitter_wnd_top.CreateStatic(this, 1, 2, WS_CHILD | WS_VISIBLE | WS_BORDER))
	{
		return FALSE;
	}
	//������� �к��� �ĳ�������
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

	//�ɿ�
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
