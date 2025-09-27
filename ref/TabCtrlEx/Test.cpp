// Test.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "Test.h"
#include "TestDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CTestApp

BEGIN_MESSAGE_MAP(CTestApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CTestApp construction

CTestApp::CTestApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}


// The one and only CTestApp object

CTestApp theApp;
CGlobal Global;

// CTestApp initialization

BOOL CTestApp::InitInstance()
{
#ifdef __GDI_PLUS__	
	GdiplusStartupInput gdiplusStartupInput;
	GdiplusStartup(&m_gdiplusToken, &gdiplusStartupInput, NULL);
#endif

	// InitCommonControlsEx() is required on Windows XP if an application
	// manifest specifies use of ComCtl32.dll version 6 or later to enable
	// visual styles.  Otherwise, any window creation will fail.
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// Set this to include all the common control classes you want to use
	// in your application.
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();

	AfxEnableControlContainer();

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	// of your final executable, you should remove from the following
	// the specific initialization routines you do not need
	// Change the registry key under which our settings are stored
	// TODO: You should modify this string to be something appropriate
	// such as the name of your company or organization
	SetRegistryKey(_T("Local AppWizard-Generated Applications"));

	Global.LoadBitmaps();
	Global.LoadIcons();

	Global.SetRGB(IDX_RGB_MASK, RGB(255,0,255));
	Global.SetRGB(IDX_RGB_BACKGROUND, RGB(255,255,255));

	Global.SetRGB(IDX_RGB_FONT, RGB(51,51,51));
	Global.SetRGB(IDX_RGB_FONT_CAPTION, RGB(0,0,0));
	Global.SetRGB(IDX_RGB_FONT_CAPTION_INACTIVE, RGB(178,178,178));

	CTestDlg dlg;
	m_pMainWnd = &dlg;	

	Global.SetFont(IDX_FONT_SMALL, _T("Arial"), 8);
	Global.SetFont(IDX_FONT_MEDIUM, _T("Arial"), 9);
	Global.SetFont(IDX_FONT_LARGE, _T("Arial"), 11, TRUE);

	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with OK
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with Cancel
	}

	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}

int CTestApp::ExitInstance()
{
	// TODO: Add your specialized code here and/or call the base class

#ifdef __GDI_PLUS__	
	GdiplusShutdown(m_gdiplusToken);
#endif

	return CWinApp::ExitInstance();
}
