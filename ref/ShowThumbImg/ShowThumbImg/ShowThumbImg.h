
// ShowThumbImg.h : PROJECT_NAME ���� ���α׷��� ���� �� ��� �����Դϴ�.
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"		// �� ��ȣ�Դϴ�.


// CShowThumbImgApp:
// �� Ŭ������ ������ ���ؼ��� ShowThumbImg.cpp�� �����Ͻʽÿ�.
//

class CShowThumbImgApp : public CWinApp
{
public:
	CShowThumbImgApp();

// �������Դϴ�.
public:
	virtual BOOL InitInstance();

// �����Դϴ�.

	DECLARE_MESSAGE_MAP()
};

extern CShowThumbImgApp theApp;
