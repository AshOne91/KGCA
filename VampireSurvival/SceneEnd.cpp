#include "SceneTitle.h"
#include "MapObject.h"
#include "GameWorld.h"
#include "SoundManager.h"
#include "Object2DComponent.h"
#include "Writer.h"
#include "SceneMain.h"
#include "SceneEnd.h"

extern bool g_bClear;
void SceneEnd::OnEnter()
{
	I_GameWorld.SetCameraPos({ 0.0f, 0.0f });
	std::wstring mapshader = L"DefaultShape.txt";
	_pBackGround = CreateObject<MapObject>();
	_pBackGround->Create(_pd3dDevice, _pImmediateContext, mapshader, L"../../resource/introBG.png");
	_pBackGround->SetRect({ 0,0, dfSCREEN_WIDTH, dfSCREEN_HEIGHT });
	_pBackGround->SetCameraSize(I_GameWorld.GetViewSize());
	_pBackGround->SetCameraPos(I_GameWorld.GetCameraPos());;

	if (g_bClear == true)
	{
		_pTitle = CreateObject<MapObject>();
		_pTitle->Create(_pd3dDevice, _pImmediateContext, mapshader, L"../../resource/stageComplete.png");
		_pTitle->SetRect({ 0,0, dfSCREEN_WIDTH * 0.5f, dfSCREEN_HEIGHT * 0.3f });
		_pTitle->SetCameraSize(I_GameWorld.GetViewSize());
		_pTitle->SetCameraPos({ I_GameWorld.GetCameraPos() });
		_pTitle->SetPosition({ I_GameWorld.GetCameraPos().x, I_GameWorld.GetCameraPos().y-100.0f });
		_pBackGroundMusic = I_Sound.Load(L"../../resource/sfx/sfx_piano.ogg");
		_pBackGroundMusic->PlayEffect();

	}
	else
	{
		_pTitle = CreateObject<MapObject>();
		_pTitle->Create(_pd3dDevice, _pImmediateContext, mapshader, L"../../resource/gameOver.png");
		_pTitle->SetRect({ 0,0, dfSCREEN_WIDTH * 0.5f, dfSCREEN_HEIGHT * 0.3f });
		_pTitle->SetCameraSize(I_GameWorld.GetViewSize());
		_pTitle->SetCameraPos({ I_GameWorld.GetCameraPos() });
		_pTitle->SetPosition({ I_GameWorld.GetCameraPos().x, I_GameWorld.GetCameraPos().y - 100.0f });
		_pBackGroundMusic = I_Sound.Load(L"../../resource/sfx/VS_GameOver_v02-01.ogg");
		_pBackGroundMusic->PlayEffect();
	}

	_pPressAnyKey = CreateObject<MapObject>();
	_pPressAnyKey->Create(_pd3dDevice, _pImmediateContext, mapshader, L"../../resource/PressEnterToPlay.png");
	_pPressAnyKey->SetRect({ 0.0f, 0.0f, dfSCREEN_WIDTH * 0.5f, dfSCREEN_HEIGHT * 0.2f });
	_pPressAnyKey->SetCameraPos({ I_GameWorld.GetCameraPos() });
	_pPressAnyKey->SetCameraSize(I_GameWorld.GetViewSize());
	_pPressAnyKey->SetPosition({ I_GameWorld.GetCameraPos().x, I_GameWorld.GetCameraPos().y + 200.0f });
}

void SceneEnd::OnExecute()
{
	if (I_Input.GetKey(VK_RETURN) == KEY_PUSH)
	{
		Message msg;
		msg.eventType = EventType::ChangeScene;
		msg._pExtraInfo = &SceneMain::GetInstance();
		I_EventManager.PostNotifycation(EventType::ChangeScene, NotifyType::BroadCast, nullptr, &msg);
	}
}

void SceneEnd::OnExit()
{
	_pBackGroundMusic->Stop();
}
