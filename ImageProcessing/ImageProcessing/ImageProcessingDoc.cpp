
// ImageProcessingDoc.cpp : CImageProcessingDoc Ŭ������ ����
//

#include "stdafx.h"
// SHARED_HANDLERS�� �̸� ����, ����� �׸� �� �˻� ���� ó���⸦ �����ϴ� ATL ������Ʈ���� ������ �� ������
// �ش� ������Ʈ�� ���� �ڵ带 �����ϵ��� �� �ݴϴ�.
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


// CImageProcessingDoc ����/�Ҹ�

CImageProcessingDoc::CImageProcessingDoc()
	: m_InputImage(NULL)
{
	// TODO: ���⿡ ��ȸ�� ���� �ڵ带 �߰��մϴ�.

}

CImageProcessingDoc::~CImageProcessingDoc()
{
}

BOOL CImageProcessingDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: ���⿡ ���ʱ�ȭ �ڵ带 �߰��մϴ�.
	// SDI ������ �� ������ �ٽ� ����մϴ�.

	return TRUE;
}




// CImageProcessingDoc serialization

void CImageProcessingDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: ���⿡ ���� �ڵ带 �߰��մϴ�.
	}
	else
	{
		// TODO: ���⿡ �ε� �ڵ带 �߰��մϴ�.
	}
}

#ifdef SHARED_HANDLERS

// ����� �׸��� �����մϴ�.
void CImageProcessingDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// ������ �����͸� �׸����� �� �ڵ带 �����Ͻʽÿ�.
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

// �˻� ó���⸦ �����մϴ�.
void CImageProcessingDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// ������ �����Ϳ��� �˻� �������� �����մϴ�.
	// ������ �κ��� ";"�� ���еǾ�� �մϴ�.

	// ��: strSearchContent = _T("point;rectangle;circle;ole object;");
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

// CImageProcessingDoc ����

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


// CImageProcessingDoc ���


BOOL CImageProcessingDoc::OnOpenDocument(LPCTSTR lpszPathName)
{
	if (!CDocument::OnOpenDocument(lpszPathName))
		return FALSE;

	// TODO:  ���⿡ Ư��ȭ�� �ۼ� �ڵ带 �߰��մϴ�.
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

		for (i = 0; i < m_Re_size; i++)
			m_OutputImage[i] = 0;

		for (i = 0;i < m_height;i++) {
			for (j = 0;j < m_width;j++) {
				m_OutputImage[i*dlg.m_UpSampleRate*m_Re_width + dlg.m_UpSampleRate*j] = m_InputImage[i*m_width + j];
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

	double input_avg; // �Է� ������ ���
	double input_deviation; //�Է� ������ ǥ������


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
