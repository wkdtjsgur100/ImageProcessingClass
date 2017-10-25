
// ImageProcessingDoc.h : CImageProcessingDoc Ŭ������ �������̽�
//


#pragma once


class CImageProcessingDoc : public CDocument
{
protected: // serialization������ ��������ϴ�.
	CImageProcessingDoc();
	DECLARE_DYNCREATE(CImageProcessingDoc)

// Ư���Դϴ�.
public:

// �۾��Դϴ�.
public:

// �������Դϴ�.
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// �����Դϴ�.
public:
	virtual ~CImageProcessingDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ������ �޽��� �� �Լ�
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// �˻� ó���⿡ ���� �˻� �������� �����ϴ� ����� �Լ�
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
};
