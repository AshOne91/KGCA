#pragma once
#include "GameCore.h"
#include "Component.h"

#define dfMAP_X_COUNT 3
#define dfMAP_Y_COUNT 3

class MapObject;
class Monster;
enum class MapRotateType;
class MapManager : public Singleton<MapManager>, public ComponentObject
{
private:
	ID3D11Device* _pd3dDevice = nullptr;
	ID3D11DeviceContext* _pImmediateContext = nullptr;
	std::vector<std::vector<MapObject*>> _mapObjectList{ dfMAP_Y_COUNT, {dfMAP_X_COUNT, nullptr} };

private:
	friend class Singleton<MapManager>;

public:
	void Set(ID3D11Device* pd3dDevice, ID3D11DeviceContext* pImmediateContext);

private:
	void mapRotate(MapRotateType rotate);

public:
	virtual bool CInit() override;
	virtual bool CFrame() override;
	virtual bool CRender() override;
	virtual bool CRelease() override;
	virtual bool OnEvent(EventType eventType, ComponentObject* pSender, Message* msg) override;

public:
	MapManager();
	~MapManager();
};

#define I_MapManager MapManager::GetInstance()

