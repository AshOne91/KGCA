#include "Sample.h"
#include "MapObject.h"
static Vector2D vSize = { dfSCREEN_WIDTH, dfSCREEN_HEIGHT };

bool Sample::Init()
{
	auto pTexture = I_Tex.Load(L"../../resource/bg_forest.png");
	std::wstring mapshader = L"../../data/shader/DefaultShape.txt";
	Texture* pMaskTex = I_Tex.Load(L"../../data/bitmap2.bmp");

	UINT mapWidth = pTexture->_Desc.Width;
	UINT mapHeight = pTexture->_Desc.Height;
	int MapCenterX = (mapWidth * dfMAP_X_COUNT) * 0.5f;
	int MapCenterY = (mapHeight * dfMAP_Y_COUNT) * 0.5f;
	UINT mapMidWidth = mapWidth * 0.5f;
	UINT mapMidHeight = mapHeight * 0.5f;
	int iIndex = 0;
	for (int y = 1; y <= dfMAP_Y_COUNT; ++y)
	{
		for (int x = 1; x <= dfMAP_X_COUNT; ++x)
		{
			auto pMapObject = new MapObject;
			pMapObject->Create(_pd3dDevice, _pImmediateContext, mapshader, L"../../resource/bg_forest.png");
			pMapObject->SetRect({ 0, 0, (float)mapWidth, (float)mapHeight });
			pMapObject->SetPosition(
				{
					(float)(mapWidth * (x - 1) - mapMidWidth * (x - 1)) + (float)(mapWidth * x - mapMidWidth * x) ,
					(float)(mapHeight * (y - 1) - mapMidHeight * (y - 1)) + (float)(mapHeight * y - mapMidHeight * y)});
			_mapObjectList[y - 1][x - 1] = pMapObject;
		}
	}

	//중점이동
	for (int y = 0; y < dfMAP_Y_COUNT; ++y)
	{
		for (int x = 0; x < dfMAP_X_COUNT; ++x)
		{
			Vector2D curPos = _mapObjectList[y][x]->_vPos;
			_mapObjectList[y][x]->SetPosition({ curPos.x - MapCenterX, curPos.y - MapCenterY });
		}
	}

	_pUser = new User2D;
	_pUser->Create(_pd3dDevice, _pImmediateContext,
		L"../../data/shader/DefaultShapeMask.txt",
		L"../../data/bitmap1.bmp");
	_pUser->SetMask(pMaskTex);
	_pUser->_fSpeed = 300.0f;
	_pUser->SetRect({ 90, 2, 40, 60 });
	_pUser->SetPosition({ 0.0f,0.0f });
	_vCamera = _pUser->_vPos;

	return true;
}

bool Sample::Frame()
{
	_pUser->Frame();
	_vCamera = _pUser->_vPos;
	_pUser->SetCameraSize(vSize);
	_pUser->SetCameraPos(_vCamera);
	_pUser->SetPosition(_pUser->_vPos, _vCamera);

	int index = 0;
	std::vector<std::pair<int,int>> collisonMap;
	int centerX = dfMAP_X_COUNT * 0.5f;
	int centerY = dfMAP_Y_COUNT * 0.5f;
	for (int y = 0; y < dfMAP_Y_COUNT; ++y)
	{
		for (int x = 0; x < dfMAP_X_COUNT; ++x)
		{
			auto pMapObj = _mapObjectList[y][x];
			pMapObj->SetCameraSize(vSize);
			pMapObj->SetCameraPos(_vCamera);
			pMapObj->Frame();
			if ((centerX != x || centerY != y) && Collision::RectToPoint(pMapObj->_rtCollision, {(long)_pUser->_vPos.x, (long)_pUser->_vPos.y}))
			{
				collisonMap.push_back({ x, y });
			}
		}
	}

	for (auto& collisionMap : collisonMap)
	{
		std::vector<std::vector<MapObject*>> _tempMapList{ dfMAP_Y_COUNT, {dfMAP_X_COUNT, nullptr} };
		int x = collisionMap.first;
		int y = collisionMap.second;

		//좌상단
		if ((centerX - 1) == x && (centerY - 1) == y)
		{
			
		}
		//상단
		if (centerX == x && (centerY - 1) == y)
		{
			_tempMapList[0][0] = _mapObjectList[2][0];
			_tempMapList[0][1] = _mapObjectList[2][1];
			_tempMapList[0][2] = _mapObjectList[2][2];
			_tempMapList[0][0]->SetPosition(_mapObjectList[0][0]->_vPos - Vector2D(0.0f, _mapObjectList[0][0]->_ptImageSize.y));
			_tempMapList[0][1]->SetPosition(_mapObjectList[0][1]->_vPos - Vector2D(0.0f, _mapObjectList[0][0]->_ptImageSize.y));
			_tempMapList[0][2]->SetPosition(_mapObjectList[0][2]->_vPos - Vector2D(0.0f, _mapObjectList[0][0]->_ptImageSize.y));

			_tempMapList[1][0] = _mapObjectList[0][0];
			_tempMapList[1][1] = _mapObjectList[0][1];
			_tempMapList[1][2] = _mapObjectList[0][2];

			_tempMapList[2][0] = _mapObjectList[1][0];
			_tempMapList[2][1] = _mapObjectList[1][1];
			_tempMapList[2][2] = _mapObjectList[1][2];
			_mapObjectList = _tempMapList;
		}
		//우상단
		if ((centerX + 1) == x && (centerY - 1) == y)
		{

		}
		//우
		if ((centerX + 1) == x && centerY == y)
		{
			_tempMapList[0][2] = _mapObjectList[0][0];
			_tempMapList[1][2] = _mapObjectList[1][0];
			_tempMapList[2][2] = _mapObjectList[2][0];


			_tempMapList[0][0] = _mapObjectList[0][1];
			_tempMapList[1][0] = _mapObjectList[1][1];
			_tempMapList[2][0] = _mapObjectList[2][1];

			_tempMapList[0][1] = _mapObjectList[0][2];
			_tempMapList[1][1] = _mapObjectList[1][2];
			_tempMapList[2][1] = _mapObjectList[2][2];
			_mapObjectList = _tempMapList;
		}
		//우하단
		if (centerX + 1 == x && centerY + 1 == y)
		{

		}
		//하단
		if (centerX == x && centerY + 1 == y)
		{
			_tempMapList[2][0] = _mapObjectList[0][0];
			_tempMapList[2][1] = _mapObjectList[0][1];
			_tempMapList[2][2] = _mapObjectList[0][2];


			_tempMapList[0][0] = _mapObjectList[1][0];
			_tempMapList[0][1] = _mapObjectList[1][1];
			_tempMapList[0][2] = _mapObjectList[1][2];

			_tempMapList[1][0] = _mapObjectList[2][0];
			_tempMapList[1][1] = _mapObjectList[2][1];
			_tempMapList[1][2] = _mapObjectList[2][2];
			_mapObjectList = _tempMapList;
		}
		//좌하단
		if (centerX - 1 == x && centerY + 1 == y)
		{

		}
		//좌
		if (centerX - 1 == x && centerY == y)
		{
			_tempMapList[0][0] = _mapObjectList[0][2];
			_tempMapList[1][0] = _mapObjectList[1][2];
			_tempMapList[2][0] = _mapObjectList[2][2];


			_tempMapList[0][1] = _mapObjectList[0][0];
			_tempMapList[1][1] = _mapObjectList[1][0];
			_tempMapList[2][1] = _mapObjectList[2][0];

			_tempMapList[0][2] = _mapObjectList[0][1];
			_tempMapList[1][2] = _mapObjectList[1][1];
			_tempMapList[2][2] = _mapObjectList[2][1];
			_mapObjectList = _tempMapList;
		}
	}

	return true;
}

bool Sample::Render()
{
	for (auto& vec : _mapObjectList)
	{
		for (auto pMapObj : vec)
		{
			pMapObj->Render();
		}
	}

	_pUser->PreRender();
	_pImmediateContext->PSSetShaderResources(1, 1,
		&_pUser->_pMaskTex->_pTextureSRV);
	_pUser->PostRender();
	return true;
}

bool Sample::Release()
{
	return true;
}

GAME_RUN(KSHCoreSample, dfSCREEN_WIDTH, dfSCREEN_HEIGHT)