// TestDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Test.h"
#include "TestDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CTestDlg dialog

#define TAB_HEADER_HEIGHT		24

CTestDlg::CTestDlg(CWnd* pParent /*=NULL*/)
	: CSkinDialog(CTestDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	m_bInitialized = FALSE;

	m_pImageList = NULL;
}

void CTestDlg::DoDataExchange(CDataExchange* pDX)
{
	CSkinDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDOK, m_btnOk);
	DDX_Control(pDX, IDCANCEL, m_btnCancel);
	DDX_Control(pDX, IDC_TAB1, m_tab1);
	DDX_Control(pDX, IDC_TAB2, m_tab2);
	DDX_Control(pDX, IDC_TAB3, m_tab3);
	DDX_Control(pDX, IDC_TAB4, m_tab4);
	DDX_Control(pDX, IDC_TAB5, m_tab5);

}

BEGIN_MESSAGE_MAP(CTestDlg, CSkinDialog)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_SIZE()
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP	
END_MESSAGE_MAP()


// CTestDlg message handlers

BOOL CTestDlg::OnInitDialog()
{
	CSkinDialog::OnInitDialog();

#if 0
	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
#else
	if( !m_bInitialized )
	{
		m_bInitialized = TRUE;

		// Ok Button
		m_btnOk.SetBitmaps(Global.GetBitmap(IDX_BMP_BTN_BASE), Global.GetRGB(IDX_RGB_MASK));
		m_btnOk.SetIcon(Global.GetIcon(IDX_ICON_OK, ICON16), NULL, 5);

		// Cancel Button
		m_btnCancel.SetBitmaps(Global.GetBitmap(IDX_BMP_BTN_BASE), Global.GetRGB(IDX_RGB_MASK));
		m_btnCancel.SetIcon(Global.GetIcon(IDX_ICON_CANCEL, ICON16), NULL, 5);

		// Image List
		m_pImageList = new CImageList();		
		if(!m_pImageList->Create( 16, 16, ILC_COLOR32, 0, 1))
		{
			delete m_pImageList;
			m_pImageList = NULL;
		}
		else 
		{
			m_pImageList->Add(Global.GetIcon(IDX_ICON_HOME,ICON16));
			m_pImageList->Add(Global.GetIcon(IDX_ICON_FAVORITES,ICON16));
			m_pImageList->Add(Global.GetIcon(IDX_ICON_INTERNET,ICON16));
			m_pImageList->Add(Global.GetIcon(IDX_ICON_SETTING,ICON16));
		}

		// TAB 1
		m_tab1.SetImageList(m_pImageList);
		m_tab1.ModifyStyle(TCS_BOTTOM|TCS_MULTILINE|TCS_VERTICAL, TCS_OWNERDRAWFIXED|TCS_FIXEDWIDTH|TCS_BUTTONS);
		m_tab1.InsertItem( 0, _T("사진"), 0 );
		m_tab1.InsertItem( 1, _T("여행"), 1 );
		m_tab1.InsertItem( 2, _T("스포츠"), 2 );
		m_tab1.InsertItem( 3, _T("연극"), 3 );
		
		m_tab1.SetColor(RGB(51,51,51), RGB(206,206,206), Global.GetRGB(IDX_RGB_BACKGROUND), Global.GetRGB(IDX_RGB_BACKGROUND));
		m_tab1.SetItemSize(CSize(80,TAB_HEADER_HEIGHT));
		//m_tab1.Set3dBorder(TRUE);

		// TAB 2
		m_tab2.SetImageList(m_pImageList);
		m_tab2.ModifyStyle(TCS_BOTTOM|TCS_BUTTONS, TCS_OWNERDRAWFIXED|TCS_FIXEDWIDTH);
		m_tab2.InsertItem( 0, _T("사진"), 0 );
		m_tab2.InsertItem( 1, _T("여행"), 1 );

		m_tab2.SetColor(RGB(51,51,51), RGB(215,213,224), Global.GetRGB(IDX_RGB_BACKGROUND), Global.GetRGB(IDX_RGB_BACKGROUND));
		m_tab2.SetItemSize(CSize(70,TAB_HEADER_HEIGHT));
		m_tab2.Set3dBorder(TRUE);

		// TAB 3
		m_tab3.SetImageList(m_pImageList);
		m_tab3.ModifyStyle(TCS_BOTTOM|TCS_MULTILINE|TCS_VERTICAL|TCS_BUTTONS, TCS_OWNERDRAWFIXED|TCS_FIXEDWIDTH);
		m_tab3.InsertItem( 0, _T("사진"), 0 );
		m_tab3.InsertItem( 1, _T("여행"), 1 );

		m_tab3.SetColor(RGB(51,51,51), RGB(186,186,186), Global.GetRGB(IDX_RGB_BACKGROUND), Global.GetRGB(IDX_RGB_BACKGROUND));
		m_tab3.SetItemSize(CSize(70,TAB_HEADER_HEIGHT));
		m_tab3.Set3dBorder(TRUE);

		// TAB 4
		m_tab4.SetImageList(m_pImageList);
		m_tab4.ModifyStyle(TCS_BOTTOM|TCS_MULTILINE|TCS_VERTICAL|TCS_BUTTONS, TCS_OWNERDRAWFIXED|TCS_FIXEDWIDTH);
		m_tab4.InsertItem( 0, _T("사진"), 0 );
		m_tab4.InsertItem( 1, _T("여행"), 1 );

		m_tab4.SetColor(RGB(51,51,51), RGB(103,103,103), Global.GetRGB(IDX_RGB_BACKGROUND), Global.GetRGB(IDX_RGB_BACKGROUND));
		m_tab4.SetItemSize(CSize(70,TAB_HEADER_HEIGHT));
		//m_tab3.Set3dBorder(TRUE);

		// TAB 5
		m_tab5.SetImageList(m_pImageList);
		m_tab5.ModifyStyle(TCS_BOTTOM|TCS_BUTTONS, TCS_OWNERDRAWFIXED|TCS_FIXEDWIDTH|TCS_VERTICAL);
		m_tab5.InsertItem( 0, _T("사진"), 0 );
		m_tab5.InsertItem( 1, _T("여행"), 1 );
		m_tab5.InsertItem( 2, _T("스포츠"), 2 );
		m_tab5.InsertItem( 3, _T("연극"), 3 );
		
		m_tab5.SetColor(RGB(51,51,51), RGB(206,206,206), Global.GetRGB(IDX_RGB_BACKGROUND), Global.GetRGB(IDX_RGB_BACKGROUND));
		m_tab5.SetItemSize(CSize(80,TAB_HEADER_HEIGHT));
		//m_tab5.Set3dBorder(TRUE);

		RelocationControls();
	}
#endif

	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CTestDlg::OnPaint()
{
#if 0
	if( IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CSkinDialog::OnPaint();
	}
#else
	CSkinDialog::OnPaint();
#endif
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CTestDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CTestDlg::OnSize(UINT nType, int cx, int cy)
{
	CSkinDialog::OnSize(nType, cx, cy);

	// TODO: Add your message handler code here

	if( m_bInitialized )
		RelocationControls();
}

void CTestDlg::RelocationControls()
{
	CRect rc;
	GetClientRect(&rc);

	int x=0, y=0;

	SIZE size = Global.GetBitmapSize(IDX_BMP_BTN_BASE);

	x = rc.Width() - 20 - size.cx;
	y = rc.Height() - 10 - size.cy;
	m_btnCancel.MoveWindow(x, y, size.cx, size.cy, TRUE);
	
	x -= size.cx + 10;
	m_btnOk.MoveWindow(x, y, size.cx, size.cy, TRUE);
	m_btnOk.Invalidate();
}

void CTestDlg::OnDestroy()
{
	CSkinDialog::OnDestroy();

	// TODO: Add your message handler code here

	if( m_pImageList != NULL ) 
	{
		if( m_pImageList->GetImageCount() )
			m_pImageList->DeleteImageList();
		delete m_pImageList;
		m_pImageList = NULL;
	}
}
