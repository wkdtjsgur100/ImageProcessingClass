// AndOperateDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "ImageProcessing.h"
#include "AndOperateDlg.h"
#include "afxdialogex.h"


// CAndOperateDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CAndOperateDlg, CDialogEx)

CAndOperateDlg::CAndOperateDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG6, pParent)
	, m_AndValue(0)
{

}

CAndOperateDlg::~CAndOperateDlg()
{
}

void CAndOperateDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_AndValue);
}


BEGIN_MESSAGE_MAP(CAndOperateDlg, CDialogEx)
END_MESSAGE_MAP()


// CAndOperateDlg 메시지 처리기입니다.
