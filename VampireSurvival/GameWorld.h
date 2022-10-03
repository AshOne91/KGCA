#pragma once
#include "GameCore.h"
#include "Component.h"

#define dfSCREEN_WIDTH 800
#define dfSCREEN_HEIGHT 600

class User2D;
class Monster;
class GameWorld : public Singleton<GameWorld> , public ComponentObject
{
private:
	ID3D11Device* _pd3dDevice = nullptr;
	ID3D11DeviceContext* _pImmediateContext = nullptr;
	IDXGISwapChain* _pSwapChain = nullptr;
	Vector2D _vSize = { dfSCREEN_WIDTH, dfSCREEN_HEIGHT };
	Vector2D _vCamera = { 0, 0 };
	//User2D* _pUser = nullptr;
	//std::vector<Monster*> _monsterList;

private:
	friend class Singleton<GameWorld>;

public:
	void Set(ID3D11Device* pd3dDevice, ID3D11DeviceContext* pImmediateContext, IDXGISwapChain* pSwapChain);
	ID3D11Device* GetDevice();
	ID3D11DeviceContext* GetDeviceImmediateContext();
	IDXGISwapChain* GetSwapChain();
	Vector2D GetViewSize();
	Vector2D GetCameraPos();
	//User2D* GetUserPtr();
	void SetCameraPos(const Vector2D& vCameraPos);
	//void AddMonster(Monster* pMonster);

public:
	virtual bool CInit() override;
	virtual bool CFrame() override;
	virtual bool CRender() override;
	virtual bool CRelease() override;
	virtual bool OnEvent(EventType eventType, ComponentObject* pSender, Message* msg) override;


private:
	GameWorld();
public:
	~GameWorld();
};

#define I_GameWorld GameWorld::GetInstance()

