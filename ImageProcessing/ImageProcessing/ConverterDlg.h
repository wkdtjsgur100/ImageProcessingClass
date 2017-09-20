#pragma once
#include "afxwin.h"


// CConverterDlg 대화 상자입니다.

class CConverterDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CConverterDlg)

public:
	CConverterDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CConverterDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG5 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	int m_Deviation;
	int m_Avg;
};
