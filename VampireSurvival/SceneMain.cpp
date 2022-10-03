#include "SceneMain.h"
#include "MapManager.h"

void SceneMain::OnEnter()
{
	I_MapManager.CInit();
}

void SceneMain::OnExecute()
{
	I_MapManager.CFrame();
}

void SceneMain::OnExit()
{
	I_MapManager.CRelease();
}

