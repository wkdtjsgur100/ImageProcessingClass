
// ImageProcessingDoc.cpp : CImageProcessingDoc 클래스의 구현
//

#include "stdafx.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "ImageProcessing.h"
#endif

#include "ImageProcessingDoc.h"
#include "DownSampleDlg.h"
#include "UpSampleDlg.h"
#include "QuantizationDlg.h"
#include "ConstantDlg.h"
#include "ConverterDlg.h"
#include "AndOperateDlg.h"
#include "StressTransformDlg.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CImageProcessingDoc

IMPLEMENT_DYNCREATE(CImageProcessingDoc, CDocument)

BEGIN_MESSAGE_MAP(CImageProcessingDoc, CDocument)
END_MESSAGE_MAP()


// CImageProcessingDoc 생성/소멸

CImageProcessingDoc::CImageProcessingDoc()
	: m_InputImage(NULL)
{
	// TODO: 여기에 일회성 생성 코드를 추가합니다.

}

CImageProcessingDoc::~CImageProcessingDoc()
{
}

BOOL CImageProcessingDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: 여기에 재초기화 코드를 추가합니다.
	// SDI 문서는 이 문서를 다시 사용합니다.

	return TRUE;
}




// CImageProcessingDoc serialization

void CImageProcessingDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: 여기에 저장 코드를 추가합니다.
	}
	else
	{
		// TODO: 여기에 로딩 코드를 추가합니다.
	}
}

#ifdef SHARED_HANDLERS

// 축소판 그림을 지원합니다.
void CImageProcessingDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// 문서의 데이터를 그리려면 이 코드를 수정하십시오.
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// 검색 처리기를 지원합니다.
void CImageProcessingDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// 문서의 데이터에서 검색 콘텐츠를 설정합니다.
	// 콘텐츠 부분은 ";"로 구분되어야 합니다.

	// 예: strSearchContent = _T("point;rectangle;circle;ole object;");
	SetSearchContent(strSearchContent);
}

void CImageProcessingDoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = NULL;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != NULL)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CImageProcessingDoc 진단

#ifdef _DEBUG
void CImageProcessingDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CImageProcessingDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CImageProcessingDoc 명령


BOOL CImageProcessingDoc::OnOpenDocument(LPCTSTR lpszPathName)
{
	if (!CDocument::OnOpenDocument(lpszPathName))
		return FALSE;

	// TODO:  여기에 특수화된 작성 코드를 추가합니다.
	CFile File;

	File.Open(lpszPathName, CFile::modeRead | CFile::typeBinary);

	if (File.GetLength() == 256 * 256) {
		m_height = 256;
		m_width = 256;
	}
	else if (File.GetLength() == 512 * 512) {
		m_height = 512;
		m_width = 512;
	}
	else if (File.GetLength() == 640 * 480) {
		m_height = 480;
		m_width = 640;
	}
	else {
		AfxMessageBox(_T("Not support Image Size"));
		return 0;
	}
	m_size = m_width*m_height;

	m_InputImage = new unsigned char[m_size];

	for (int i = 0; i < m_size; i++)
		m_InputImage[i] = 255;

	File.Read(m_InputImage, m_size);
	File.Close();

	return TRUE;
}


void CImageProcessingDoc::OnDownSampling()
{
	int i, j;
	CDownSampleDlg dlg;

	if (dlg.DoModal() == IDOK)
	{
		m_Re_height = m_height / dlg.m_DownSampleRate;
		m_Re_width = m_width / dlg.m_DownSampleRate;

		m_Re_size = m_Re_height * m_Re_width;

		m_OutputImage = new unsigned char[m_Re_size];

		for (i = 0;i < m_Re_height; i++) {
			for (j = 0;j < m_Re_width; j++) {
				m_OutputImage[i*m_Re_width + j] = m_InputImage[(i*dlg.m_DownSampleRate*m_width) + dlg.m_DownSampleRate*j];
			}
		}
	}
}


void CImageProcessingDoc::OnUpSampling()
{
	int i, j;

	CUpSampleDlg dlg;

	if (dlg.DoModal() == IDOK) {
		m_Re_height = m_height* dlg.m_UpSampleRate;
		m_Re_width = m_width * dlg.m_UpSampleRate;
		m_Re_size = m_Re_height* m_Re_width;

		m_OutputImage = new unsigned char[m_Re_size];

		/* Nearest 보간
		
		for (i = 0;i < m_Re_height;i++) {
			for (j = 0;j < m_Re_width;j++) {
				m_OutputImage[i*m_Re_width + j] = m_InputImage[(i/dlg.m_UpSampleRate)*m_width + (j/dlg.m_UpSampleRate)];
			}
		}*/

		/*
		양선형 보간
		*/
		for (i = 0;i < m_Re_height;i++) {
			for (j = 0;j < m_Re_width;j++) {
				double r_H = (double)i / dlg.m_UpSampleRate;
				double r_W = (double)j / dlg.m_UpSampleRate;

				int i_H = (int)floor(r_H);
				int i_W = (int)floor(r_W);

				double s_H = r_H - i_H;
				double s_W = r_W - i_W;

				if (i_H < 0 || i_H >= (m_height - 1) || i_W < 0 || i_W >= (m_width - 1))
				{
					m_OutputImage[i*m_Re_width + j] = 255;
				}
				else
				{
					double C1 = (double)m_InputImage[i_H*m_width + i_W];
					double C2 = (double)m_InputImage[i_H*m_width + i_W+1];
					double C3 = (double)m_InputImage[(i_H+1)*m_width + i_W+1];
					double C4 = (double)m_InputImage[(i_H+1)*m_width + i_W];

					unsigned char newValue = (unsigned char)(C1*(1 - s_H)*(1 - s_W) + C2*s_W*(1 - s_H) + C3*s_W*s_H + C4*(1 - s_W)*s_H);

					m_OutputImage[i*m_Re_width + j] = newValue;
				}
			}
		}
	}
}


void CImageProcessingDoc::OnQuantization()
{
	CQuantizationDlg dlg;
	m_Re_height = m_height;
	m_Re_width = m_width;

	m_Re_size = m_Re_height * m_Re_width;

	m_OutputImage = new unsigned char[m_Re_size];

	if (dlg.DoModal() == IDOK)
	{
		int i, sb;
		sb = 8 - dlg.m_QuantBit;

		for (i = 0; i < m_size; i++) {
			m_OutputImage[i] = m_InputImage[i] >> sb << sb;
		}
	}
}


void CImageProcessingDoc::OnSumConstant()
{
	CConstantDlg dlg;

	int i;
	m_Re_height = m_height;
	m_Re_width = m_width;
	m_Re_size = m_Re_size = m_Re_height*m_Re_width;

	m_OutputImage = new unsigned char[m_Re_size];

	if (dlg.DoModal() == IDOK) {
		for (i = 0; i < m_size; i++) {
			if (m_InputImage[i] + dlg.m_Constant >= 255)
				m_OutputImage[i] = 255;
			else
				m_OutputImage[i] = (unsigned char)(m_InputImage[i] + dlg.m_Constant);
		}
	}
}


void CImageProcessingDoc::OnAvgDevConvert()
{
	CConverterDlg dlg;

	int i;

	double input_avg; // 입력 영상의 평균
	double input_deviation; //입력 영상의 표준편차


	m_Re_height = m_height;
	m_Re_width = m_width;
	m_Re_size = m_Re_size = m_Re_height*m_Re_width;

	m_OutputImage = new unsigned char[m_Re_size];

	if (dlg.DoModal() == IDOK) {
		unsigned long long sigma = 0;

		for (i = 0; i < m_size; i++)
			sigma += m_InputImage[i];

		input_avg = sigma / (double)m_size;

		for (i = 0; i < m_size; i++)
			sigma += (m_InputImage[i] - input_avg)*(m_InputImage[i] - input_avg);

		input_deviation = sqrtl(sigma / (double)m_size);

		for (i = 0; i < m_size; i++) {
			int z = (dlg.m_Deviation / input_deviation)*(m_InputImage[i] - input_avg) + dlg.m_Avg;
			if (z >= 255)
				m_OutputImage[i] = 255;
			else
				m_OutputImage[i] = (unsigned char)z;
		}
	}
}


void CImageProcessingDoc::OnAndOperate()
{
	CAndOperateDlg dlg;
	int i;
	m_Re_height = m_height;
	m_Re_width = m_width;

	m_Re_size = m_Re_height * m_Re_width;

	m_OutputImage = new unsigned char[m_Re_size];

	if (dlg.DoModal() == IDOK) {
		for (i = 0; i < m_size; i++) {
			if ((m_InputImage[i] & (unsigned char)dlg.m_AndValue) >= 255){
				m_OutputImage[i] = 255;
			}
			else if ((m_InputImage[i] & (unsigned char)dlg.m_AndValue) < 0) {
				m_OutputImage[i] = 0;
			}
			else {
				m_OutputImage[i] = (m_InputImage[i] & (unsigned char)dlg.m_AndValue);
			}
		}
	}
}


void CImageProcessingDoc::OnNegaTransform()
{
	int i;
	m_Re_height = m_height;
	m_Re_width = m_width;

	m_Re_size = m_Re_height * m_Re_width;

	m_OutputImage = new unsigned char[m_Re_size];
	
	for (i = 0; i < m_size; i++)
		m_OutputImage[i] = 255 - m_InputImage[i];
}


void CImageProcessingDoc::OnStressTransform()
{
	CStressTransformDlg dlg;
	int i;
	m_Re_height = m_height;
	m_Re_width = m_width;

	m_Re_size = m_Re_height * m_Re_width;

	m_OutputImage = new unsigned char[m_Re_size];

	if (dlg.DoModal() == IDOK) {
		for (i = 0; i < m_size; i++) {
			if (m_InputImage[i] >= dlg.m_stressMin && m_InputImage[i] <= dlg.m_stressMax)
				m_OutputImage[i] = 255;
			else
				m_OutputImage[i] = m_InputImage[i];
		}
	}
}


void CImageProcessingDoc::OnMasking()
{
	int i, j;
	double Mask[3][3] = {
		{0., 1., 0.},
		{1., -4., 1.},
		{0., 1., 0.}
	};

	m_Re_height = m_height;
	m_Re_width = m_width;
	m_Re_size = m_Re_height* m_Re_width;
	m_OutputImage = new unsigned char[m_Re_size];

	//m_tempImage = OnMaskProcess(m_InputImage, Mask);
	m_tempImage = OnMedianProcess(m_InputImage,m_Re_width,m_Re_height);

	for(i=0;i<m_Re_height; i++)
		for (j = 0; j < m_Re_width; j++)
		{
			if (m_tempImage[i][j] > 255.)
				m_tempImage[i][j] = 255.;
			if (m_tempImage[i][j] < 0.)
				m_tempImage[i][j] = 0.;
		}

	m_tempImage = OnScale(m_tempImage, m_Re_height, m_Re_width);

	for (i = 0; i < m_Re_height; i++)
		for (j = 0; j < m_Re_width; j++)
			m_OutputImage[i*m_Re_width + j] = (unsigned char)m_tempImage[i][j];
}

double** CImageProcessingDoc::OnMaskProcess(unsigned char* Target, double Mask[3][3])
{
	int i, j, n, m;
	double **tempInputImage, **tempOutputImage, S = 0.0;

	tempInputImage = Image2DMem(m_height + 2, m_width + 2);
	tempOutputImage = Image2DMem(m_height, m_width);

	for (i = 0; i < m_height; i++)
		for (j = 0; j < m_width; j++)
			tempInputImage[i + 1][j + 1] = (double)Target[i*m_width + j];

	for(i=0;i<m_height;i++)
		for (j = 0; j < m_width; j++)
		{
			for (n = 0; n < 3; n++)
				for (m = 0; m < 3; m++)
					S += Mask[n][m] * tempInputImage[i + n][j + m];
			
			tempOutputImage[i][j] = S;
			S = 0.0;
		}

	return tempOutputImage;
}


double** CImageProcessingDoc::OnScale(double** Target, int height, int width)
{
	int i, j;
	double min, max;
	min = max = Target[0][0];

	for (i = 0; i < height; i++)
		for (j = 0; j < width; j++)
		{
			if (Target[i][j] < min)
				min = Target[i][j];
			if (Target[i][j] > max)
				max = Target[i][j];
		}

	max = max - min;

	for (i = 0; i < height; i++)
		for (j = 0; j < width; j++)
			Target[i][j] = (Target[i][j] - min)*(255 / max);

	return Target;
}


double** CImageProcessingDoc::Image2DMem(int height, int width)
{
	double** temp;
	int i, j;
	temp = new double*[height];
	
	for (i = 0; i < height; i++)
		temp[i] = new double[width];

	for (i = 0; i < height; i++)
		for (j = 0; j < width; j++)
			temp[i][j] = 0.0;

	return temp;
}
void CImageProcessingDoc::bubbleSort(double* arr, int n)
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < i; j++)
		{
			if (arr[i] < arr[j])
			{
				int t = arr[i];
				arr[i] = arr[j];
				arr[j] = t;
			}
		}
	}
}
double** CImageProcessingDoc::OnMedianProcess(unsigned char* Target, int width, int height)
{
	int i, j, n, m;
	double **tempOutputImage;

	tempOutputImage = Image2DMem(height, width);
	for (i = 0; i<height; i++)
		for (j = 0; j < width; j++)
		{
			double arr[9] = { 0., };
			for (n = 0; n < 3; n++)
				for (m = 0; m < 3; m++)
					arr[3*n+m] = Target[(i + n)*width + (j + m)];

			bubbleSort(arr, 9);
			tempOutputImage[i][j] = arr[4];
		}
	return tempOutputImage;
}


void CImageProcessingDoc::OnMedian()
{

}


void CImageProcessingDoc::OnMirrorHor()
{
	int i, j;
	double **tempArray;

	m_Re_height = m_height;
	m_Re_width = m_width;
	m_Re_size = m_Re_height* m_Re_width;
	m_OutputImage = new unsigned char[m_Re_size];

	m_tempImage = Image2DMem(m_height, m_width);
	tempArray = Image2DMem(m_Re_height, m_Re_width);

	for (i = 0;i < m_height; i++) {
		for (j = 0;j < m_width; j++) {
			m_tempImage[i][j] = (double)m_InputImage[i*m_width + j];
		}
	}

	for (i = 0;i < m_Re_height; i++) {
		for (j = 0;j < m_Re_width;j++) {
			int x = -j + m_Re_width - 1;
			int y = i;

			if (x<0 || x > m_width || y<0 || y>m_height)
				tempArray[i][j] = 0;
			else
				tempArray[i][j] = m_tempImage[y][x];
		}
	}

	for (i = 0;i < m_Re_height; i++) {
		for (j = 0;j < m_Re_width;j++) {
			m_OutputImage[i*m_Re_width + j] = (unsigned char)tempArray[i][j];
		}
	}
	delete[] m_tempImage;
	delete[] tempArray;
}



void CImageProcessingDoc::OnMeanSub()
{
	int i, j, CH, CW, newH, newW, degree = 45;
	double Radian, PI, **tempArray, Value;
	
	m_Re_height = m_height;
	m_Re_width = m_width;
	m_Re_size = m_Re_height* m_Re_width;
	m_OutputImage = new unsigned char[m_Re_size];

	PI = 3.14159265358979;

	Radian = (double)degree*PI / 180.0;
	CH = m_height / 2;
	CW = m_width / 2;

	m_tempImage = Image2DMem(m_height, m_width);
	tempArray = Image2DMem(m_Re_height, m_Re_width);

	for (i = 0;i < m_height; i++) {
		for (j = 0;j < m_width; j++) {
			m_tempImage[i][j] = (double)m_InputImage[i*m_width + j];
		}
	}
	for (i = 0;i < m_height;i++) {
		for (j = 0;j < m_width;j++) {
			newH = (int)((i - CH)*cos(Radian) - (j - CW)*sin(Radian) + CH);
			newW = (int)((i - CH)*sin(Radian) + (j - CW)*sin(Radian) + CW);

			if (newH < 0 || newH >= m_height)
				Value = 0;
			else if (newW < 0 || newW >= m_width)
				Value = 0;
			else
				Value = m_tempImage[newH][newW];

			tempArray[i][j] = Value;
		}
	}
	for (i = 0;i < m_Re_height; i++) {
		for (j = 0;j < m_Re_width;j++) {
			m_OutputImage[i*m_Re_width + j] = (unsigned char)tempArray[i][j];
		}
	}
	delete[] m_tempImage;
	delete[] tempArray;
}


void CImageProcessingDoc::OnFindChief()
{
	int i, j, CH, CW, newH, newW, degree = 45;
	double Radian, PI, **tempArray, Value;

	m_Re_height = m_height;
	m_Re_width = m_width;
	m_Re_size = m_Re_height* m_Re_width;
	m_OutputImage = new unsigned char[m_Re_size];

	PI = 3.14159265358979;

	Radian = (double)degree*PI / 180.0;
	CH = m_height / 2;
	CW = m_width / 2;

	m_tempImage = Image2DMem(m_height, m_width);
	tempArray = Image2DMem(m_Re_height, m_Re_width);

	for (i = 0;i < m_height; i++) {
		for (j = 0;j < m_width; j++) {
			m_tempImage[i][j] = (double)m_InputImage[i*m_width + j];
		}
	}
	for (i = 0;i < m_height;i++) {
		for (j = 0;j < m_width;j++) {
			double d = sqrtl((CH - i)*(CH - i) + (CW - j)*(CW - j));
			Radian = -(d * PI / 180.0);
			newH = (int)((i - CH)*cos(Radian) - (j - CW)*sin(Radian) + CH);
			newW = (int)((i - CH)*sin(Radian) + (j - CW)*sin(Radian) + CW);

			if (newH < 0 || newH >= m_height)
				Value = 0;
			else if (newW < 0 || newW >= m_width)
				Value = 0;
			else
				Value = m_tempImage[newH][newW];

			tempArray[i][j] = Value;
		}
	}
	for (i = 0;i < m_Re_height; i++) {
		for (j = 0;j < m_Re_width;j++) {
			m_OutputImage[i*m_Re_width + j] = (unsigned char)tempArray[i][j];
		}
	}
	delete[] m_tempImage;
	delete[] tempArray;
}


void CImageProcessingDoc::OnRotateByPoint(CPoint d)
{
	double D = sqrtl(d.x*d.x + d.y*d.y);
	double cost = d.x / D;
	double sint = d.y / D;

	int i, j, CH, CW, newH, newW, degree = 45;
	double Radian, PI, **tempArray, Value;

	m_Re_height = m_height;
	m_Re_width = m_width;
	m_Re_size = m_Re_height* m_Re_width;
	m_OutputImage = new unsigned char[m_Re_size];

	PI = 3.14159265358979;

	Radian = (double)degree*PI / 180.0;
	CH = m_height / 2;
	CW = m_width / 2;

	m_tempImage = Image2DMem(m_height, m_width);
	tempArray = Image2DMem(m_Re_height, m_Re_width);

	for (i = 0;i < m_height; i++) {
		for (j = 0;j < m_width; j++) {
			m_tempImage[i][j] = (double)m_InputImage[i*m_width + j];
		}
	}
	for (i = 0;i < m_height;i++) {
		for (j = 0;j < m_width;j++) {
			double d = sqrtl((CH - i)*(CH - i) + (CW - j)*(CW - j));

			newH = (int)(sint*(j-CW)+cost*(i-CH)+CH);
			newW = (int)(cost*(j-CW)-sint*(i-CH)+CW);

			if (newH < 0 || newH >= m_height)
				Value = 0;
			else if (newW < 0 || newW >= m_width)
				Value = 0;
			else
				Value = m_tempImage[newH][newW];

			tempArray[i][j] = Value;
		}
	}
	for (i = 0;i < m_Re_height; i++) {
		for (j = 0;j < m_Re_width;j++) {
			m_OutputImage[i*m_Re_width + j] = (unsigned char)tempArray[i][j];
		}
	}
	delete[] m_tempImage;
	delete[] tempArray;
}
