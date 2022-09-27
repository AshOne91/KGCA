#include "TimeCounter.h"

TimeCounter::TimeCounter():_bActive(false), _iDuration(0), _iTime(0)
{
}

TimeCounter::TimeCounter(int duration):_bActive(false), _iDuration(duration), _iTime(0)
{
}

bool TimeCounter::Start(int duration)
{
    if (duration >= 0)
    {
        _iDuration = duration;
        _iTime = Time::TickCount();
        _bActive = true;
        return true;
    }
    return false;
}

bool TimeCounter::Start()
{
    if (_iDuration >= 0)
    {
        _iTime = Time::TickCount();
        _bActive = true;
        return true;
    }

    return false;
}

bool TimeCounter::IsFinished()
{
    if (IsActive() == false)
    {
        return false;
    }

    if (_iDuration <= ProcessTime())
    {
        _bActive = false;
        return true;
    }

    return false;
}

__int64 TimeCounter::ProcessTime()
{
    return Time::TickCount() - _iTime;
}

__int64 TimeCounter::RemainTime()
{
    if (IsActive() != false)
    {
        return _iDuration - ProcessTime();
    }

    return 0;
}

bool TimeCounter::IsActive()
{
    return _bActive;
}

void TimeCounter::SetActive(bool state)
{
    _bActive = state;
}

void TimeCounter::ForceFinish()
{
    _iDuration = 0;
}
