#pragma once
#include <GameCore.h>
#include "KFbxFile.h"
#include "CameraDebug.h"
#include "Character.h"

class Sample : public GameCore
{
	//FbxLoader _FBXLoader;
	std::vector<KFbxFile*> _fbxList;
	std::vector<Character*> _NpcList;
	Character* _UserCharacter;
	CameraDebug* _pMainCamera;

public:
	virtual bool Init() final;
	virtual bool Frame() final;
	virtual bool Render() final;
	virtual bool Release() final;
	void ClearD3D11DeviceContext(ID3D11DeviceContext* pd3dDeviceContext);
};
