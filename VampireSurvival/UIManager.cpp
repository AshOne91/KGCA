#include "UIManager.h"

void UIManager::Set(ID3D11Device* pd3dDevice, ID3D11DeviceContext* pImmediateContext)
{
	_pd3dDevice = pd3dDevice;
	_pImmediateContext = pImmediateContext;
}

bool UIManager::CInit()
{
	for (auto& pair : _uiList)
	{
		pair.second->CInit();
	}
	return true;
}

bool UIManager::CFrame()
{
	for (auto& pair : _uiList)
	{
		pair.second->CFrame();
	}
	return true;
}

bool UIManager::CRender()
{
	for (auto& pair : _uiList)
	{
		pair.second->CRender();
	}
	return true;
}

bool UIManager::CRelease()
{
	for (auto& pair : _uiList)
	{
		pair.second->CRelease();
		delete pair.second;
	}
	_uiList.clear();
	return true;
}

bool UIManager::OnEvent(EventType eventType, ComponentObject* pSender, Message* msg)
{
	return true;
}

UIManager::UIManager()
{

}

UIManager::~UIManager()
{
	CRelease();
}