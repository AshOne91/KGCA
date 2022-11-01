#pragma once
#include <GameCore.h>
#include "FbxLoader.h"
#include "CameraDebug.h"

class Sample : public GameCore
{
	//FbxLoader _FBXLoader;
	std::vector<FbxLoader*> _fbxList;
	CameraDebug* _pMainCamera;

public:
	virtual bool Init() final;
	virtual bool Frame() final;
	virtual bool Render() final;
	virtual bool Release() final;
};
