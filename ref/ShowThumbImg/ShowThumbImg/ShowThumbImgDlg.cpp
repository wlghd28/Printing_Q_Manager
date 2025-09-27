
// ShowThumbImgDlg.cpp : 구현 파일
//

#include "stdafx.h"
#include "ShowThumbImg.h"
#include "ShowThumbImgDlg.h"
#include "afxdialogex.h"
#include <gdiplus.h> //gdi+
#include "ImageResize.hpp"

#pragma comment(lib, "gdiplus.lib") //gdi+
using namespace Gdiplus;
using namespace std;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CShowThumbImgDlg 대화 상자



CShowThumbImgDlg::CShowThumbImgDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_SHOWTHUMBIMG_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	// GDI+ 초기화
	GdiplusStartupInput gdiplusStartupInput;
	GdiplusStartup(&m_gdiplusToken, &gdiplusStartupInput, NULL);//ULONG_PTR	m_gdiplusToken(헤더에서 선언됨)
	m_hOrigin = m_hThumbnail = NULL;
}

CShowThumbImgDlg::~CShowThumbImgDlg()
{
	DeleteObject(m_hOrigin);//기존의 원본 이미지 핸들은 삭제
	DeleteObject(m_hThumbnail);//기존의 썸네일 이미지 핸들 삭제
	m_hOrigin = m_hThumbnail = NULL;

	GdiplusShutdown(m_gdiplusToken);
}

void CShowThumbImgDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SEL_FILE_BTN, m_SelFileBtn);
	DDX_Control(pDX, IDC_PREVIEW_BITMAP, m_Thumbnail);
}

BEGIN_MESSAGE_MAP(CShowThumbImgDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_EN_CHANGE(IDC_SEL_FILE_BTN, &CShowThumbImgDlg::OnEnChangeSelFileBtn)
END_MESSAGE_MAP()


// CShowThumbImgDlg 메시지 처리기

BOOL CShowThumbImgDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.
	//파일 불러오기에서 정해진 이미지 확장자만 보여주도록 한다
	m_SelFileBtn.EnableFileBrowseButton(_T("이미지 파일"), _T("Image Files|*.bmp;*.jpg;*.png;*.gif;*.tif||"));
	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CShowThumbImgDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 응용 프로그램의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CShowThumbImgDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CShowThumbImgDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CShowThumbImgDlg::OnEnChangeSelFileBtn()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
	CString strImgPath;
	m_SelFileBtn.GetWindowText(strImgPath);
	ShowThumbnailImg(strImgPath);
}

//이미지를 픽처 컨트롤에 보여준다
BOOL CShowThumbImgDlg::ShowThumbnailImg(CString strImgPath)
{
	//썸네일 원본크기대로 출력할 수 없는 경우라면
	DeleteObject(m_hOrigin);//기존의 원본 이미지 핸들은 삭제
	DeleteObject(m_hThumbnail);//기존의 썸네일 이미지 핸들 삭제
	m_hOrigin = m_hThumbnail = NULL;

	CRect rct;
	m_Thumbnail.GetWindowRect(&rct);

	if (rct.Width() < 15 || rct.Height() < 15) //썸네일 컨트롤의 크기가 너무 작으면 보여주지 않는다.
		return FALSE;

	float fRatio = 1.0f;

	int nPreviewWidth = rct.Width() - 5;
	int nPreviewHeight = rct.Height() - 5;

	int nOriginImgWidth = 0; //원본 이미지의 너비
	int nOriginImgHeight = 0;//원본 이미지의 높이
	m_hOrigin = GetHBITMAP(strImgPath);
	if (!m_hOrigin)
		return FALSE;

	if (!GetImgSize(m_hOrigin, nOriginImgWidth, nOriginImgHeight))
	{
		DeleteObject(m_hOrigin);
		m_hOrigin = NULL;
		return FALSE;
	}

	int nThumbImgWidth = 0, nThumbImgHeight = 0;

	fRatio = min((float)nPreviewWidth / (float)nOriginImgWidth, (float)nPreviewHeight / (float)nOriginImgHeight);
	if (fRatio < 1)
	{
		//썸네일이 픽처컨트롤 보다 크다면 픽처컨트롤의 크기만큼 축소한다. 축소는 썸네일 이미지의 비율을 유지하도록 한다.
		nThumbImgWidth = static_cast<UINT>(nOriginImgWidth * fRatio);
		nThumbImgHeight = static_cast<UINT>(nOriginImgHeight * fRatio);
	}
	else
	{
		//썸네일이 픽처컨트롤의 크기보다 작다면 원본 썸네일 이미지 크기를 그대로 출력한다
		nThumbImgWidth = (int)(nOriginImgWidth*0.99);
		nThumbImgHeight = (int)(nOriginImgHeight*0.99);
	}

	//새로운 크기로 리사이징한다. m_hOrigin, m_hThumbnail 핸들은 다시 생성할 필요가 있을때 삭제한다
	m_hThumbnail = GetResizeHBITMAP(m_hOrigin, nThumbImgWidth, nThumbImgHeight);
	
	m_Thumbnail.SetBitmap(m_hThumbnail); //픽처컨트롤(미리보기 창)에 비트맵연결

	return TRUE;
}

//이미지의 크기를 구한다
BOOL CShowThumbImgDlg::GetImgSize(HBITMAP hBitmap, int& nWidth, int& nHeight)
{
	nWidth = nHeight = 0;
	if (!hBitmap)
		return FALSE;

	BITMAP bit;
	if (!GetObject(hBitmap, sizeof(BITMAP), &bit))
		return FALSE;

	nWidth = bit.bmWidth;
	nHeight = bit.bmHeight;
	
	return TRUE;
}

//인자의 hbitmap, 리턴값의  hbitmap 핸들은 사용자가 Deleteobject 해줘야 한다
HBITMAP CShowThumbImgDlg::GetResizeHBITMAP(HBITMAP hBitmap, int nNewWidth, int nNewHeight)
{
	CImageResize imgResize;
	return imgResize.ScaleBitmap(hBitmap, nNewWidth, nNewHeight);
}

//이미지 파일로 부터 HBITMAP 핸들을 구한다
HBITMAP CShowThumbImgDlg::GetHBITMAP(LPCTSTR lpszFile)
{
	HBITMAP hBitmap = NULL;
	Gdiplus::Bitmap* pBmp = ::new Bitmap(lpszFile);
	if (!pBmp)
		return NULL;

	pBmp->GetHBITMAP(RGB(255, 255, 255), &hBitmap);

	::delete pBmp;

	return hBitmap;
}