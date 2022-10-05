#include "Sound.h"
#include <tchar.h>
void Sound::Paused()
{
    if (_pChannel == nullptr) return;
    bool paused;
    _pChannel->getPaused(&paused);
    _pChannel->setPaused(!paused);
}

void Sound::VolumeUp(float fVolume)
{
    _fVolume += fVolume;
    _fVolume = (std::min)(1.0f, _fVolume);
    _pChannel->setVolume(_fVolume);
}

void Sound::VolumeDown(float fVolume)
{
    _fVolume -= fVolume;
    _fVolume = (std::max)(0.0f, _fVolume);
    _pChannel->setVolume(_fVolume);
}

bool Sound::Play(bool bLoop)
{
    if (IsPlay() == false)
    {
        FMOD_RESULT hr = _pSystem->playSound(_pSound, nullptr, false, &_pChannel);
        if (hr == FMOD_OK)
        {
            _fVolume = 0.5f;
            _pChannel->setVolume(_fVolume);
            SetLoop(bLoop);
        }
    }
    return true;
}

bool Sound::PlayEffect(bool bLoop)
{
    FMOD_RESULT hr = _pSystem->playSound(_pSound, nullptr, false, &_pChannel);
    //FMOD_RESULT hr = _pSystem->playSound(_pSound, nullptr, false, &_pChannel);
    if (hr == FMOD_OK)
    {
        _fVolume = 0.5f;
        _pChannel->setVolume(_fVolume);
        SetLoop(bLoop);
    }
    return true;
}

void Sound::Stop()
{
    _pChannel->stop();
}

void Sound::SetLoop(bool bLoop)
{
    if (bLoop)
    {
        _pChannel->setMode(FMOD_LOOP_NORMAL);
    }
    else
    {
        _pChannel->setMode(FMOD_LOOP_OFF);
    }
}

bool Sound::IsPlay()
{
    bool playing = false;
    if (_pChannel != nullptr)
    {
        _pChannel->isPlaying(&playing);
    }
    return playing;
}

bool Sound::Load(FMOD::System* pSystem, const std::wstring& filename)
{
    _pSystem = pSystem;
    FMOD_RESULT hr = _pSystem->createSound(to_wm(filename).c_str(), FMOD_DEFAULT, nullptr, &_pSound);
    if (hr == FMOD_OK)
    {
        _pSound->getLength(&_TotalTime, FMOD_TIMEUNIT_MS);
    }
    return true;
}

bool Sound::Init()
{
    return true;
}

bool Sound::Frame()
{
    if (_pChannel)
    {
        unsigned int ms = 0;
        _pChannel->getPosition(&ms, FMOD_TIMEUNIT_MS);
        TCHAR szBuffer[256] = { 0, };
        _stprintf_s(szBuffer, _T("경과시간[% 02d:% 02d : % 02d], 파일크기[% 02d:% 02d : % 02d]"),
            ms / 1000 / 60,
            ms / 1000 % 60,
            ms / 10 % 60,
            _TotalTime / 1000 / 60,
            _TotalTime / 1000 % 60,
            _TotalTime / 10 % 60);
        _szBuffer = szBuffer;
    }
    return true;
}

bool Sound::Render()
{
    return true;
}

bool Sound::Release()
{
    if (_pSound) _pSound->release();
    _pSound = nullptr;
    return true;
}
