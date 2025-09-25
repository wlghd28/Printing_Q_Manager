// TestDlg.h : header file
//

#pragma once

#include "SkinDialog.h"
#include "afxwin.h"
#include "afxcmn.h"

#include "SkinButton.h"
#include "TabCtrlEx.h"

// CTestDlg dialog
class CTestDlg : public CSkinDialog
{
// Construction
public:
	CTestDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_TEST_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support

	CImageList *m_pImageList;

	CSkinButton m_btnOk;
	CSkinButton m_btnCancel;

	CTabCtrlEx m_tab1;
	CTabCtrlEx m_tab2;
	CTabCtrlEx m_tab3;
	CTabCtrlEx m_tab4;
	CTabCtrlEx m_tab5;

// Implementation
protected:
	HICON m_hIcon;

	BOOL m_bInitialized;

	void RelocationControls();

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnDestroy();
	DECLARE_MESSAGE_MAP()
};
