#include "MapManager.h"
#include "GameWorld.h"
#include "User2D.h"
#include "MapObject.h"
#include "Monster.h"

void MapManager::Set(ID3D11Device* pd3dDevice, ID3D11DeviceContext* pImmediateContext)
{
	_pd3dDevice = pd3dDevice;
	_pImmediateContext = pImmediateContext;
}

void MapManager::mapRotate(MapRotateType rotate)
{
	std::vector<std::vector<MapObject*>> _tempMapList{ dfMAP_Y_COUNT, {dfMAP_X_COUNT, nullptr} };
	switch (rotate)
	{
	case MapRotateType::Up:
	{
		_tempMapList[0][0] = _mapObjectList[2][0];
		_tempMapList[0][1] = _mapObjectList[2][1];
		_tempMapList[0][2] = _mapObjectList[2][2];
		_tempMapList[0][0]->SetPosition(_mapObjectList[0][0]->_vPos - Vector2D(0.0f, _mapObjectList[0][0]->_rtCollision.h));
		_tempMapList[0][1]->SetPosition(_mapObjectList[0][1]->_vPos - Vector2D(0.0f, _mapObjectList[0][0]->_rtCollision.h));
		_tempMapList[0][2]->SetPosition(_mapObjectList[0][2]->_vPos - Vector2D(0.0f, _mapObjectList[0][0]->_rtCollision.h));

		_tempMapList[1][0] = _mapObjectList[0][0];
		_tempMapList[1][1] = _mapObjectList[0][1];
		_tempMapList[1][2] = _mapObjectList[0][2];

		_tempMapList[2][0] = _mapObjectList[1][0];
		_tempMapList[2][1] = _mapObjectList[1][1];
		_tempMapList[2][2] = _mapObjectList[1][2];
		_mapObjectList = _tempMapList;
	}
	break;
	case MapRotateType::Right:
	{
		_tempMapList[0][2] = _mapObjectList[0][0];
		_tempMapList[1][2] = _mapObjectList[1][0];
		_tempMapList[2][2] = _mapObjectList[2][0];
		_tempMapList[0][2]->SetPosition(_mapObjectList[0][2]->_vPos + Vector2D(_mapObjectList[0][0]->_rtCollision.w, 0.0f));
		_tempMapList[1][2]->SetPosition(_mapObjectList[1][2]->_vPos + Vector2D(_mapObjectList[0][0]->_rtCollision.w, 0.0f));
		_tempMapList[2][2]->SetPosition(_mapObjectList[2][2]->_vPos + Vector2D(_mapObjectList[0][0]->_rtCollision.w, 0.0f));

		_tempMapList[0][0] = _mapObjectList[0][1];
		_tempMapList[1][0] = _mapObjectList[1][1];
		_tempMapList[2][0] = _mapObjectList[2][1];

		_tempMapList[0][1] = _mapObjectList[0][2];
		_tempMapList[1][1] = _mapObjectList[1][2];
		_tempMapList[2][1] = _mapObjectList[2][2];
		_mapObjectList = _tempMapList;
	}
	break;
	case MapRotateType::Down:
	{
		_tempMapList[2][0] = _mapObjectList[0][0];
		_tempMapList[2][1] = _mapObjectList[0][1];
		_tempMapList[2][2] = _mapObjectList[0][2];
		_tempMapList[2][0]->SetPosition(_mapObjectList[2][0]->_vPos + Vector2D(0.0f, _mapObjectList[0][0]->_rtCollision.h));
		_tempMapList[2][1]->SetPosition(_mapObjectList[2][1]->_vPos + Vector2D(0.0f, _mapObjectList[0][0]->_rtCollision.h));
		_tempMapList[2][2]->SetPosition(_mapObjectList[2][2]->_vPos + Vector2D(0.0f, _mapObjectList[0][0]->_rtCollision.h));

		_tempMapList[0][0] = _mapObjectList[1][0];
		_tempMapList[0][1] = _mapObjectList[1][1];
		_tempMapList[0][2] = _mapObjectList[1][2];

		_tempMapList[1][0] = _mapObjectList[2][0];
		_tempMapList[1][1] = _mapObjectList[2][1];
		_tempMapList[1][2] = _mapObjectList[2][2];
		_mapObjectList = _tempMapList;
	}
	break;
	case MapRotateType::Left:
	{
		_tempMapList[0][0] = _mapObjectList[0][2];
		_tempMapList[1][0] = _mapObjectList[1][2];
		_tempMapList[2][0] = _mapObjectList[2][2];
		_tempMapList[0][0]->SetPosition(_mapObjectList[0][0]->_vPos - Vector2D(_mapObjectList[0][0]->_rtCollision.w, 0.0f));
		_tempMapList[1][0]->SetPosition(_mapObjectList[1][0]->_vPos - Vector2D(_mapObjectList[0][0]->_rtCollision.w, 0.0f));
		_tempMapList[2][0]->SetPosition(_mapObjectList[2][0]->_vPos - Vector2D(_mapObjectList[0][0]->_rtCollision.w, 0.0f));

		_tempMapList[0][1] = _mapObjectList[0][0];
		_tempMapList[1][1] = _mapObjectList[1][0];
		_tempMapList[2][1] = _mapObjectList[2][0];

		_tempMapList[0][2] = _mapObjectList[0][1];
		_tempMapList[1][2] = _mapObjectList[1][1];
		_tempMapList[2][2] = _mapObjectList[2][1];
		_mapObjectList = _tempMapList;
	}
	break;
	}
}

bool MapManager::Init()
{
    auto pTexture = I_Tex.Load(L"../../resource/bg_forest.png");
    std::wstring mapshader = L"../../data/shader/DefaultShape.txt";
    UINT mapWidth = pTexture->_Desc.Width;
    UINT mapHeight = pTexture->_Desc.Height;
    int MapCenterX = (mapWidth * dfMAP_X_COUNT) * 0.5f;
    int MapCenterY = (mapHeight * dfMAP_Y_COUNT) * 0.5f;
    UINT mapMidWidth = mapWidth * 0.5f;
    UINT mapMidHeight = mapHeight * 0.5f;
	for (int y = 1; y <= dfMAP_Y_COUNT; ++y)
	{
		for (int x = 1; x <= dfMAP_X_COUNT; ++x)
		{
			auto pMapObject = new MapObject;
			pMapObject->Create(_pd3dDevice, _pImmediateContext, mapshader, L"../../resource/bg_forest.png");
			pMapObject->Init();
			pMapObject->SetRect({ 0, 0, (float)mapWidth, (float)mapHeight });
			pMapObject->SetPosition(
				{
					(float)(mapWidth * (x - 1) - mapMidWidth * (x - 1)) + (float)(mapWidth * x - mapMidWidth * x) ,
					(float)(mapHeight * (y - 1) - mapMidHeight * (y - 1)) + (float)(mapHeight * y - mapMidHeight * y) });
			_mapObjectList[y - 1][x - 1] = pMapObject;
			pMapObject->SetMonsterPrototype(new Monster(100, 100));
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

    return true;
}

bool MapManager::Frame()
{
	std::vector<std::pair<int, int>> collisonMap;
	int centerX = dfMAP_X_COUNT * 0.5f;
	int centerY = dfMAP_Y_COUNT * 0.5f;
	for (int y = 0; y < dfMAP_Y_COUNT; ++y)
	{
		for (int x = 0; x < dfMAP_X_COUNT; ++x)
		{
			auto pMapObj = _mapObjectList[y][x];
			pMapObj->SetCameraSize(I_GameWorld.GetViewSize());
			pMapObj->SetCameraPos(I_GameWorld.GetCameraPos());
			pMapObj->Frame();
			if ((centerX != x || centerY != y) && Collision::RectToPoint(pMapObj->_rtCollision, { (long)I_GameWorld.GetUserPtr()->_vPos.x, (long)I_GameWorld.GetUserPtr()->_vPos.y }))
			{
				collisonMap.push_back({ x, y });
			}
		}
	}

	for (auto& collisionMap : collisonMap)
	{
		int x = collisionMap.first;
		int y = collisionMap.second;

		//좌상단
		if ((centerX - 1) == x && (centerY - 1) == y)
		{
			mapRotate(MapRotateType::Left);
			mapRotate(MapRotateType::Up);
		}
		//상단
		if (centerX == x && (centerY - 1) == y)
		{
			mapRotate(MapRotateType::Up);
		}
		//우상단
		if ((centerX + 1) == x && (centerY - 1) == y)
		{
			mapRotate(MapRotateType::Right);
			mapRotate(MapRotateType::Up);
		}
		//우
		if ((centerX + 1) == x && centerY == y)
		{
			mapRotate(MapRotateType::Right);
		}
		//우하단
		if (centerX + 1 == x && centerY + 1 == y)
		{
			mapRotate(MapRotateType::Right);
			mapRotate(MapRotateType::Down);
		}
		//하단
		if (centerX == x && centerY + 1 == y)
		{
			mapRotate(MapRotateType::Down);
		}
		//좌하단
		if (centerX - 1 == x && centerY + 1 == y)
		{
			mapRotate(MapRotateType::Left);
			mapRotate(MapRotateType::Down);
		}
		//좌
		if (centerX - 1 == x && centerY == y)
		{
			mapRotate(MapRotateType::Left);
		}
	}
    return true;
}

bool MapManager::Render()
{
	for (auto& vec : _mapObjectList)
	{
		for (auto pMapObj : vec)
		{
			pMapObj->Render();
		}
	}
    return true;
}

bool MapManager::Release()
{
	for (auto& vec : _mapObjectList)
	{
		for (auto pMapObj : vec)
		{
			pMapObj->Release();
			delete pMapObj;
		}
	}
	_mapObjectList.clear();
    return true;
}

MapManager::MapManager()
{

}

MapManager::~MapManager()
{
	Release();
}
