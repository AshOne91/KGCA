#include "Sample.h"
#include "GameWorld.h"
#include "MapManager.h"

bool Sample::Init()
{
	I_GameWorld.Set(_pd3dDevice.Get(), _pImmediateContext.Get(), _pSwapChain.Get());
	I_GameWorld.CInit();
	return true;
}

bool Sample::Frame()
{
	I_GameWorld.CFrame();
	return true;
}

bool Sample::Render()
{
	I_GameWorld.CRender();
	return true;
}

bool Sample::Release()
{
	I_GameWorld.CRelease();
	return true;
}

GAME_RUN(KSHCoreSample, dfSCREEN_WIDTH, dfSCREEN_HEIGHT)