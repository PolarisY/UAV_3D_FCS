
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

	/*ȥ���˵���*/
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

	int cx = GetSystemMetrics(SM_CXSCREEN);
	int	cy = GetSystemMetrics(SM_CYSCREEN);
	SetWindowPos(NULL, 0, 0, cx, cy, SWP_NOMOVE);

	CRect rect;
	GetClientRect(&rect);
	
	/*�������ڷֳ�4������*/
	if (!m_SplitterWnd.CreateStatic(this, 2, 2, WS_CHILD | WS_VISIBLE | WS_BORDER))
	{
		return FALSE;
	}  

	if (!m_SplitterWnd1.CreateStatic(&m_SplitterWnd, 2, 1, WS_CHILD | WS_VISIBLE, m_SplitterWnd.IdFromRowCol(0, 1)))
	{
		return FALSE;
	}

	/*���Ͻ�����3Dģ��*/
	if (!m_SplitterWnd.CreateView(0, 0, RUNTIME_CLASS(COSGViewControl), CSize((int)rect.Width() * 0.7, (int)(rect.Height() * 0.8)), pContext))
	{
		return FALSE;
	} 
 

	/*���Ͻ����ڷ��п��ƺ�HUDģ��*/ 
	if (!m_SplitterWnd1.CreateView(0, 0, RUNTIME_CLASS(CHUDViewControl), CSize((int)rect.Width() * 0.3, (int)(rect.Height() * 0.8 * 0.6)), pContext))
	{
		return FALSE;
	}

	if (!m_SplitterWnd1.CreateView(1, 0, RUNTIME_CLASS(CFlightSysViewControl), CSize((int)rect.Width() * 0.3, (int)(rect.Height() * 0.8 * 0.4)), pContext))
	{
		return FALSE;
	}



	/*���½��������ݻط�ģ��*/
	if (!m_SplitterWnd.CreateView(1, 0, RUNTIME_CLASS(CPlayBackViewControl), CSize((int)rect.Width() * 0.7, (int)(rect.Height() * 0.2)), pContext))
	{
		return FALSE;
	}

	/*���½�����ͨ������ģ��*/
	if (!m_SplitterWnd.CreateView(1, 1, RUNTIME_CLASS(CConnectionViewControl), CSize((int)rect.Width() * 0.3, (int)(rect.Height() * 0.2)), pContext))
	{
		return FALSE;
	} 
	



	  

	return true;
}
