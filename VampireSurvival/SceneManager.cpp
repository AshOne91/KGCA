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
    if (eventType == EventType::CreateObjectInComponent)
    {
        Scene* pScene = dynamic_cast<Scene*>(CurrentState());
        BaseObject* pObj = static_cast<BaseObject*>(msg->_pExtraInfo);
        ComponentObject* pComponent = dynamic_cast<ComponentObject*>(pObj);
        pScene->AddObject(pComponent);
    }
    if (eventType == EventType::DestroyObjectInComponent)
    {
        Scene* pScene = dynamic_cast<Scene*>(CurrentState());
        unsigned __int64 index = *(static_cast<unsigned __int64*>(msg->_pExtraInfo));
        pScene->RemoveObject(index);
    }
    return true;
}

SceneManager::SceneManager()
{

}

SceneManager::~SceneManager()
{
}
