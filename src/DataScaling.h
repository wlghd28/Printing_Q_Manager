#pragma once

// 잉크 시스템 구조체
typedef struct INKSYSTEM
{
	// A system
	CiLinearGaugeX id_level_out1_a;		// A OUT1 리조버 레벨
	CiLinearGaugeX id_level_in_a;		// A IN 리조버 레벨
	CiLinearGaugeX id_level_out2_a;		// A OUT2 리조버 레벨

	// B system
	CiLinearGaugeX id_level_out1_b;		// B OUT1 리조버 레벨
	CiLinearGaugeX id_level_in_b;		// B IN 리조버 레벨
	CiLinearGaugeX id_level_out2_b;		// B OUT2 리조버 레벨

	// A Pump
	CiLedRectangleX id_pump_out1_a;		// A OUT1 순환펌프
	CiLedRectangleX id_pump_out2_a;		// A OUT2 순환펌프

	// B Pump
	CiLedRectangleX id_pump_out1_b;		// B OUT1 순환펌프
	CiLedRectangleX id_pump_out2_b;		// B OUT2 순환펌프

}INKSYSTEM;

// DataScaling 대화 상자
class DataScaling : public CDialog
{
	DECLARE_DYNAMIC(DataScaling)

public:
	DataScaling(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~DataScaling();

	// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MONITORING_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.
	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnDestroy();
	afx_msg void OnOK();
	afx_msg void OnCancel();
	DECLARE_MESSAGE_MAP()
public:

	// 메서드
	afx_msg void OnBnClickedMfcbuttonAdminInksystemSetup();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);


	// 퍼지 잉크량 관련 변수들
	double in_rejover_level_a[7] = { 0, };
	double in_rejover_level_b[7] = { 0, };


	// 스케일링 관련 변수들
	// 순서대로 (LC, C, LM, M, Y, LK, K)
	double scaledflow[65536];	// 유량 값 스케일링 해서 담을 배열
	double scaleddrumlevel[65536];		//  드럼 레벨 스케일링 해서 담을 배열
	double m_dbScaled_MainInkLevel[7][65536] = { { 0, }, };		// 메인 잉크통 레벨 스케일링 해서 담을 배열
	double scaledtemp[65536];	// 온도 스케일링 해서 담을 배열
	double scaledpressure[65536];	// 압력 스케일링 해서 담을 배열

	// 리조버 레벨 스케일링
	float scaling_gradient_in_a[7] = { 0, }; // y=ax+b >> a
	float scaling_gradient_out1_a[7] = { 0, }; // y=ax+b >> a
	float scaling_gradient_out2_a[7] = { 0, }; // y=ax+b >> a

	float scaling_gradient_in_b[7] = { 0, }; // y=ax+b >> a
	float scaling_gradient_out1_b[7] = { 0, }; // y=ax+b >> a
	float scaling_gradient_out2_b[7] = { 0, }; // y=ax+b >> a

	float scaling_remain_in_a[7] = { 0, };	// y=ax+b >> b
	float scaling_remain_out1_a[7] = { 0, };	// y=ax+b >> b
	float scaling_remain_out2_a[7] = { 0, };	// y=ax+b >> b

	float scaling_remain_in_b[7] = { 0, };	// y=ax+b >> b
	float scaling_remain_out1_b[7] = { 0, };	// y=ax+b >> b
	float scaling_remain_out2_b[7] = { 0, };	// y=ax+b >> b

	float scaledlevel_in_a[7][500];		// A in 리조버
	float scaledlevel_out1_a[7][500];	// B out1 리조버
	float scaledlevel_out2_a[7][500];	// B out2 리조버 

	float scaledlevel_in_b[7][500];		// B in리조버
	float scaledlevel_out1_b[7][500];	// B out1 리조버
	float scaledlevel_out2_b[7][500];	// B out2 리조버 


	// 스케일링 함수
	int Scalining();
};
