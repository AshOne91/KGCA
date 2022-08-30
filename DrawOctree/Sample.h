#pragma once
#include "TDevice.h"
#include "TBaseObject.h"
#include "TGameCore.cpp"
class Sample : public TDevice
{
	TGameCore<TObject> game3D;
	TGameCore<TObject2D> game2D;
	TBaseObject		m_object;
public:
	bool		Init(); // 초기화
	bool		Frame();// 실시간 계산
	bool		Render();// 실시간 랜더링
	bool		Release();// 소멸 및 삭제
};

