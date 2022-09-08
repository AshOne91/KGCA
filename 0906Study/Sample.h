#pragma once
#include "GameCore.h"
#include "BaseObject.h"
#include "TextureManager.h"

class Sample : public GameCore
{
public:
	ID3D11SamplerState* g_pDefaultSS;
	std::vector<BaseObject*>	_ObjectList;
	std::vector<Texture*>		_ObjectTextureList;
public:
	virtual bool		Init() override;
	virtual bool		Frame() override;
	virtual bool		Render() override;
	virtual bool		Release() override;
};

