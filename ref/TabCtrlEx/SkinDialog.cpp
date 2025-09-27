// SkinDialog.cpp : implementation file
//

#include "stdafx.h"
#include "SkinDialog.h"

#include "Test.h"

#define MARGIN_BOX			10

#define MARGIN_MAXIMIZED	4

// CSkinDialog dialog
CSkinDialog::CSkinDialog(UINT nResourceID, CWnd* pParent /*=NULL*/)
	: CDialog(nResourceID, pParent)
{
	//{{AFX_DATA_INIT(CShapeDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT

	m_CtlColorBrush.CreateSolidBrush(Global.GetRGB(IDX_RGB_BACKGROUND));

	m_nClickedBox	= CLICKED_BOX_NONE;

	m_bTracking		= FALSE;

	m_bDraging		= FALSE;
	m_bSizeCursor	= FALSE;

	m_bActive		= FALSE;

	m_cfText		= RGB(0,0,0);
	m_cfMask		= RGB(255,0,255);

	m_hBmpCapL		= NULL;
	m_hBmpCapM		= NULL;
	m_hBmpCapR		= NULL;
	m_hBmpFrmL		= NULL;
	m_hBmpFrmLB		= NULL;
	m_hBmpFrmB		= NULL;
	m_hBmpFrmR		= NULL;
	m_hBmpFrmRB		= NULL;

	m_hBmpMinimize	= NULL;
	m_hBmpMaximize	= NULL;
	m_hBmpRestore	= NULL;
	m_hBmpExit		= NULL;

	m_hIcon			= NULL;

	memset(&m_sizeCapL, 0x00, sizeof(SIZE));
	memset(&m_sizeCapM, 0x00, sizeof(SIZE));
	memset(&m_sizeCapR, 0x00, sizeof(SIZE));
	memset(&m_sizeFrmL, 0x00, sizeof(SIZE));
	memset(&m_sizeFrmLB, 0x00, sizeof(SIZE));
	memset(&m_sizeFrmB, 0x00, sizeof(SIZE));
	memset(&m_sizeFrmRB, 0x00, sizeof(SIZE));
	memset(&m_sizeFrmR, 0x00, sizeof(SIZE));
	memset(&m_sizeBox, 0x00, sizeof(SIZE));
}

void CSkinDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CSkinDialog, CDialog)
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_WM_SIZE()
	ON_WM_NCPAINT()	
	ON_WM_NCACTIVATE()
	ON_WM_NCCALCSIZE()
	ON_WM_CTLCOLOR()
	ON_WM_GETMINMAXINFO()
	ON_WM_SETCURSOR()
	ON_MESSAGE(WM_ENTERSIZEMOVE, OnEnterSizeMove)
	ON_MESSAGE(WM_EXITSIZEMOVE, OnExitSizeMove)
	ON_WM_ACTIVATE()	
	ON_WM_PAINT()
END_MESSAGE_MAP()


// CSkinDialog message handlers

HBRUSH CSkinDialog::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  Change any attributes of the DC here

	if( pWnd->IsKindOf(RUNTIME_CLASS(CButton)) )
	{
		return (HBRUSH)m_CtlColorBrush;
	}

	// TODO:  Return a different brush if the default is not desired
	return hbr;
}

void CSkinDialog::OnDestroy() 
{
	CDialog::OnDestroy();
	
	// TODO: Add your message handler code here

	m_CtlColorBrush.DeleteObject();
	m_rgnWnd.DeleteObject();
}

void CSkinDialog::OnNcPaint()
{
	// TODO: Add your message handler code here
	// Do not call CDialog::OnNcPaint() for painting messages
	if( GetWindowLong(GetSafeHwnd(), GWL_STYLE) & WS_CAPTION )
	{
		DrawFrame();
	}
}

void CSkinDialog::OnSize(UINT nType, int cx, int cy) 
{
	CDialog::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here

	if( GetWindowLong(GetSafeHwnd(), GWL_STYLE) & WS_CAPTION )
	{
		CRect rc;
		GetWindowRect(&rc);

		int width = rc.Width()+1;
		int height = rc.Height()+1;

		int x = 0, y = 0;
		int round = 14;
		CRgn rgnA, rgnB;

		if( nType == SIZE_MAXIMIZED )
		{
			x = MARGIN_MAXIMIZED;
			y = MARGIN_MAXIMIZED;
			width -= MARGIN_MAXIMIZED;
			height -= MARGIN_MAXIMIZED;
		}

		// ��ü ����
		if( (HRGN)m_rgnWnd != NULL )
			m_rgnWnd.DeleteObject();
		m_rgnWnd.CreateRectRgn( x, y, width, height );

		// left-top�߶󳻱� ���� ����
		rgnA.CreateEllipticRgn(x, y, round, round);
		rgnB.CreateRectRgn(x, y, round/2, round/2);
		rgnA.CombineRgn(&rgnB, &rgnA, RGN_DIFF);

		// left-top���� �߶�
		m_rgnWnd.CombineRgn(&m_rgnWnd, &rgnA, RGN_DIFF);
		rgnA.DeleteObject();
		rgnB.DeleteObject();

		// right-top�߶󳻱� ���� ����
		rgnA.CreateEllipticRgn(width-round, y, width, round);
		rgnB.CreateRectRgn(width-round/2, y, width, round/2);
		rgnA.CombineRgn(&rgnB, &rgnA, RGN_DIFF);

		// right-top���� �߶�
		m_rgnWnd.CombineRgn(&m_rgnWnd, &rgnA, RGN_DIFF);
		rgnA.DeleteObject();
		rgnB.DeleteObject();

		// left-bottom�߶󳻱� ���� ����
//		rgnA.CreateEllipticRgn(x, height-round, round, height);
//		rgnB.CreateRectRgn(x, height-round/2, round/2, height);
//		rgnA.CombineRgn(&rgnB, &rgnA, RGN_DIFF);

		// left-bottom���� �߶�
//		m_rgnWnd.CombineRgn(&m_rgnWnd, &rgnA, RGN_DIFF);
//		rgnA.DeleteObject();
//		rgnB.DeleteObject();

		// right-bottom�߶󳻱� ���� ����
//		rgnA.CreateEllipticRgn(width-round, height-round, width, height);
//		rgnB.CreateRectRgn(width-round/2, height-round/2, width, height);
//		rgnA.CombineRgn(&rgnB, &rgnA, RGN_DIFF);

		// right-bottom���� �߶�
//		m_rgnWnd.CombineRgn(&m_rgnWnd, &rgnA, RGN_DIFF);
//		rgnA.DeleteObject();
//		rgnB.DeleteObject();

		// ������
		SetWindowRgn((HRGN)m_rgnWnd, TRUE);
	}
}

BOOL CSkinDialog::OnNcActivate(BOOL bActive)
{
	// TODO: Add your message handler code here and/or call default

	if( GetWindowLong(GetSafeHwnd(), GWL_STYLE) & WS_CAPTION )
	{
		DrawFrame();
		return TRUE;
	}
	else
	{
		return CDialog::OnNcActivate(bActive);
	}
}

void CSkinDialog::OnNcCalcSize(BOOL bCalcValidRects, NCCALCSIZE_PARAMS* lpncsp)
{
	// TODO: Add your message handler code here and/or call default

	if( GetWindowLong(GetSafeHwnd(), GWL_STYLE) & WS_CAPTION )
	{
		int revision=0;
		
		// Recalculate top
		if( m_sizeCapM.cy )
		{
			revision = m_sizeCapM.cy - (GetSystemMetrics(SM_CYCAPTION)+GetSystemMetrics(SM_CYFRAME));
			lpncsp->rgrc[0].top += revision;
		}

		// Recalculate left
		if( m_sizeFrmL.cx )
		{
			revision = m_sizeFrmL.cx - GetSystemMetrics(SM_CXFRAME);
			lpncsp->rgrc[0].left += revision;
		}

		// Recalculate right
		if( m_sizeFrmR.cx )
		{
			revision = m_sizeFrmR.cx - GetSystemMetrics(SM_CXFRAME);
			lpncsp->rgrc[0].right -= revision;
		}

		// Recalculate bottom
		if( m_sizeFrmB.cy )
		{
			revision = m_sizeFrmB.cy - GetSystemMetrics(SM_CXFRAME);
			lpncsp->rgrc[0].bottom -= revision;
		}
	}

	CDialog::OnNcCalcSize(bCalcValidRects, lpncsp);
}

void CSkinDialog::DrawFrame()
{
	if( !(GetWindowLong(GetSafeHwnd(), GWL_STYLE) & WS_CAPTION) )
		return;

	int x=0,y=0,x2=0,y2=0,cx=0,cy=0;
	CRect rc;
	GetWindowRect(&rc);
	BOOL bIconic = IsIconic();
	BOOL bZoomed = IsZoomed();

	// Non-Client ������ DC�� ���´�.
	CWindowDC dc(this);	

	// ȣȯ�� �ִ� �޸� DC�� ����(�������)
	CDC BufferDC, tmpDC;
	BufferDC.CreateCompatibleDC(&dc);
	tmpDC.CreateCompatibleDC(&dc);

	// �޸� ��Ʈ�� ����
	CBitmap bmpBuffer, *pOldBitmap1;
	HGDIOBJ hgdiobj;

	// ȣȯ�� �ִ� �޸� ��Ʈ�� �����Ͽ� �޸� DC�� ����
	bmpBuffer.CreateCompatibleBitmap(&dc, rc.Width(), rc.Height());
	pOldBitmap1 = (CBitmap *)BufferDC.SelectObject(&bmpBuffer);

	// Left ĸ�� ��Ʈ���� �޸� DC�� ����
	x = 0;
	y = 0;
	cx = m_sizeCapL.cx;
	cy = m_sizeCapL.cy;
	hgdiobj = tmpDC.SelectObject( m_hBmpCapL );
	BufferDC.BitBlt(x, y, cx, cy, &tmpDC, 0, 0, SRCCOPY);

	// Center ĸ�� ��Ʈ���� �޸� DC�� ����
	x += cx;
	cx = rc.Width() - m_sizeCapL.cx - m_sizeCapR.cx;
	cy = m_sizeCapM.cy;
	tmpDC.SelectObject( m_hBmpCapM );
	BufferDC.StretchBlt(x, y, cx, cy, &tmpDC, 0, 0, m_sizeCapM.cx, m_sizeCapM.cy, SRCCOPY);

	// Right ĸ�� ��Ʈ���� �޸� DC�� ����
	x += cx;
	cx = m_sizeCapR.cx;
	cy = m_sizeCapR.cy;
	tmpDC.SelectObject( m_hBmpCapR );
	BufferDC.BitBlt(x, y, cx, cy, &tmpDC, 0, 0, SRCCOPY);

	// Left ���� ��Ʈ���� �޸� DC�� ����
	x = 0;
	y = m_sizeCapL.cy;
	cx = m_sizeFrmL.cx;
	cy = rc.Height() - m_sizeCapL.cy - m_sizeFrmB.cy;
	tmpDC.SelectObject( m_hBmpFrmL );
	BufferDC.StretchBlt(x, y, cx, cy, &tmpDC, 0, 0, m_sizeFrmL.cx, m_sizeFrmL.cy, SRCCOPY);

	// Left-Bottom ���� ��Ʈ���� �޸� DC�� ����
	y += cy;
	cx = m_sizeFrmLB.cx;
	cy = m_sizeFrmLB.cy;
	tmpDC.SelectObject( m_hBmpFrmLB );
	BufferDC.BitBlt(x, y, cx, cy, &tmpDC, 0, 0, SRCCOPY);

	// Bottom ���� ��Ʈ���� �޸� DC�� ����
	x += cx;
	cx = rc.Width() - m_sizeFrmL.cx - m_sizeFrmR.cx;
	cy = m_sizeFrmB.cy;
	tmpDC.SelectObject( m_hBmpFrmB );
	BufferDC.StretchBlt(x, y, cx, cy, &tmpDC, 0, 0, m_sizeFrmB.cx, m_sizeFrmB.cy, SRCCOPY);	

	// Right ���� ��Ʈ���� �޸� DC�� ����
	x = rc.Width()-m_sizeFrmR.cx;
	y = m_sizeCapR.cy;
	cx = m_sizeFrmR.cx;
	cy = rc.Height() - m_sizeCapR.cy - m_sizeFrmRB.cy;
	tmpDC.SelectObject( m_hBmpFrmR );
	BufferDC.StretchBlt(x, y, cx, cy, &tmpDC, 0, 0, m_sizeFrmR.cx, m_sizeFrmR.cy, SRCCOPY);

	// Right-Bottom ���� ��Ʈ���� �޸� DC�� ����
	x = rc.Width()-m_sizeFrmRB.cx;
	y += cy;
	cx = m_sizeFrmRB.cx;
	cy = m_sizeFrmRB.cy;
	tmpDC.SelectObject( m_hBmpFrmRB );
	BufferDC.BitBlt(x, y, cx, cy, &tmpDC, 0, 0, SRCCOPY);	

	if( !bIconic )
	{
		// ĸ�� ������ ��Ʈ���� �޸� DC�� ����
		::DrawIconEx(BufferDC.m_hDC, 15, 5, m_hIcon, 24, 24, 0, NULL, DI_NORMAL);

		if( bZoomed )
			y = MARGIN_MAXIMIZED;
		else
			y = 0;

		// Close Box ��Ʈ���� �޸� DC�� ����
		tmpDC.SelectObject(m_hBmpExit);
		x = rc.Width()-MARGIN_BOX-m_sizeBox.cx;
		BufferDC.BitBlt(x, y, m_sizeBox.cx, m_sizeBox.cx, &tmpDC, 0, 0, SRCCOPY);

		if( !bZoomed )
		{
			// Maximize Box ��Ʈ���� �޸� DC�� ����
			tmpDC.SelectObject(m_hBmpMaximize);
			x = x-m_sizeBox.cx;			
			BufferDC.BitBlt(x, y, m_sizeBox.cx, m_sizeBox.cx, &tmpDC, 0, 0, SRCCOPY);
		}
		else
		{
			// Restore Box ��Ʈ���� �޸� DC�� ����
			tmpDC.SelectObject(m_hBmpRestore);
			x = x-m_sizeBox.cx;			
			BufferDC.BitBlt(x, y, m_sizeBox.cx, m_sizeBox.cx, &tmpDC, 0, 0, SRCCOPY);
		}

		// Minimize Box ��Ʈ���� �޸� DC�� ����
		tmpDC.SelectObject(m_hBmpMinimize);
		x = x-m_sizeBox.cx;		
		BufferDC.BitBlt(x, y, m_sizeBox.cx, m_sizeBox.cx, &tmpDC, 0, 0, SRCCOPY);
	}
	else
	{
		// ĸ�� ������ ��Ʈ���� �޸� DC�� ����
		::DrawIconEx(BufferDC.m_hDC, 15, 5, m_hIcon, 16, 16, 0, NULL, DI_NORMAL);

		// Close Box ��Ʈ���� �޸� DC�� ����
		tmpDC.SelectObject(m_hBmpExit);
		x = rc.Width()-MARGIN_BOX-m_sizeBox.cx;
		BufferDC.BitBlt(x, 0, m_sizeBox.cx, m_sizeBox.cx, &tmpDC, 0, 0, SRCCOPY);//m_sizeBox.cx, m_sizeBox.cx, m_cfMask);

		// Maximize Box ��Ʈ���� �޸� DC�� ����
		tmpDC.SelectObject(m_hBmpMaximize);
		x = x-m_sizeBox.cx;		
		BufferDC.BitBlt(x, 0, m_sizeBox.cx, m_sizeBox.cx, &tmpDC, 0, 0, SRCCOPY);//m_sizeBox.cx, m_sizeBox.cx, m_cfMask);

		// Restore Box ��Ʈ���� �޸� DC�� ����
		tmpDC.SelectObject(m_hBmpRestore);
		x = x-m_sizeBox.cx;		
		BufferDC.BitBlt(x, 0, m_sizeBox.cx, m_sizeBox.cx, &tmpDC, 0, 0, SRCCOPY);//m_sizeBox.cx, m_sizeBox.cx, m_cfMask);
	}

	// �޸� DC ���� ����
	tmpDC.SelectObject(hgdiobj);
	tmpDC.DeleteDC();

	// �ؽ�Ʈ ����带 ����(����)
	BufferDC.SetBkMode(TRANSPARENT);

	// �⺻ �۲��� DC�� ����
	//CFont *pOldFont = (CFont *)BufferDC.SelectObject(GetFont());

	// �ؽ�Ʈ�� ������� ����
	BufferDC.SetTextColor(m_cfText);

	// ���ڿ��� ��µ� �������� ��ǥ ����
	BufferDC.SetTextAlign(TA_LEFT|TA_TOP);
	
	if( !bIconic )
	{
		// �ؽ�Ʈ�� �޸� DC�� ���
		CString str;
		GetWindowText(str);
		BufferDC.TextOut(50, 10, str);

		// Ŭ���̾�Ʈ ������ �����Ѵ�.
		x = m_sizeFrmL.cx;
		y = m_sizeCapM.cy;
		x2 = rc.Width() - m_sizeFrmR.cx;
		y2 = rc.Height() - m_sizeFrmB.cy;	
		dc.ExcludeClipRect(x, y, x2, y2);
	}
	else
	{
		// �ؽ�Ʈ�� �޸� DC�� ���
		CString str;
		GetWindowText(str);

		if( str.GetLength() > 4 )
			str = str.Left(4) + _T("...");

		BufferDC.TextOut(30, (rc.Height()-dc.GetTextExtent(str).cy)/2, str);
	}

	// �޸� DC�� �׷��� ��Ʈ���� ȭ������ ����	
	dc.BitBlt(0, 0, rc.Width(), rc.Height(), &BufferDC, 0, 0, SRCCOPY);

	// �޸� DC ���� �� ����
	//BufferDC.SelectObject(pOldFont);
	BufferDC.SelectObject(pOldBitmap1);
	BufferDC.DeleteDC();
}

BOOL CSkinDialog::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message) 
{
	// TODO: Add your message handler code here and/or call default

	if( nHitTest == HTBOTTOM	|| nHitTest == HTTOP || 
		nHitTest == HTLEFT		|| nHitTest == HTRIGHT ||
		nHitTest == HTBOTTOMLEFT|| nHitTest == HTBOTTOMRIGHT ||
		nHitTest == HTTOPLEFT	|| nHitTest == HTTOPRIGHT )
		m_bSizeCursor = TRUE;
	else
		m_bSizeCursor = FALSE;

	if( m_nClickedBox != CLICKED_BOX_NONE )
		return TRUE;

	return CDialog::OnSetCursor(pWnd, nHitTest, message);
}

LRESULT CSkinDialog::OnEnterSizeMove( WPARAM wParam, LPARAM lParam)
{
	if( m_bSizeCursor )
		return 0L;

	if( !m_bDraging )
	{
		m_bDraging = TRUE;
		::SetWindowLong(m_hWnd, GWL_EXSTYLE, GetWindowLong(m_hWnd, GWL_EXSTYLE) ^ WS_EX_LAYERED);
		Global.SetLayeredWindowAttributes(m_hWnd, 0, 176, LWA_ALPHA);
		::RedrawWindow(m_hWnd, NULL, NULL, RDW_ERASE | RDW_INVALIDATE | RDW_FRAME | RDW_ALLCHILDREN);
	}

	m_bTracking = FALSE;
    return 0L;
}


LRESULT CSkinDialog::OnExitSizeMove( WPARAM wParam, LPARAM lParam)
{
	if( m_bDraging )
	{
		m_bDraging = FALSE;
		::SetWindowLong(m_hWnd, GWL_EXSTYLE, GetWindowLong(m_hWnd, GWL_EXSTYLE) & ~WS_EX_LAYERED);
		::RedrawWindow(m_hWnd, NULL, NULL, RDW_ERASE | RDW_INVALIDATE | RDW_FRAME | RDW_ALLCHILDREN);
	}

	m_bTracking = FALSE;
    return 0L;
}

void CSkinDialog::SetCtlColor(COLORREF crCtlColor)
{
	m_CtlColorBrush.DeleteObject();
	m_CtlColorBrush.CreateSolidBrush(crCtlColor);
	RedrawWindow();
}

void CSkinDialog::OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized)
{
	m_bActive = (nState ? TRUE : FALSE);

	if( GetWindowLong(GetSafeHwnd(), GWL_STYLE) & WS_CAPTION )
	{
		if( m_bActive )
		{
			m_hIcon = Global.GetIcon(IDX_ICON_SKIN,ICON24);
			m_cfText = Global.GetRGB(IDX_RGB_FONT_CAPTION);
		}
		else
		{
			m_hIcon = Global.GetIcon(IDX_ICON_SKIN_INACTIVE,ICON24);
			m_cfText = Global.GetRGB(IDX_RGB_FONT_CAPTION_INACTIVE);
		}

		DrawFrame();
	}
	else
	{
		CDialog::OnActivate(nState, pWndOther, bMinimized);
	}

	// TODO: Add your message handler code here
	
}

BOOL CSkinDialog::PreTranslateMessage(MSG* pMsg) 
{
	// TODO: Add your specialized code here and/or call the base class

	if(	pMsg->message == WM_SYSKEYDOWN && pMsg->wParam == VK_F4 ||
		pMsg->wParam == VK_ESCAPE || 
		pMsg->wParam == VK_RETURN )
	{
		return TRUE;
	}
	else if( pMsg->message == WM_NCLBUTTONDOWN ||	// None Client �������� ���콺 ���� ��ư�� ���� ���� ��
			 pMsg->message == WM_NCMOUSEMOVE ||		// None Client �������� ���콺�� �̵��� ��
			 pMsg->message == WM_LBUTTONUP ||		// None Client ������ �ƴѰ����� ���콺 ���� ��ư�� �������� ���
			 pMsg->message == WM_NCLBUTTONUP ||		// None Client �������� ���콺 ���� ��ư�� �������� ���
			 pMsg->message == WM_NCMOUSELEAVE )		// None Client ������ �ƴѰ����� ���콺�� �̵����� ���
	{
		if( GetWindowLong(GetSafeHwnd(), GWL_STYLE) & WS_CAPTION )
		{
			CRect rc;
			GetWindowRect(&rc);

			CRect rcExit, rcMaximize, rcMinimize;

			int x=0,y=0,cx=0,cy=0;

			SIZE sizeBox = Global.GetBitmapSize(IDX_BMP_BOX_EXIT);

			BOOL bZoomed = IsZoomed();				// ���� �����찡 �ִ�ȭ ��������..
			BOOL bIconic = IsIconic();				// ���� �����찡 �ּ�ȭ ��������..
			BOOL bLButton = KEYDOWN(VK_LBUTTON);	// ���� ���콺 ���� ��ư�� �������ִ���..

			y = rc.top+MARGIN_MAXIMIZED;

			rcExit.left = rc.right-MARGIN_BOX-sizeBox.cx;
			rcExit.top = y;
			rcExit.right = rcExit.left+sizeBox.cx;
			rcExit.bottom = rcExit.top+sizeBox.cy;

			rcMaximize.left = rcExit.left-sizeBox.cx;
			rcMaximize.top = y;
			rcMaximize.right = rcMaximize.left+sizeBox.cx;
			rcMaximize.bottom = rcMaximize.top+sizeBox.cy;

			rcMinimize.left = rcMaximize.left-sizeBox.cx;
			rcMinimize.top = y;
			rcMinimize.right = rcMinimize.left+sizeBox.cx;
			rcMinimize.bottom = rcMinimize.top+sizeBox.cy;

			switch( pMsg->message )
			{
			case WM_NCLBUTTONDOWN :
				if( rcExit.PtInRect(pMsg->pt) )
				{
					SetCapture();
					m_nClickedBox = CLICKED_BOX_EXIT;
					m_hBmpExit = Global.GetBitmap(IDX_BMP_BOX_EXIT_ON);
					DrawFrame();
					return TRUE;
				}
				else if( rcMaximize.PtInRect(pMsg->pt) )
				{
					SetCapture();
					m_nClickedBox = CLICKED_BOX_MAXIMIZE;
					if( IsZoomed() )
						m_hBmpRestore = Global.GetBitmap(IDX_BMP_BOX_RESTORE_ON);
					else
						m_hBmpMaximize = Global.GetBitmap(IDX_BMP_BOX_MAXMIZE_ON);
					DrawFrame();
					return TRUE;
				}
				else if( rcMinimize.PtInRect(pMsg->pt) )
				{
					SetCapture();
					m_nClickedBox = CLICKED_BOX_MINIMIZE;
					if( bIconic )
						m_hBmpRestore = Global.GetBitmap(IDX_BMP_BOX_RESTORE_ON);
					else
						m_hBmpMinimize = Global.GetBitmap(IDX_BMP_BOX_MINIMIZE_ON);
					DrawFrame();
					return TRUE;
				}
				else
				{
					m_nClickedBox = CLICKED_BOX_NONE;

					if( bZoomed )
						return TRUE;
				}
				break;

			case WM_NCMOUSELEAVE :
				m_bTracking = FALSE;
				if( m_nClickedBox == CLICKED_BOX_NONE )
				{					
					m_hBmpMinimize = Global.GetBitmap(IDX_BMP_BOX_MINIMIZE);
					m_hBmpMaximize = Global.GetBitmap(IDX_BMP_BOX_MAXMIZE);
					m_hBmpRestore = Global.GetBitmap(IDX_BMP_BOX_RESTORE);
					m_hBmpExit = Global.GetBitmap(IDX_BMP_BOX_EXIT);
					m_nClickedBox = CLICKED_BOX_NONE;					
					DrawFrame();
				}
				break;

			case WM_NCMOUSEMOVE :				
				if( !m_bTracking )
				{	// ���콺�� �����츦 ����� WM_NCMOUSELEAVE �̺�Ʈ�� �߻��ϵ��� ����
					m_bTracking = TRUE;
					TRACKMOUSEEVENT t = { sizeof(TRACKMOUSEEVENT), TME_NONCLIENT|TME_LEAVE, m_hWnd, 0 };
					::TrackMouseEvent(&t);					
				}

				if( m_nClickedBox != CLICKED_BOX_NONE )
					break;
				
				m_hBmpMinimize = Global.GetBitmap(IDX_BMP_BOX_MINIMIZE);
				m_hBmpMaximize = Global.GetBitmap(IDX_BMP_BOX_MAXMIZE);
				m_hBmpRestore = Global.GetBitmap(IDX_BMP_BOX_RESTORE);
				m_hBmpExit = Global.GetBitmap(IDX_BMP_BOX_EXIT);				
				
				if( rcExit.PtInRect(pMsg->pt) )
				{
					m_hBmpExit = Global.GetBitmap(IDX_BMP_BOX_EXIT_OVER);
				}
				else if( rcMaximize.PtInRect(pMsg->pt) )
				{
					if( IsZoomed() )
						m_hBmpRestore = Global.GetBitmap(IDX_BMP_BOX_RESTORE_OVER);
					else
						m_hBmpMaximize = Global.GetBitmap(IDX_BMP_BOX_MAXMIZE_OVER);
				}
				else if( rcMinimize.PtInRect(pMsg->pt) )
				{
					if( bIconic )
						m_hBmpRestore = Global.GetBitmap(IDX_BMP_BOX_RESTORE_OVER);
					else
						m_hBmpMinimize = Global.GetBitmap(IDX_BMP_BOX_MINIMIZE_OVER);
				}				
				DrawFrame();
				break;

			case WM_LBUTTONUP :
			case WM_NCLBUTTONUP :
				if( m_nClickedBox != CLICKED_BOX_NONE )
					ReleaseCapture();

				if( rcExit.PtInRect(pMsg->pt) )
				{
					if( m_nClickedBox == CLICKED_BOX_EXIT )
					{
						PostMessage(WM_CLOSE, 0, 0);
					}
				}
				else if( rcMaximize.PtInRect(pMsg->pt) )
				{
					if( m_nClickedBox == CLICKED_BOX_MAXIMIZE )
					{
						if( IsZoomed() )
							ShowWindow(SW_RESTORE);
						else
							ShowWindow(SW_MAXIMIZE);
					}
				}
				else if( rcMinimize.PtInRect(pMsg->pt) )
				{
					if( m_nClickedBox == CLICKED_BOX_MINIMIZE )
					{
						if( bIconic )
							ShowWindow(SW_RESTORE);
						else
							ShowWindow(SW_MINIMIZE);
					}
				}
				else
				{					
					m_hBmpMinimize = Global.GetBitmap(IDX_BMP_BOX_MINIMIZE);
					m_hBmpMaximize = Global.GetBitmap(IDX_BMP_BOX_MAXMIZE);
					m_hBmpRestore = Global.GetBitmap(IDX_BMP_BOX_RESTORE);
					m_hBmpExit = Global.GetBitmap(IDX_BMP_BOX_EXIT);
					DrawFrame();
				}

				m_nClickedBox = CLICKED_BOX_NONE;
				break;
			}
		}
	}

	return CDialog::PreTranslateMessage(pMsg);
}

void CSkinDialog::OnGetMinMaxInfo(MINMAXINFO FAR* lpMMI) 
{
	// TODO: Add your message handler code here and/or call default		

	lpMMI->ptMinTrackSize.x = 240;								// ������ �ּ� �ʺ� 
	lpMMI->ptMinTrackSize.y = 100;								// ������ �ּ� ����

#if 0
	/*--------------------------------------------------------------------------------------------
	�Ʒ� �Լ��� Main ����� ȭ���� �۾� ǥ���� ��/���� ���� �۾� ������ ����� ������ API�Դϴ�.
	�̸� ����Ͽ� ������ �ִ�ȭ�� ������ ��ġ/������ ������ ������ �� �ֽ��ϴ�.
	������ ��� ����͸� ����Ѵٸ� �Ʒ��� API�ƴ� ����ͺ� �۾� ������ ������ API�� ����ؾ� �մϴ�.
	�׸��� �ش� �������� ��ġ�� ���� �ҼӵǴ� ����ʹ� �޶��� �� �ֽ��ϴ�.
	�̷� ���� ó���ؾ� �Ұ� �����Ƿ� �츮�� ������ ������ ������ ȣ��Ǵ� 
	OnCreate���� ������ ��Ÿ�ϸ� ������Ͽ� �� ������ ������ �ذ��ϰڽ��ϴ�.
	--------------------------------------------------------------------------------------------*/
	CRect rc;	
	::SystemParametersInfo(SPI_GETWORKAREA, 0, &rc, 0);	

	lpMMI->ptMaxPosition.x = -MARGIN_MAXIMIZED;					// ������ �ִ�ȭ �� X�� ��ǥ
	lpMMI->ptMaxPosition.y = -MARGIN_MAXIMIZED;					// ������ �ִ�ȭ �� Y�� �·�
	lpMMI->ptMaxSize.x = rc.Width()+MARGIN_MAXIMIZED*2;			// ������ �ִ�ȭ �� �ʺ�
	lpMMI->ptMaxSize.y = rc.Height()+MARGIN_MAXIMIZED*2;		// ������ �ִ�ȭ �� ����
	lpMMI->ptMaxTrackSize.x = rc.Width()+MARGIN_MAXIMIZED*2;	// ������ �ִ�ȭ �� �ʺ�
	lpMMI->ptMaxTrackSize.y = rc.Height()+MARGIN_MAXIMIZED*2;	// ������ �ִ�ȭ �� ����
#endif

	CDialog::OnGetMinMaxInfo(lpMMI);
}

int CSkinDialog::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialog::OnCreate(lpCreateStruct) == -1)
		return -1;

	// �������� �ý��� �ڽ��� ǥ������ �ʱ� ���� �������� ��Ÿ���� ������
	// ��� Maximize ó���� �ϱ� ���� ���ҽ������� �ý��� ���� ������ ��Ÿ���� Enable ��Ŵ
	ModifyStyle( WS_SYSMENU, 0);

	// TODO:  Add your specialized creation code here
	m_cfText = Global.GetRGB(IDX_RGB_FONT_CAPTION);
	m_cfMask = Global.GetRGB(IDX_RGB_MASK);

	// �� ��Ʈ���� ������ ������ ���´�.
	m_sizeCapL		= Global.GetBitmapSize(IDX_BMP_CAPTION_LEFT);
	m_sizeCapM		= Global.GetBitmapSize(IDX_BMP_CAPTION_CENTER);
	m_sizeCapR		= Global.GetBitmapSize(IDX_BMP_CAPTION_RIGHT);
	m_sizeFrmL		= Global.GetBitmapSize(IDX_BMP_FRAME_LEFT);
	m_sizeFrmLB		= Global.GetBitmapSize(IDX_BMP_FRAME_LEFT_BOTTOM);
	m_sizeFrmB		= Global.GetBitmapSize(IDX_BMP_FRAME_BOTTOM);
	m_sizeFrmRB		= Global.GetBitmapSize(IDX_BMP_FRAME_RIGHT_BOTTOM);
	m_sizeFrmR		= Global.GetBitmapSize(IDX_BMP_FRAME_RIGHT);
	m_sizeBox		= Global.GetBitmapSize(IDX_BMP_BOX_EXIT);

	// �� ��Ʈ���� �ڵ��� ���´�.
	m_hBmpCapL		= Global.GetBitmap(IDX_BMP_CAPTION_LEFT);
	m_hBmpCapM		= Global.GetBitmap(IDX_BMP_CAPTION_CENTER);
	m_hBmpCapR		= Global.GetBitmap(IDX_BMP_CAPTION_RIGHT);
	m_hBmpFrmL		= Global.GetBitmap(IDX_BMP_FRAME_LEFT);
	m_hBmpFrmLB		= Global.GetBitmap(IDX_BMP_FRAME_LEFT_BOTTOM);
	m_hBmpFrmB		= Global.GetBitmap(IDX_BMP_FRAME_BOTTOM);
	m_hBmpFrmR		= Global.GetBitmap(IDX_BMP_FRAME_RIGHT);
	m_hBmpFrmRB		= Global.GetBitmap(IDX_BMP_FRAME_RIGHT_BOTTOM);

	m_hBmpMinimize	= Global.GetBitmap(IDX_BMP_BOX_MINIMIZE);
	m_hBmpMaximize	= Global.GetBitmap(IDX_BMP_BOX_MAXMIZE);
	m_hBmpRestore	= Global.GetBitmap(IDX_BMP_BOX_RESTORE);
	m_hBmpExit		= Global.GetBitmap(IDX_BMP_BOX_EXIT);

	//
	m_hIcon			= Global.GetIcon(IDX_ICON_SKIN,ICON24);			

	return 0;
}

void CSkinDialog::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: Add your message handler code here
	// Do not call CDialog::OnPaint() for painting messages

	CRect rc;
	GetClientRect(&rc);
	dc.FillSolidRect(rc, Global.GetRGB(IDX_RGB_BACKGROUND));
}