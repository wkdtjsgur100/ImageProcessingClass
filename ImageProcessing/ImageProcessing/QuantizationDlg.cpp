// QuantizationDlg.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "ImageProcessing.h"
#include "QuantizationDlg.h"
#include "afxdialogex.h"


// CQuantizationDlg ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CQuantizationDlg, CDialogEx)

CQuantizationDlg::CQuantizationDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG3, pParent)
	, m_QuantBit(0)
{

}

CQuantizationDlg::~CQuantizationDlg()
{
}

void CQuantizationDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_QuantBit);
	DDV_MinMaxInt(pDX, m_QuantBit, 1, 8);
}


BEGIN_MESSAGE_MAP(CQuantizationDlg, CDialogEx)
END_MESSAGE_MAP()


// CQuantizationDlg �޽��� ó�����Դϴ�.
