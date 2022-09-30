#include "UIManager.h"

void UIManager::Set(ID3D11Device* pd3dDevice, ID3D11DeviceContext* pImmediateContext)
{
	_pd3dDevice = pd3dDevice;
	_pImmediateContext = pImmediateContext;
}

bool UIManager::CInit()
{
	return false;
}

bool UIManager::CFrame()
{
	return false;
}

bool UIManager::CRender()
{
	return false;
}

bool UIManager::CRelease()
{
	return false;
}

bool UIManager::OnEvent(EventType eventType, ComponentObject* pSender, Message* msg)
{
	return false;
}

UIManager::UIManager()
{

}

UIManager::~UIManager()
{
	CRelease();
}