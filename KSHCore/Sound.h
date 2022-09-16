#pragma once
//https://www.fmod.com/download#fmodengine
//C:\Program Files (x86)\FMOD SoundSystem\FMOD Studio API Windows\api\core
// inc, lib   -> core ¿¡ º¹»ç

#include "Std.h"
#include "fmod.h"
#include "fmod.hpp"
#include "fmod_errors.h"
#pragma comment (lib, "fmod_vc.lib")

class Sound
{
public:
	std::wstring _szName;

public:
	FMOD::System* _pSystem = nullptr;
	FMOD::Sound* _pSound = nullptr;
	FMOD::Channel* _pChannel = nullptr;
	float _fVolume;
	unsigned int _TotalTime;
	std::wstring _szBuffer;

public:
	void Paused();
	void VolumeUp(float fVolume = 0.1f);
	void VolumeDown(float fVolume = 0.1f);
	bool Play(bool bLoop = false);
	bool PlayEffect(bool bLoop = false);
	void Stop();
	void SetLoop(bool bLoop = false);
	bool IsPlay();

public:
	virtual bool Load(FMOD::System* pSystem, const std::wstring& filename);
	virtual bool Init();
	virtual bool Frame();
	virtual bool Render();
	virtual bool Release();
};

