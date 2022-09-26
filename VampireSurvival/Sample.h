#pragma once
#include "GameCore.h"
#include "User2D.h"
#define dfSCREEN_WIDTH 800
#define dfSCREEN_HEIGHT 600
#define dfMAP_X_COUNT 3
#define dfMAP_Y_COUNT 3

class MapObject;
class Sample : public GameCore
{
private:
	Vector2D _vCamera = { 0, 0 };
	User2D* _pUser = nullptr;
	std::vector<std::vector<MapObject*>> _mapObjectList{dfMAP_Y_COUNT, {dfMAP_X_COUNT, nullptr}};

public:
	virtual bool Init() final;
	virtual bool Frame() final;
	virtual bool Render() final;
	virtual bool Release() final;
};
