// ConverterDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "ImageProcessing.h"
#include "ConverterDlg.h"
#include "afxdialogex.h"


// CConverterDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CConverterDlg, CDialogEx)

CConverterDlg::CConverterDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG5, pParent)
	, m_Deviation(0)
	, m_Avg(0)
{

}

CConverterDlg::~CConverterDlg()
{
}

void CConverterDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT2, m_Deviation);
	DDX_Text(pDX, IDC_EDIT1, m_Avg);
}


BEGIN_MESSAGE_MAP(CConverterDlg, CDialogEx)
END_MESSAGE_MAP()


// CConverterDlg 메시지 처리기입니다.
