#pragma once
#include "BaseObject.h"
#include "CameraDebug.h"

class Map : public BaseObject
{
public:
	DWORD _dwNumRows;
	DWORD _dwNumColumns;
	DWORD_VECTOR indexlist;
public:
	bool Build(UINT iWidth, UINT iHeight);
	bool UpdateBuffer(CameraDebug* pMainCamera);
};

