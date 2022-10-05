#include "SceneMain.h"
#include "MapManager.h"
#include "User2DComponent.h"
#include "SoundManager.h"

void SceneMain::OnEnter()
{
	I_Sprite.Load(L"SpriteInfo.txt");
	I_MapManager.CInit();
	_pUser = CreateObject<User2DComponent>();
	_pBackGroundMusic = I_Sound.Load(L"../../resource/sfx/bgm_elrond_plant.ogg");
	_pBackGroundMusic->Play(true);
}

void SceneMain::OnExecute()
{
	I_MapManager.CFrame();
}

void SceneMain::OnExit()
{
	_pBackGroundMusic->Stop();
	I_MapManager.CRelease();
}

