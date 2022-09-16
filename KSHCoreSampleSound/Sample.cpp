#include "Sample.h"

bool Sample::Init()
{
	//I_Sound.LoadAll(L"../../data/sound/");
	_pBGSound = I_Sound.GetPtr(L"OnlyLove.MP3");
	if (_pBGSound == nullptr)
	{
		_pBGSound = I_Sound.Load(L"../../data/sound/OnlyLove.MP3");
	}
	_pShot = I_Sound.GetPtr(L"GunShot.mp3");
	if (_pShot == nullptr)
	{
		_pShot = I_Sound.Load(L"../../data/sound/GunShot.mp3");
	}
	_pEffect = I_Sound.GetPtr(L"romance.mid");
	if (_pEffect == nullptr)
	{
		_pEffect = I_Sound.Load(L"../../data/sound/romance.mid");
	}
	_pBGSound->Play(true);
	return true;
}

bool Sample::Frame()
{
	I_Sound.Frame();
	if (I_Input.GetKey(VK_HOME) == KEY_PUSH)
	{
		_pShot->PlayEffect();
	}
	if (I_Input.GetKey(VK_INSERT) == KEY_PUSH)
	{
		_pEffect->PlayEffect();
	}
	if (I_Input.GetKey(VK_END) == KEY_PUSH)
	{
		_pBGSound->Stop();
	}
	if (I_Input.GetKey(VK_F1) == KEY_PUSH)
	{
		_pBGSound->Paused();
	}
	if (I_Input.GetKey(VK_F2) == KEY_PUSH)
	{
		_pBGSound->VolumeUp();
	}
	if (I_Input.GetKey(VK_F3) == KEY_PUSH)
	{
		_pBGSound->VolumeDown();
	}
	return true;
}

bool Sample::Render()
{
	_Writer.Draw(0, 100, _pBGSound->_szBuffer);
	return true;
}

bool Sample::Release()
{
	return true;
}

GAME_RUN(KSHCoreSample, 1024, 768)