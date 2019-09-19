
// GUI-1Dlg.h : header file
//

#pragma once


// CGUI1Dlg dialog
class CGUI1Dlg : public CDialogEx
{
// Construction
public:
	CGUI1Dlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_GUI1_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedbtn2d();
	afx_msg void OnBnClickedButton2();
//	afx_msg void OnEnChangetxtinput2();
//	afx_msg void OnEnUpdatetxtinput2();
//	afx_msg void OnEnKillfocustxtinput2();
//	afx_msg void OnEnUpdatetxtinput2();
	afx_msg void OnEnChangetxtinput2();
	afx_msg void OnBnClickedbtntriangular2d();
	afx_msg void OnBnClickedbtnsquareev2d();
	afx_msg void OnBnClickedbtntriangularev2d();
	afx_msg void OnBnClickedbtntriangularv2d2();
	afx_msg void OnBnClickedbtnsquarev2d2();
	afx_msg void OnEnChangetxtinput();
	afx_msg void OnEnChangetxtinput3();
	afx_msg void OnEnKillfocustxtinput();
	afx_msg void OnEnKillfocustxtinput3();
};
