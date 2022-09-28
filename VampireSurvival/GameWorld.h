#pragma once
#include "GameCore.h"

#define dfSCREEN_WIDTH 800
#define dfSCREEN_HEIGHT 600

class User2D;
class Monster;
class GameWorld : public Singleton<GameWorld>
{
private:
	ID3D11Device* _pd3dDevice = nullptr;
	ID3D11DeviceContext* _pImmediateContext = nullptr;
	Vector2D _vSize = { dfSCREEN_WIDTH, dfSCREEN_HEIGHT };
	Vector2D _vCamera = { 0, 0 };
	User2D* _pUser = nullptr;
	std::vector<Monster*> _monsterList;

private:
	friend class Singleton<GameWorld>;

public:
	void Set(ID3D11Device* pd3dDevice, ID3D11DeviceContext* pImmediateContext);
	ID3D11Device* GetDevice();
	ID3D11DeviceContext* GetDeviceImmediateContext();
	Vector2D GetViewSize();
	Vector2D GetCameraPos();
	User2D* GetUserPtr();
	void SetCameraPos(const Vector2D& vCameraPos);
	void AddMonster(Monster* pMonster);

public:
	bool Init();
	bool Frame();
	bool Render();
	bool Release();

private:
	GameWorld();
public:
	~GameWorld();
};

#define I_GameWorld GameWorld::GetInstance()

