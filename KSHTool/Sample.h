#pragma once
#include "GameCore.h"
#include "Scene.h"
#include "SceneInGame.h"
#include "SceneTitle.h"
#include "Quadtree.h"
#include "KFbxFile.h"
#include "Character.h"

class Sample : public GameCore
{
public:
	std::shared_ptr<SceneTitle> _pTitle = nullptr;
	std::shared_ptr<SceneInGame> _pInGame = nullptr;
	std::shared_ptr<Scene> _pCurrentScene = nullptr;
	ShapeDirectionLine						_DirLine;
	Quadtree _Quadtree;

	//TFbxFile	m_FBXLoader;
	std::vector< KFbxFile*> _fbxList;
	std::vector< Character*> _NpcList;
	Character* _UserCharacter;

public:
	virtual bool		Init() override;
	virtual bool		Frame() override;
	virtual bool		Render() override;
	virtual bool		Release() override;
	virtual HRESULT CreateDXResource() override;
	void    ClearD3D11DeviceContext(ID3D11DeviceContext* pd3dDeviceContext);
};

