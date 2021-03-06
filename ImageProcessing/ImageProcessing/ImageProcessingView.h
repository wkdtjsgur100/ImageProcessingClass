
// ImageProcessingView.h : CImageProcessingView 클래스의 인터페이스
//

#pragma once


class CImageProcessingView : public CView
{
protected: // serialization에서만 만들어집니다.
	CImageProcessingView();
	DECLARE_DYNCREATE(CImageProcessingView)

// 특성입니다.
public:
	CImageProcessingDoc* GetDocument() const;

// 작업입니다.
public:

// 재정의입니다.
public:
	virtual void OnDraw(CDC* pDC);  // 이 뷰를 그리기 위해 재정의되었습니다.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 구현입니다.
public:
	virtual ~CImageProcessingView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnDownSampling();
	afx_msg void OnUpSampling();
	afx_msg void OnQantization();
	afx_msg void OnSumConstant();
	afx_msg void OnAvgDevConvert();
	afx_msg void OnAndOperate();
	afx_msg void OnNegaTransform();
	afx_msg void OnStressTransform();
	afx_msg void OnMasking();
	afx_msg void OnMedian();
	afx_msg void OnMirrorHor();
	afx_msg void OnRotation();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	bool m_bDrawMode;
	bool m_LineDrawn;
	CPoint m_ptStart;
	CPoint m_ptEnd;
	afx_msg void OnFindChief();
};

#ifndef _DEBUG  // ImageProcessingView.cpp의 디버그 버전
inline CImageProcessingDoc* CImageProcessingView::GetDocument() const
   { return reinterpret_cast<CImageProcessingDoc*>(m_pDocument); }
#endif

