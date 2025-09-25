#if !defined(AFX_TabCtrlEx_H__1E6E4FE9_BE01_4DA1_AFA9_A98527A3769B__INCLUDED_)
#define AFX_TabCtrlEx_H__1E6E4FE9_BE01_4DA1_AFA9_A98527A3769B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// TabCtrlEx.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CTabCtrlEx window

class CTabCtrlEx : public CTabCtrl
{
// Construction
public:
	CTabCtrlEx();

	// ����/���/���� �� ����
	void SetColor(COLORREF crText, COLORREF crBorder, COLORREF crBackIn, COLORREF crBackOut, BOOL bRedraw=TRUE);
	// ���� ��Ÿ�� ����
	void Set3dBorder(BOOL b3dBorder) { m_b3dBorder = b3dBorder; }
	// �� ������ �̹��� ����
	void SetItemImage(int nItem, int nImage);

protected:
	COLORREF m_crBackIn;		// �� ���� ����
	COLORREF m_crBackOut;		// �� �ٱ��� ����
	COLORREF m_crText;			// �ؽ�Ʈ ��
	COLORREF m_crBorder;		// ���� ��

	BOOL	m_b3dBorder;		// ���� ��Ÿ�� : TRUE=3D, FALSE=�÷�

protected:
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTabCtrlEx)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CTabCtrlEx();

	// Generated message map functions
protected:
	//{{AFX_MSG(CTabCtrlEx)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnPaint();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

protected:
	// ���� ��Ÿ���� ��� �ؽ�Ʈ�� ���ھ� ���η� ���
	virtual void TextOutVertical(CDC* pDC, CRect rect, CStringW sText);
	// ���� ������ �׸�
	virtual void DrawMainBorder(LPDRAWITEMSTRUCT lpDrawItemStruct);
	// �ش� �� �������� �ؽ�Ʈ�� ���
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	// �ش� �� �������� ������ �׸�
	virtual void DrawItemBorder(LPDRAWITEMSTRUCT lpDrawItemStruct);
	virtual void PreSubclassWindow();
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TabCtrlEx_H__1E6E4FE9_BE01_4DA1_AFA9_A98527A3769B__INCLUDED_)
