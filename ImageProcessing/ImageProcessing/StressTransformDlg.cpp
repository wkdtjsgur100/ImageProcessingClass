// StressTransformDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "ImageProcessing.h"
#include "StressTransformDlg.h"
#include "afxdialogex.h"


// CStressTransformDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CStressTransformDlg, CDialogEx)

CStressTransformDlg::CStressTransformDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG7, pParent)
	, m_stressMin(0)
	, m_stressMax(0)
{

}

CStressTransformDlg::~CStressTransformDlg()
{
}

void CStressTransformDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_stressMin);
	DDX_Text(pDX, IDC_EDIT2, m_stressMax);
}


BEGIN_MESSAGE_MAP(CStressTransformDlg, CDialogEx)
END_MESSAGE_MAP()


// CStressTransformDlg 메시지 처리기입니다.
