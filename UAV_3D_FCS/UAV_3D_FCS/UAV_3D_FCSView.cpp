
// UAV_3D_FCSView.cpp : CUAV_3D_FCSView ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
#ifndef SHARED_HANDLERS
#include "UAV_3D_FCS.h"
#endif

#include "UAV_3D_FCSDoc.h"
#include "UAV_3D_FCSView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CUAV_3D_FCSView

IMPLEMENT_DYNCREATE(CUAV_3D_FCSView, CView)

BEGIN_MESSAGE_MAP(CUAV_3D_FCSView, CView)
	// ��׼��ӡ����
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
END_MESSAGE_MAP()

// CUAV_3D_FCSView ����/����

CUAV_3D_FCSView::CUAV_3D_FCSView()
{
	// TODO: �ڴ˴���ӹ������

}

CUAV_3D_FCSView::~CUAV_3D_FCSView()
{
}

BOOL CUAV_3D_FCSView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CView::PreCreateWindow(cs);
}

// CUAV_3D_FCSView ����

void CUAV_3D_FCSView::OnDraw(CDC* /*pDC*/)
{
	CUAV_3D_FCSDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: �ڴ˴�Ϊ����������ӻ��ƴ���
}


// CUAV_3D_FCSView ��ӡ

BOOL CUAV_3D_FCSView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// Ĭ��׼��
	return DoPreparePrinting(pInfo);
}

void CUAV_3D_FCSView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӷ���Ĵ�ӡǰ���еĳ�ʼ������
}

void CUAV_3D_FCSView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӵ�ӡ����е��������
}


// CUAV_3D_FCSView ���

#ifdef _DEBUG
void CUAV_3D_FCSView::AssertValid() const
{
	CView::AssertValid();
}

void CUAV_3D_FCSView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CUAV_3D_FCSDoc* CUAV_3D_FCSView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CUAV_3D_FCSDoc)));
	return (CUAV_3D_FCSDoc*)m_pDocument;
}
#endif //_DEBUG


// CUAV_3D_FCSView ��Ϣ�������
