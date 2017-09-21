#pragma once


// CStressTransformDlg 대화 상자입니다.

class CStressTransformDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CStressTransformDlg)

public:
	CStressTransformDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CStressTransformDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG7 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	int m_stressMin;
	int m_stressMax;
};
