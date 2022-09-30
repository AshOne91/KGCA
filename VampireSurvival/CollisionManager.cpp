#include "CollisionManager.h"

void CollisionManager::Set(ID3D11Device* pd3dDevice, ID3D11DeviceContext* pImmediateContext)
{
	_pd3dDevice = pd3dDevice;
	_pImmediateContext = pImmediateContext;
}

bool CollisionManager::CInit()
{
	return true;
}

bool CollisionManager::CFrame()
{
	return true;
}

bool CollisionManager::CRender()
{
	return true;
}

bool CollisionManager::CRelease()
{
	return true;
}

bool CollisionManager::OnEvent(EventType eventType, ComponentObject* pSender, Message* msg)
{
	return false;
}

CollisionManager::CollisionManager()
{

}

CollisionManager::~CollisionManager()
{
	CRelease();
}