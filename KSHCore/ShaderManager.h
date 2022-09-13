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
	std::map<std::wstring, Shader*> _List;

public:
	Shader* Load(const std::wstring& name);
	Shader* VLoad(const std::wstring& name, std::string funName = "VS");
	Shader* PLoad(const std::wstring& name, std::string funName = "PS");
	bool Release();
private:
	ShaderManager();
public:
	~ShaderManager();
};

#define I_Shader ShaderManager::GetInstance()

