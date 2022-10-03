#include "SceneManager.h"

void SceneManager::Set(ID3D11Device* pd3dDevice, ID3D11DeviceContext* pImmediateContext)
{
    _pd3dDevice = pd3dDevice;
    _pImmediateContext = pImmediateContext;
}

bool SceneManager::CInit()
{
    CurrentState()->Enter();
    return true;
}

bool SceneManager::CFrame()
{
    Excute();
    return true;
}

bool SceneManager::CRender()
{
    return true;
}

bool SceneManager::CRelease()
{
    return true;
}

bool SceneManager::OnEvent(EventType eventType, ComponentObject* pSender, Message* msg)
{
    if (eventType == EventType::ChangeScene)
    {
        ChangeState(static_cast<State*>(msg->_pExtraInfo));
    }
    return true;
}

SceneManager::SceneManager()
{

}

SceneManager::~SceneManager()
{
}
