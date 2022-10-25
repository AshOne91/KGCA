#pragma once
#include "BaseObject.h"
#include "CameraDebug.h"

class Map : public BaseObject
{
	DWORD_VECTOR indexlist;
public:
	bool Build(UINT iWidth, UINT iHeight);
	bool UpdateBuffer(CameraDebug* pMainCamera);
};

