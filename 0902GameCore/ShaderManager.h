#pragma once
#include "Shader.h"
class ShaderManager : public Singleton<ShaderManager>
{
public:
	ID3D11Device* _pd3dDevice = nullptr;
	ID3D11DeviceContext* _pImmediateContext = nullptr;
	void SetDevice(ID3D11Device* pd3dDevice, ID3D11DeviceContext* pContext);

private:
	friend class Singleton<ShaderManager>;
	std::map<std::wstring, Shader*> _list;

public:
	Shader* Load(const std::wstring& name);
	bool Release();

private:
	ShaderManager();
public:
	~ShaderManager();
};

#define I_Shader ShaderManager::GetInstance()

