#include "Sample.h"
#include "GameWorld.h"
#include "MapManager.h"

bool Sample::Init()
{
	I_GameWorld.Set(_pd3dDevice.Get(), _pImmediateContext.Get());
	I_MapManager.Set(_pd3dDevice.Get(), _pImmediateContext.Get());
	I_GameWorld.Init();
	I_MapManager.Init();
	return true;
}

bool Sample::Frame()
{
	I_MapManager.Frame();
	I_GameWorld.Frame();
	return true;
}

bool Sample::Render()
{
	I_MapManager.Render();
	I_GameWorld.Render();
	return true;
}

bool Sample::Release()
{
	I_MapManager.Release();
	I_GameWorld.Release();
	return true;
}

GAME_RUN(KSHCoreSample, dfSCREEN_WIDTH, dfSCREEN_HEIGHT)