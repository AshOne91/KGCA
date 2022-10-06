#include "GameWorld.h"
#include "User2D.h"
#include "Monster.h"
#include "CollisionManager.h"
#include "EventManager.h"
#include "MapManager.h"
#include "ObjectManager.h"
#include "UIManager.h"
#include "SceneManager.h"
#include "SceneTitle.h"
#include "TextManager.h"

void GameWorld::Set(ID3D11Device* pd3dDevice, ID3D11DeviceContext* pImmediateContext, IDXGISwapChain* pSwapChain)
{
    _pd3dDevice = pd3dDevice;
    _pImmediateContext = pImmediateContext;
    _pSwapChain = pSwapChain;
    I_SceneManager.Set(_pd3dDevice, _pImmediateContext);
    I_CollisionManager.Set(_pd3dDevice, _pImmediateContext);
    I_EventManager.Set(_pd3dDevice, _pImmediateContext);
    //I_MapManager.Set(_pd3dDevice, _pImmediateContext);
    I_ObjectManager.Set(_pd3dDevice, _pImmediateContext);
    I_UIManager.Set(_pd3dDevice, _pImmediateContext);
    I_TextManager.Set(_pd3dDevice, _pImmediateContext, _pSwapChain);
}

ID3D11Device* GameWorld::GetDevice()
{
    return _pd3dDevice;
}

ID3D11DeviceContext* GameWorld::GetDeviceImmediateContext()
{
    return _pImmediateContext;
}

IDXGISwapChain* GameWorld::GetSwapChain()
{
    return _pSwapChain;
}

Vector2D GameWorld::GetViewSize()
{
    return _vSize;
}

Vector2D GameWorld::GetCameraPos()
{
    return _vCamera;
}

/*User2D* GameWorld::GetUserPtr()
{
    return _pUser;
}*/

void GameWorld::SetCameraPos(const Vector2D& vCameraPos)
{
    _vCamera = vCameraPos;
}

/*void GameWorld::AddMonster(Monster* pMonster)
{
    //_monsterList.push_back(pMonster);
}*/

bool GameWorld::CInit()
{
    I_EventManager.CInit();
    I_EventManager.GetInstance().AddListener(EventType::CreateObject, &(I_ObjectManager));
    I_EventManager.GetInstance().AddListener(EventType::CreateObject, &(I_CollisionManager));
    I_EventManager.GetInstance().AddListener(EventType::CreateObject, &(I_UIManager));
    I_EventManager.GetInstance().AddListener(EventType::DestroyObject, &(I_ObjectManager));
    I_EventManager.GetInstance().AddListener(EventType::DestroyObject, &(I_CollisionManager));
    I_EventManager.GetInstance().AddListener(EventType::DestroyObject, &(I_UIManager));
    I_EventManager.GetInstance().AddListener(EventType::CreateComponent, &(I_ObjectManager));
    I_EventManager.GetInstance().AddListener(EventType::CreateComponent, &(I_CollisionManager));
    I_EventManager.GetInstance().AddListener(EventType::CreateComponent, &(I_UIManager));
    I_EventManager.GetInstance().AddListener(EventType::AddComponent, &(I_ObjectManager));
    I_EventManager.GetInstance().AddListener(EventType::AddComponent, &(I_CollisionManager));
    I_EventManager.GetInstance().AddListener(EventType::AddComponent, &(I_UIManager));
    I_EventManager.GetInstance().AddListener(EventType::ReleaseComponent, &(I_ObjectManager));
    I_EventManager.GetInstance().AddListener(EventType::ReleaseComponent, &(I_CollisionManager));
    I_EventManager.GetInstance().AddListener(EventType::ReleaseComponent, &(I_UIManager));
    I_EventManager.GetInstance().AddListener(EventType::ChangeScene, &(I_SceneManager));
    I_EventManager.GetInstance().AddListener(EventType::CreateObjectInComponent, &(I_ObjectManager));
    I_EventManager.GetInstance().AddListener(EventType::CreateObjectInComponent, &(I_SceneManager));
    I_EventManager.GetInstance().AddListener(EventType::DestroyObjectInComponent, &(I_ObjectManager));
    I_EventManager.GetInstance().AddListener(EventType::DestroyObjectInComponent, &(I_SceneManager));
    I_TextManager.CInit();
    I_SceneManager.SetCurrentState(&SceneTitle::GetInstance());
    I_ObjectManager.CInit();
    I_CollisionManager.CInit();
    I_UIManager.CInit();
    I_SceneManager.CInit();
    return true;
}

bool GameWorld::CFrame()
{
    I_SceneManager.CFrame();
    I_CollisionManager.CFrame();
    I_EventManager.CFrame();
    I_ObjectManager.CFrame();
    I_UIManager.CFrame();
    I_TextManager.CFrame();
    return true;
}

bool GameWorld::CRender()
{
    I_SceneManager.CRender();
    I_CollisionManager.CRender();
    I_EventManager.CRender();
    I_ObjectManager.CRender();
    I_UIManager.CRender();
    I_TextManager.CRender();
    return true;
}

bool GameWorld::CRelease()
{
    I_SceneManager.CRelease();
    I_CollisionManager.CRelease();
    I_EventManager.CRelease();
    I_ObjectManager.CRelease();
    I_UIManager.CRelease();
    I_TextManager.CRelease();
    return true;
}

bool GameWorld::OnEvent(EventType eventType, ComponentObject* pSender, Message* msg)
{
    return true;
}

GameWorld::GameWorld()
{

}

GameWorld::~GameWorld()
{

}
