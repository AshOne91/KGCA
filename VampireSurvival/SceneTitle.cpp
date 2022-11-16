#include "SceneTitle.h"
#include "MapObject.h"
#include "GameWorld.h"
#include "SoundManager.h"
#include "Object2DComponent.h"
#include "Writer.h"
#include "SceneMain.h"

void SceneTitle::OnEnter()
{
	I_GameWorld.SetCameraPos({ 0.0f, 0.0f });
	std::wstring mapshader = L"DefaultShape.txt";
	_pBackGround = CreateObject<MapObject>();
	_pBackGround->Create(_pd3dDevice, _pImmediateContext, mapshader, L"../../resource/introBG.png");
	_pBackGround->SetRect({0,0, dfSCREEN_WIDTH, dfSCREEN_HEIGHT});
	_pBackGround->SetCameraSize(I_GameWorld.GetViewSize());
	_pBackGround->SetCameraPos(I_GameWorld.GetCameraPos());
	//_pBackGround->SetPosition({-100.0f, 0.0f});

	_pMan2 = CreateObject<Object2DComponent>();
	_pMan2->Create(_pd3dDevice, _pImmediateContext, mapshader, L"../../resource/illustrations.png");
	_pMan2->SetRect({ 0.0f, 0.0f, 320.0f, 191.0f });
	_pMan2->SetCameraPos(I_GameWorld.GetCameraPos());
	_pMan2->SetCameraSize(I_GameWorld.GetViewSize());
	_pMan2->SetPosition({ 0.0f, -200.0f }, I_GameWorld.GetCameraPos());

	_pTitle = CreateObject<MapObject>();
	_pTitle->Create(_pd3dDevice, _pImmediateContext, mapshader, L"../../resource/title.png");
	_pTitle->SetRect({ 0,0, dfSCREEN_WIDTH * 0.5f, dfSCREEN_HEIGHT * 0.3f});
	_pTitle->SetCameraSize(I_GameWorld.GetViewSize());
	_pTitle->SetCameraPos(I_GameWorld.GetCameraPos());
	_pTitle->SetPosition({ 0.0f, -100.0f });

	_pMan = CreateObject<Object2DComponent>();
	_pMan->Create(_pd3dDevice, _pImmediateContext, mapshader, L"../../resource/illustrations.png");
	_pMan->SetRect({0.0f, 192.0f, 196.0f, 284.0f});
	_pMan->SetCameraPos(I_GameWorld.GetCameraPos());
	_pMan->SetCameraSize(I_GameWorld.GetViewSize());
	_pMan->SetPosition({ 0.0f, 150.0f }, I_GameWorld.GetCameraPos());

	_pWoman = CreateObject<Object2DComponent>();
	_pWoman->Create(_pd3dDevice, _pImmediateContext, mapshader, L"../../resource/illustrations.png");
	_pWoman->SetRect({ 193.0f, 198.0f, 220.0f, 195.0f });
	_pWoman->SetCameraPos(I_GameWorld.GetCameraPos());
	_pWoman->SetCameraSize(I_GameWorld.GetViewSize());
	_pWoman->SetPosition({ -300.0f, -100.0f }, I_GameWorld.GetCameraPos());

	_pPressAnyKey = CreateObject<MapObject>();
	_pPressAnyKey->Create(_pd3dDevice, _pImmediateContext, mapshader, L"../../resource/PressEnterToPlay.png");
	_pPressAnyKey->SetRect({ 0.0f, 0.0f, dfSCREEN_WIDTH * 0.5f, dfSCREEN_HEIGHT * 0.2f });
	_pPressAnyKey->SetCameraPos(I_GameWorld.GetCameraPos());
	_pPressAnyKey->SetCameraSize(I_GameWorld.GetViewSize());
	_pPressAnyKey->SetPosition({ 0.0f, 200.0f });

	_pBackGroundMusic = I_Sound.Load(L"../../resource/sfx/VS_Music_v04-01.ogg");
	_pBackGroundMusic->Play(false);
}

void SceneTitle::OnExecute()
{
	if (I_Input.GetKey(VK_RETURN) == KEY_PUSH)
	{
		Message msg;
		msg.eventType = EventType::ChangeScene;
		msg._pExtraInfo = &SceneMain::GetInstance();
		I_EventManager.PostNotifycation(EventType::ChangeScene, NotifyType::BroadCast, nullptr, &msg);
	}
}

void SceneTitle::OnExit()
{
	_pBackGroundMusic->Stop();
}
