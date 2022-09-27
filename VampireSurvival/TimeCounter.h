#pragma once
#include <chrono>

class Time
{
public:
	static auto TickCount()
	{
		return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now().time_since_epoch()).count();
	}
};
class TimeCounter
{
private:
	bool _bActive = false;
	__int64 _iDuration;
	__int64 _iTime;

public:
	TimeCounter();
	TimeCounter(int duration);

public:
	bool Start(int duration);
	bool Start();
	bool IsFinished();
	__int64 ProcessTime();
	__int64 RemainTime();
	bool IsActive();
	void SetActive(bool state);
	void ForceFinish();
};

