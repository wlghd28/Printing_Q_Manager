
// ShowThumbImgDlg.h : 헤더 파일
//

#pragma once
#include "afxeditbrowsectrl.h"
#include "afxwin.h"


// CShowThumbImgDlg 대화 상자
class CShowThumbImgDlg : public CDialogEx
{
// 생성입니다.
public:
	CShowThumbImgDlg(CWnd* pParent = NULL);	// 표준 생성자입니다.
	~CShowThumbImgDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SHOWTHUMBIMG_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
private:
	// 파일선택 컨트롤
	CMFCEditBrowseCtrl m_SelFileBtn;
	// 이미지 미리보기
	CStatic m_Thumbnail;
	ULONG_PTR	m_gdiplusToken;//gdi+ 사용
	HBITMAP m_hOrigin, m_hThumbnail; //원본이미지, 썸네일 이미지의 핸들
public:
	BOOL ShowThumbnailImg(CString strImgPath);
	BOOL GetImgSize(HBITMAP hBitmap, int& nWidth, int& nHeight);
	HBITMAP GetResizeHBITMAP(HBITMAP hBitmap, int nNewWidth, int nNewHeight);
	HBITMAP GetHBITMAP(LPCTSTR lpszFile);
public:
	afx_msg void OnEnChangeSelFileBtn();
};
