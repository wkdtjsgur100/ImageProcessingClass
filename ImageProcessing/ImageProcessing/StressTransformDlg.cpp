// StressTransformDlg.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "ImageProcessing.h"
#include "StressTransformDlg.h"
#include "afxdialogex.h"


// CStressTransformDlg ��ȭ �����Դϴ�.

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


// CStressTransformDlg �޽��� ó�����Դϴ�.
