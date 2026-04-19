#include "pch.h"
#include "Q_Manager_DK.h"
#include "Q_Manager_DKDlg.h"
#include "CIoDlg.h"
#include "afxdialogex.h"

// AdamIO의 IO 명령이 성공률이 약 70%인 관계로 소프트웨어적으로 시스템 동작 신뢰성을 확보하기 위한 코드
UINT CIoDlg::ThreadDo5050Control(LPVOID _method)    
{
	// 다이얼로그 인스턴스
	CIoDlg *ciodlg = (CIoDlg*)_method;

	// 부모 다이얼로그 Q_Manager 인스턴스 데이터를 받아온다.
	CQManagerDKDlg * qmdlg = (CQManagerDKDlg *)AfxGetApp()->GetMainWnd();

	int i = 0;
	int colorindex = 0;

	while (1)
	{
		// 스레드 스위치
		if (!qmdlg->thread_switch)
			break;

        // AdamLib 초기화 성공했을 시 실행
		if (qmdlg->adamlib_connect_inksystem_switch[colorindex])
		{
			// 퍼지 스위치가 OFF일 경우
			// 주기적으로 퍼지를 0으로 때려준다. (퍼지는 멈춤명령이 실패할 경우 시스템에 치명적이므로 주기적으로 OFF 명령을 날려준다.)
			if (!qmdlg->purge_start_switch[colorindex])
			{
                qmdlg->adamlib[colorindex]->SetValues_5050(0, 0);
                qmdlg->Wait(500, 1);
			}
			// 퍼지 스위치가 ON일 경우
			else
			{
                bool isSuccess = false;
                // qmdlg->io_validation >> 계속 실패할 경우 무한정 대기할 수는 없기 때문에 일정 횟수 이상 실패할 경우 사용자에게 오류를 알려주고 동작을 멈춘다.
				for (i = 0; i < qmdlg->io_validation; i++)
				{
					if (qmdlg->adamlib[colorindex]->SetValues_5050(qmdlg->purge_switch_a[colorindex], qmdlg->purge_switch_b[colorindex]))
                    {
                        isSuccess = true;
						break;
                    }
					qmdlg->Wait(100, 1);
				}
                if(!isSuccess) qmdlg->SendError(ERROR_PURGE);
				qmdlg->Wait(qmdlg->purgetime, 1);
				for (i = 0; i < qmdlg->io_validation; i++)
				{
					if (qmdlg->adamlib[colorindex]->SetValues_5050(0, 0))
						break;
					qmdlg->Wait(100, 1);
				}
                qmdlg->purge_start_switch[colorindex] = false;
			}
		}
		else
			qmdlg->Wait(3000, 1);
	}

    // 스레드 종료 확인 변수
	qmdlg->thread_quit[7] = true;
	return 0;
}
