
// UAV_3D_FCSView.h : CUAV_3D_FCSView ��Ľӿ�
//

#pragma once


class CUAV_3D_FCSView : public CView
{
protected: // �������л�����
	CUAV_3D_FCSView();
	DECLARE_DYNCREATE(CUAV_3D_FCSView)

// ����
public:
	CUAV_3D_FCSDoc* GetDocument() const;

// ����
public:

// ��д
public:
	virtual void OnDraw(CDC* pDC);  // ��д�Ի��Ƹ���ͼ
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// ʵ��
public:
	virtual ~CUAV_3D_FCSView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // UAV_3D_FCSView.cpp �еĵ��԰汾
inline CUAV_3D_FCSDoc* CUAV_3D_FCSView::GetDocument() const
   { return reinterpret_cast<CUAV_3D_FCSDoc*>(m_pDocument); }
#endif

