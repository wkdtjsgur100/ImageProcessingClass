#pragma once
#include "afxwin.h"


// CConverterDlg ��ȭ �����Դϴ�.

class CConverterDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CConverterDlg)

public:
	CConverterDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CConverterDlg();

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG5 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	int m_Deviation;
	int m_Avg;
};
