#pragma once
#include <windows.h>

class TTimer
{
private:
	LARGE_INTEGER	m_Frequency;	// 초당 주파수 
	LARGE_INTEGER	m_Current;		// 현재 시간 
	LARGE_INTEGER	m_Frame;		// 이전 프레임의 시간 체크 
	float			m_fSecPerFrame;	// 프레임 경과 시간 

	LARGE_INTEGER	m_FPS;				// FPS 체크 타이머		
	int				m_iFramePerSecond;	// 초당 프레임	
	int				m_iFPSElapse;		// 초당 경과된 프레임 


	LARGE_INTEGER	m_Start;		// 이벤트 타이머 시작 시간
	LARGE_INTEGER	m_Elapse;		// 이베트 타이머 경과 시간
	bool			m_bStarted;			// 이벤트 타이머 작동여부
	float			m_fEventTime;


public:
	// 엔진코어에서 사용하는 지원함수
	bool	Init();
	bool	Frame();
	bool	Render();
	bool	Release();

	// 경과한 시간에 대한 지원 함수들
	void	Reset();
	void	Start();
	void	Stop();
	bool	IsStarted() const;
	float	GetElapsedTime();

	// FPS
	int				GetFPS();
	float			GetSPF();

public:
	TTimer();
	~TTimer();
};
