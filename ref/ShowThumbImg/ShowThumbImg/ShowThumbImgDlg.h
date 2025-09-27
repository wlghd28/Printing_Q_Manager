
// ShowThumbImgDlg.h : ��� ����
//

#pragma once
#include "afxeditbrowsectrl.h"
#include "afxwin.h"


// CShowThumbImgDlg ��ȭ ����
class CShowThumbImgDlg : public CDialogEx
{
// �����Դϴ�.
public:
	CShowThumbImgDlg(CWnd* pParent = NULL);	// ǥ�� �������Դϴ�.
	~CShowThumbImgDlg();

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SHOWTHUMBIMG_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV �����Դϴ�.


// �����Դϴ�.
protected:
	HICON m_hIcon;

	// ������ �޽��� �� �Լ�
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
private:
	// ���ϼ��� ��Ʈ��
	CMFCEditBrowseCtrl m_SelFileBtn;
	// �̹��� �̸�����
	CStatic m_Thumbnail;
	ULONG_PTR	m_gdiplusToken;//gdi+ ���
	HBITMAP m_hOrigin, m_hThumbnail; //�����̹���, ����� �̹����� �ڵ�
public:
	BOOL ShowThumbnailImg(CString strImgPath);
	BOOL GetImgSize(HBITMAP hBitmap, int& nWidth, int& nHeight);
	HBITMAP GetResizeHBITMAP(HBITMAP hBitmap, int nNewWidth, int nNewHeight);
	HBITMAP GetHBITMAP(LPCTSTR lpszFile);
public:
	afx_msg void OnEnChangeSelFileBtn();
};
