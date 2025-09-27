
// ShowThumbImgDlg.cpp : ���� ����
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


// ���� ���α׷� ������ ���Ǵ� CAboutDlg ��ȭ �����Դϴ�.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

// �����Դϴ�.
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


// CShowThumbImgDlg ��ȭ ����



CShowThumbImgDlg::CShowThumbImgDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_SHOWTHUMBIMG_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	// GDI+ �ʱ�ȭ
	GdiplusStartupInput gdiplusStartupInput;
	GdiplusStartup(&m_gdiplusToken, &gdiplusStartupInput, NULL);//ULONG_PTR	m_gdiplusToken(������� �����)
	m_hOrigin = m_hThumbnail = NULL;
}

CShowThumbImgDlg::~CShowThumbImgDlg()
{
	DeleteObject(m_hOrigin);//������ ���� �̹��� �ڵ��� ����
	DeleteObject(m_hThumbnail);//������ ����� �̹��� �ڵ� ����
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


// CShowThumbImgDlg �޽��� ó����

BOOL CShowThumbImgDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// �ý��� �޴��� "����..." �޴� �׸��� �߰��մϴ�.

	// IDM_ABOUTBOX�� �ý��� ��� ������ �־�� �մϴ�.
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

	// �� ��ȭ ������ �������� �����մϴ�.  ���� ���α׷��� �� â�� ��ȭ ���ڰ� �ƴ� ��쿡��
	//  �����ӿ�ũ�� �� �۾��� �ڵ����� �����մϴ�.
	SetIcon(m_hIcon, TRUE);			// ū �������� �����մϴ�.
	SetIcon(m_hIcon, FALSE);		// ���� �������� �����մϴ�.

	// TODO: ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
	//���� �ҷ����⿡�� ������ �̹��� Ȯ���ڸ� �����ֵ��� �Ѵ�
	m_SelFileBtn.EnableFileBrowseButton(_T("�̹��� ����"), _T("Image Files|*.bmp;*.jpg;*.png;*.gif;*.tif||"));
	return TRUE;  // ��Ŀ���� ��Ʈ�ѿ� �������� ������ TRUE�� ��ȯ�մϴ�.
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

// ��ȭ ���ڿ� �ּ�ȭ ���߸� �߰��� ��� �������� �׸�����
//  �Ʒ� �ڵ尡 �ʿ��մϴ�.  ����/�� ���� ����ϴ� MFC ���� ���α׷��� ��쿡��
//  �����ӿ�ũ���� �� �۾��� �ڵ����� �����մϴ�.

void CShowThumbImgDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // �׸��⸦ ���� ����̽� ���ؽ�Ʈ�Դϴ�.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Ŭ���̾�Ʈ �簢������ �������� ����� ����ϴ�.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// �������� �׸��ϴ�.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// ����ڰ� �ּ�ȭ�� â�� ���� ���ȿ� Ŀ���� ǥ�õǵ��� �ý��ۿ���
//  �� �Լ��� ȣ���մϴ�.
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

//�̹����� ��ó ��Ʈ�ѿ� �����ش�
BOOL CShowThumbImgDlg::ShowThumbnailImg(CString strImgPath)
{
	//����� ����ũ���� ����� �� ���� �����
	DeleteObject(m_hOrigin);//������ ���� �̹��� �ڵ��� ����
	DeleteObject(m_hThumbnail);//������ ����� �̹��� �ڵ� ����
	m_hOrigin = m_hThumbnail = NULL;

	CRect rct;
	m_Thumbnail.GetWindowRect(&rct);

	if (rct.Width() < 15 || rct.Height() < 15) //����� ��Ʈ���� ũ�Ⱑ �ʹ� ������ �������� �ʴ´�.
		return FALSE;

	float fRatio = 1.0f;

	int nPreviewWidth = rct.Width() - 5;
	int nPreviewHeight = rct.Height() - 5;

	int nOriginImgWidth = 0; //���� �̹����� �ʺ�
	int nOriginImgHeight = 0;//���� �̹����� ����
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
		//������� ��ó��Ʈ�� ���� ũ�ٸ� ��ó��Ʈ���� ũ�⸸ŭ ����Ѵ�. ��Ҵ� ����� �̹����� ������ �����ϵ��� �Ѵ�.
		nThumbImgWidth = static_cast<UINT>(nOriginImgWidth * fRatio);
		nThumbImgHeight = static_cast<UINT>(nOriginImgHeight * fRatio);
	}
	else
	{
		//������� ��ó��Ʈ���� ũ�⺸�� �۴ٸ� ���� ����� �̹��� ũ�⸦ �״�� ����Ѵ�
		nThumbImgWidth = (int)(nOriginImgWidth*0.99);
		nThumbImgHeight = (int)(nOriginImgHeight*0.99);
	}

	//���ο� ũ��� ������¡�Ѵ�. m_hOrigin, m_hThumbnail �ڵ��� �ٽ� ������ �ʿ䰡 ������ �����Ѵ�
	m_hThumbnail = GetResizeHBITMAP(m_hOrigin, nThumbImgWidth, nThumbImgHeight);
	
	m_Thumbnail.SetBitmap(m_hThumbnail); //��ó��Ʈ��(�̸����� â)�� ��Ʈ�ʿ���

	return TRUE;
}

//�̹����� ũ�⸦ ���Ѵ�
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

//������ hbitmap, ���ϰ���  hbitmap �ڵ��� ����ڰ� Deleteobject ����� �Ѵ�
HBITMAP CShowThumbImgDlg::GetResizeHBITMAP(HBITMAP hBitmap, int nNewWidth, int nNewHeight)
{
	CImageResize imgResize;
	return imgResize.ScaleBitmap(hBitmap, nNewWidth, nNewHeight);
}

//�̹��� ���Ϸ� ���� HBITMAP �ڵ��� ���Ѵ�
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