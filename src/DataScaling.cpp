// DataScaling.cpp: 구현 파일
//

#include "pch.h"
#include "DataScaling.h"
#include "afxdialogex.h"

#define LEVEL_A_COLOR 16032864 //16764133
#define LEVEL_B_COLOR 10066176

// DataScaling 대화 상자

IMPLEMENT_DYNAMIC(DataScaling, CDialog)

DataScaling::DataScaling(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_MONITORING_DIALOG, pParent)
{

}

DataScaling::~DataScaling()
{
}

void DataScaling::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(DataScaling, CDialog)
	ON_BN_CLICKED(IDC_MFCBUTTON_ADMIN_INKSYSTEM_SETUP, &DataScaling::OnBnClickedMfcbuttonAdminInksystemSetup)
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// DataScaling 메시지 처리기
// 다이얼로그 생성될 때 초기화 실행 
BOOL DataScaling::OnInitDialog()
{
	CDialog::OnInitDialog();		// 이거 꼭 있어야함!! 이거 없어서 삽질 했었다..

	// 부모 다이얼로그 초기화
	//qmdlg = (CQManagerDKDlg*)GetParent();

	// 다이얼로그 크기 조절
	CRect rect;
	this->GetParent()->GetClientRect(&rect);
	MoveWindow(rect.left, rect.top, rect.right - rect.left, rect.bottom - rect.top - 100);


	// 글자크기 조정
	font_text.CreateFont(
		20, // nHeight 
		8, // nWidth 
		0, // nEscapement 
		0, // nOrientation 
		1, // nWeight 
		0, // bItalic 
		0, // bUnderline 
		0, // cStrikeOut 
		0, // nCharSet 
		OUT_DEFAULT_PRECIS, // nOutPrecision 
		0,                              // nClipPrecision 
		DEFAULT_QUALITY,       // nQuality
		DEFAULT_PITCH | FF_DONTCARE,  // nPitchAndFamily 
		"tahoma"); // lpszFacename

	font_text_big.CreateFont(
		40, // nHeight 
		15, // nWidth 
		0, // nEscapement 
		0, // nOrientation 
		1, // nWeight 
		0, // bItalic 
		0, // bUnderline 
		0, // cStrikeOut 
		0, // nCharSet 
		OUT_DEFAULT_PRECIS, // nOutPrecision 
		0,                              // nClipPrecision 
		DEFAULT_QUALITY,       // nQuality
		DEFAULT_PITCH | FF_DONTCARE,  // nPitchAndFamily 
		"tahoma"); // lpszFacename

	for (int i = 0; i < 4; i++)
	{
		text[i].SetFont(&font_text);
	}
	for (int i = 0; i< 7; i++)
	{
		color_name[i].SetFont(&font_text_big);
		level_data[i].SetFont(&font_text);
	}

	GetDlgItem(IDC_MFCBUTTON_ADMIN_INKSYSTEM_SETUP)->SetFont(&font_text);

	// 컬러 명 Static Text 색깔 입히기
	cbr_lc.CreateSolidBrush(RGB(0, 255, 255));
	cbr_c.CreateSolidBrush(RGB(0, 191, 255));
	cbr_lm.CreateSolidBrush(RGB(255, 192, 255));
	cbr_m.CreateSolidBrush(RGB(255, 0, 255));
	cbr_y.CreateSolidBrush(RGB(255, 255, 0));
	cbr_lk.CreateSolidBrush(RGB(211, 211, 211));
	cbr_k.CreateSolidBrush(RGB(128, 128, 128));

	// 데이터 스케일링
	Scalining();
	CloseHandle(receive_data[6]);
	
	return TRUE;
}
// 다이얼로그 제거 될 때 실행
void DataScaling::OnDestroy()
{
	CDialog::OnDestroy();
	// 다이얼로그 해제
	this->DestroyWindow();
}

void DataScaling::OnOK()
{
	//CDialog::OnOK();
}

void DataScaling::OnCancel()
{
	//CDialog::OnCancel();
}

// 스케일링 함수
int DataScaling::Scalining()
{
	// 레벨 값 Scaling
	// 기울기 연산
	//for (int i = 0; i < 7; i++)
	{
		// LC
		scaling_gradient_in_a[0] = (float)2 / 0.12;
		scaling_gradient_out1_a[0] = (float)2 / 0.12; // y=ax+b >> a
		scaling_gradient_out2_a[0] = (float)2 / 0.12; // y=ax+b >> a

		scaling_gradient_in_b[0] = (float)2 / 0.12; // y=ax+b >> a
		scaling_gradient_out1_b[0] = (float)2 / 0.12; // y=ax+b >> a
		scaling_gradient_out2_b[0] = (float)2 / 0.12; // y=ax+b >> a

		// C
		scaling_gradient_in_a[1] = (float)2 / 0.1;
		scaling_gradient_out1_a[1] = (float)2 / 0.1; // y=ax+b >> a
		scaling_gradient_out2_a[1] = (float)2 / 0.1; // y=ax+b >> a

		scaling_gradient_in_b[1] = (float)2 / 0.1; // y=ax+b >> a
		scaling_gradient_out1_b[1] = (float)2 / 0.1; // y=ax+b >> a
		scaling_gradient_out2_b[1] = (float)2 / 0.1; // y=ax+b >> a

		// LM
		scaling_gradient_in_a[2] = (float)2 / 0.1;
		scaling_gradient_out1_a[2] = (float)2 / 0.1; // y=ax+b >> a
		scaling_gradient_out2_a[2] = (float)2 / 0.1; // y=ax+b >> a

		scaling_gradient_in_b[2] = (float)2 / 0.1; // y=ax+b >> a
		scaling_gradient_out1_b[2] = (float)2 / 0.1; // y=ax+b >> a
		scaling_gradient_out2_b[2] = (float)2 / 0.1; // y=ax+b >> a

		// M
		scaling_gradient_in_a[3] = (float)2.5 / 0.1;
		scaling_gradient_out1_a[3] = (float)2.5 / 0.1; // y=ax+b >> a
		scaling_gradient_out2_a[3] = (float)2.5 / 0.1; // y=ax+b >> a

		scaling_gradient_in_b[3] = (float)2.5 / 0.1; // y=ax+b >> a
		scaling_gradient_out1_b[3] = (float)2.5 / 0.1; // y=ax+b >> a
		scaling_gradient_out2_b[3] = (float)2.5 / 0.1; // y=ax+b >> a

		// Y
		scaling_gradient_in_a[4] = (float)3 / 0.1;
		scaling_gradient_out1_a[4] = (float)3 / 0.1; // y=ax+b >> a
		scaling_gradient_out2_a[4] = (float)3 / 0.1; // y=ax+b >> a

		scaling_gradient_in_b[4] = (float)3 / 0.1; // y=ax+b >> a
		scaling_gradient_out1_b[4] = (float)3 / 0.1; // y=ax+b >> a
		scaling_gradient_out2_b[4] = (float)3 / 0.1; // y=ax+b >> a

		// LK
		scaling_gradient_in_a[5] = (float)4 / 0.1;
		scaling_gradient_out1_a[5] = (float)4 / 0.1; // y=ax+b >> a
		scaling_gradient_out2_a[5] = (float)4 / 0.1; // y=ax+b >> a

		scaling_gradient_in_b[5] = (float)2 / 0.1; // y=ax+b >> a
		scaling_gradient_out1_b[5] = (float)2 / 0.1; // y=ax+b >> a
		scaling_gradient_out2_b[5] = (float)2 / 0.1; // y=ax+b >> a

		// K
		scaling_gradient_in_a[6] = (float)3.5 / 0.1;
		scaling_gradient_out1_a[6] = (float)3.5 / 0.1; // y=ax+b >> a
		scaling_gradient_out2_a[6] = (float)3.5 / 0.1; // y=ax+b >> a

		scaling_gradient_in_b[6] = (float)3.5 / 0.1; // y=ax+b >> a
		scaling_gradient_out1_b[6] = (float)3.5 / 0.1; // y=ax+b >> a
		scaling_gradient_out2_b[6] = (float)3.5 / 0.1; // y=ax+b >> a
	}

	// 나머지 연산
	// 특정 Adam값과 매칭되는 높이를 직접 재서 구한다.
	//(높이 - 기울기 * (Adam)값)
	//for (int i = 0; i < 7; i++)
	{
		// LC
		scaling_remain_in_a[0] = (float)(20 - scaling_gradient_in_a[0] * 1.12);	// y=ax+b >> b
		scaling_remain_out1_a[0] = (float)(11 - scaling_gradient_out1_a[0] * 0.71);	// y=ax+b >> b
		scaling_remain_out2_a[0] = (float)(10 - scaling_gradient_out2_a[0] * 0.55);	// y=ax+b >> b

		scaling_remain_in_b[0] = (float)(18.5 - scaling_gradient_in_b[0] * 1.2);	// y=ax+b >> b
		scaling_remain_out1_b[0] = (float)(11.5 - scaling_gradient_out1_b[0] * 0.62);	// y=ax+b >> b
		scaling_remain_out2_b[0] = (float)(12.5 - scaling_gradient_out2_b[0] * 0.74);	// y=ax+b >> b


		// C
		scaling_remain_in_a[1] = (float)(21 - scaling_gradient_in_a[1] * 1.4);	// y=ax+b >> b
		scaling_remain_out1_a[1] = (float)(10.5 - scaling_gradient_out1_a[1] * 0.8);	// y=ax+b >> b
		scaling_remain_out2_a[1] = (float)(12 - scaling_gradient_out2_a[1] * 1.04);	// y=ax+b >> b

		scaling_remain_in_b[1] = (float)(25 - scaling_gradient_in_b[1] * 1.3);	// y=ax+b >> b
		scaling_remain_out1_b[1] = (float)(14 - scaling_gradient_out1_b[1] * 0.85);	// y=ax+b >> b
		scaling_remain_out2_b[1] = (float)(14 - scaling_gradient_out2_b[1] * 0.85);	// y=ax+b >> b


		// LM
		scaling_remain_in_a[2] = (float)(17 - scaling_gradient_in_a[2] * 0.93);	// y=ax+b >> b
		scaling_remain_out1_a[2] = (float)(11 - scaling_gradient_out1_a[2] * 0.67);	// y=ax+b >> b
		scaling_remain_out2_a[2] = (float)(11.5 - scaling_gradient_out2_a[2] * 0.59);	// y=ax+b >> b

		scaling_remain_in_b[2] = (float)(18.5 - scaling_gradient_in_b[2] * 0.98);	// y=ax+b >> b
		scaling_remain_out1_b[2] = (float)(11.5 - scaling_gradient_out1_b[2] * 0.66);	// y=ax+b >> b
		scaling_remain_out2_b[2] = (float)(9 - scaling_gradient_out2_b[2] * 0.56);	// y=ax+b >> b


		// M
		scaling_remain_in_a[3] = (float)(25 - scaling_gradient_in_a[3] * 1.35);	// y=ax+b >> b
		scaling_remain_out1_a[3] = (float)(15 - scaling_gradient_out1_a[3] * 0.98);	// y=ax+b >> b
		scaling_remain_out2_a[3] = (float)(14.5 - scaling_gradient_out2_a[3] * 0.93);	// y=ax+b >> b

		scaling_remain_in_b[3] = (float)(24 - scaling_gradient_in_b[3] * 1.5);	// y=ax+b >> b
		scaling_remain_out1_b[3] = (float)(14 - scaling_gradient_out1_b[3] * 0.9);	// y=ax+b >> b
		scaling_remain_out2_b[3] = (float)(13.5 - scaling_gradient_out2_b[3] * 1.0);	// y=ax+b >> b


		// Y
		scaling_remain_in_a[4] = (float)(24 - scaling_gradient_in_a[4] * 0.93);	// y=ax+b >> b
		scaling_remain_out1_a[4] = (float)(12 - scaling_gradient_out1_a[4] * 0.51);	// y=ax+b >> b
		scaling_remain_out2_a[4] = (float)(12.5 - scaling_gradient_out2_a[4] * 0.65);	// y=ax+b >> b

		scaling_remain_in_b[4] = (float)(24 - scaling_gradient_in_b[4] * 0.83);	// y=ax+b >> b
		scaling_remain_out1_b[4] = (float)(14.5 - scaling_gradient_out1_b[4] * 0.54);	// y=ax+b >> b
		scaling_remain_out2_b[4] = (float)(14 - scaling_gradient_out2_b[4] * 0.53);	// y=ax+b >> b

		// LK
		scaling_remain_in_a[5] = (float)(22.5 - scaling_gradient_in_a[5] * 0.77);	// y=ax+b >> b
		scaling_remain_out1_a[5] = (float)(11.5 - scaling_gradient_out1_a[5] * 0.45);	// y=ax+b >> b
		scaling_remain_out2_a[5] = (float)(15.5 - scaling_gradient_out2_a[5] * 0.55);	// y=ax+b >> b

		scaling_remain_in_b[5] = (float)(22.5 - scaling_gradient_in_b[5] * 0.74);	// y=ax+b >> b
		scaling_remain_out1_b[5] = (float)(14 - scaling_gradient_out1_b[5] * 0.39);	// y=ax+b >> b
		scaling_remain_out2_b[5] = (float)(12 - scaling_gradient_out2_b[5] * 0.48);	// y=ax+b >> b


		// K
		scaling_remain_in_a[6] = (float)(25 - scaling_gradient_in_a[6] * 0.92);	// y=ax+b >> b
		scaling_remain_out1_a[6] = (float)(15 - scaling_gradient_out1_a[6] * 0.49);	// y=ax+b >> b
		scaling_remain_out2_a[6] = (float)(15 - scaling_gradient_out2_a[6] * 0.52);	// y=ax+b >> b

		scaling_remain_in_b[6] = (float)(23 - scaling_gradient_in_b[6] * 0.65);	// y=ax+b >> b
		scaling_remain_out1_b[6] = (float)(11 - scaling_gradient_out1_b[6] * 0.53);	// y=ax+b >> b
		scaling_remain_out2_b[6] = (float)(11 - scaling_gradient_out2_b[6] * 0.62);	// y=ax+b >> b


	}

	// 스케일링 연산
	// 반드시 j 인덱스 앞에 float 캐스팅을 해줄 것!!
	for (int i = 0; i < 7; i++)
	{
		for (int j = 0; j < 500; j++)
		{
			scaledlevel_in_a[i][j] = (float)scaling_gradient_in_a[i] * ((float)j / 100) + scaling_remain_in_a[i];		// A in 리조버
			scaledlevel_out1_a[i][j] = (float)scaling_gradient_out1_a[i] * ((float)j / 100) + scaling_remain_out1_a[i];	// B out1 리조버
			scaledlevel_out2_a[i][j] = (float)scaling_gradient_out2_a[i] * ((float)j / 100) + scaling_remain_out2_a[i];	// B out2 리조버 

			scaledlevel_in_b[i][j] = (float)scaling_gradient_in_b[i] * ((float)j / 100) + scaling_remain_in_b[i];		// B in리조버
			scaledlevel_out1_b[i][j] = (float)scaling_gradient_out1_b[i] * ((float)j / 100) + scaling_remain_out1_b[i];	// B out1 리조버
			scaledlevel_out2_b[i][j] = (float)scaling_gradient_out2_b[i] * ((float)j / 100) + scaling_remain_out2_b[i];	// B out2 리조버 
		}
	}

	// 유량 값 스케일링
	int maxflow = 300;
	//GetPrivateProfileString("FLOW_ANALOG", "FLOW_MAXVALUE", "0", buf, 256, ".\\config.ini");
	//int flow_maxvalue = atoi(buf); // 테스트용 >> 최대 값 300ml로 가정
	for (int i = 0; i < 65536; i++)
	{
		scaledflow[i] = (double)maxflow * i / 65535;
	}

	// 드럼레벨 스케일링
	// 잉크채워지는 부분 500ml
	// 센서굴뚝부터 잉크 채워지는 시작부분 길이 300ml >> 굴뚝 제거로 인해 140ml로 변경
	for (int i = 0; i < 65536; i++)
	{
		scaleddrumlevel[i] = (double)800 - ((double)i * 0.0068725 + 243.79);
	}

	// 메인잉크레벨 스케일링 ( LC, C, LM, M, Y, LK ,K )
	int iArr_MainkInkMaxLevel[7] = { 48260, 51300, 49000, 51970, 44700, 42075, 43301 };
	for (int i = 0; i < 7; i++)
	{
		for (int j = 0; j < 65536; j++)
		{
			// 테스트용
			m_dbScaled_MainInkLevel[i][j] = ((double)(j - 32768) / (double)(iArr_MainkInkMaxLevel[i] - 32768)) * (double)100;
		}
	}

	// 온도 스케일링
	for (int i = 0; i < 65536; i++)
	{
		scaledtemp[i] = (double)((double)100 / 65535) * i;
	}

	// 압력 스케일링
	for (int i = 0; i < 65536; i++)
	{
		scaledpressure[i] = (double)((double)-101 / 65535) * i;
	}

	return 0;
}

// 관리자 설정 버튼
void DataScaling::OnBnClickedMfcbuttonAdminInksystemSetup()
{
	cadmininksystemsetupdlg = new CAdminInksystemSetupDlg();
	cadmininksystemsetupdlg->Create(IDD_ADMIN_INKSYSTEM_SETUP_DIALOG, this);
	cadmininksystemsetupdlg->ShowWindow(SW_SHOW);		// 설정 창 출력
}


HBRUSH DataScaling::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	switch (pWnd->GetDlgCtrlID())
	{
	case IDC_STATIC_COLORNAME_LC:
		pDC->SetBkColor(RGB(0, 255, 255));
		hbr = (HBRUSH)cbr_lc;
		break;

	case IDC_STATIC_COLORNAME_C:
		pDC->SetBkColor(RGB(0, 191, 255));
		hbr = (HBRUSH)cbr_c;
		break;

	case IDC_STATIC_COLORNAME_LM:
		pDC->SetBkColor(RGB(255, 192, 255));
		hbr = (HBRUSH)cbr_lm;
		break;

	case IDC_STATIC_COLORNAME_M:
		pDC->SetBkColor(RGB(255, 0, 255));
		hbr = (HBRUSH)cbr_m;
		break;

	case IDC_STATIC_COLORNAME_Y:
		pDC->SetBkColor(RGB(255, 255, 0));
		hbr = (HBRUSH)cbr_y;
		break;

	case IDC_STATIC_COLORNAME_LK:
		pDC->SetBkColor(RGB(211, 211, 211));
		hbr = (HBRUSH)cbr_lk;
		break;

	case IDC_STATIC_COLORNAME_K:
		pDC->SetBkColor(RGB(128, 128, 128));
		hbr = (HBRUSH)cbr_k;
		break;

	default:
		break;
	}


	// TODO:  기본값이 적당하지 않으면 다른 브러시를 반환합니다.
	return hbr;
}



