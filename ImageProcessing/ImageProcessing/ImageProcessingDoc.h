
// ImageProcessingDoc.h : CImageProcessingDoc 클래스의 인터페이스
//


#pragma once


class CImageProcessingDoc : public CDocument
{
protected: // serialization에서만 만들어집니다.
	CImageProcessingDoc();
	DECLARE_DYNCREATE(CImageProcessingDoc)

// 특성입니다.
public:

// 작업입니다.
public:

// 재정의입니다.
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// 구현입니다.
public:
	virtual ~CImageProcessingDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// 검색 처리기에 대한 검색 콘텐츠를 설정하는 도우미 함수
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
public:
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
	unsigned char*m_InputImage;
	unsigned char* m_OutputImage;
	double** m_tempImage;
	
	int m_Re_width;
	int m_Re_height;
	int m_Re_size;

	int m_width;
	int m_height;
	int m_size;
	
	void OnDownSampling();
	void OnUpSampling();
	void OnQuantization();
	void OnSumConstant();
	void OnAvgDevConvert();
	void OnAndOperate();
	void OnNegaTransform();
	void OnStressTransform();
	void OnMasking();

	double** OnMaskProcess(unsigned char* Target, double Mask[3][3]);
	double** OnScale(double** Target, int height, int width);
	double** Image2DMem(int height, int width);
	void bubbleSort(double* arr,int n);
	double** OnMedianProcess(unsigned char* Target, int width, int height);
	void OnMedian();
	void OnMirrorHor();
	void OnMeanSub();
	void OnFindChief();
	void OnRotateByPoint(CPoint d);
};
