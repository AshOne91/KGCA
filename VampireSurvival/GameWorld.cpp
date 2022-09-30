#include "GameWorld.h"
#include "User2DComponent.h"
#include "Monster.h"
#include "CollisionManager.h"
#include "EventManager.h"
#include "MapManager.h"
#include "ObjectManager.h"
#include "UIManager.h"

void GameWorld::Set(ID3D11Device* pd3dDevice, ID3D11DeviceContext* pImmediateContext)
{
    _pd3dDevice = pd3dDevice;
    _pImmediateContext = pImmediateContext;
    I_CollisionManager.Set(_pd3dDevice, _pImmediateContext);
    I_EventManager.Set(_pd3dDevice, _pImmediateContext);
    I_MapManager.Set(_pd3dDevice, _pImmediateContext);
    I_ObjectManager.Set(_pd3dDevice, _pImmediateContext);
    I_UIManager.Set(_pd3dDevice, _pImmediateContext);
}

ID3D11Device* GameWorld::GetDevice()
{
    return _pd3dDevice;
}

ID3D11DeviceContext* GameWorld::GetDeviceImmediateContext()
{
    return _pImmediateContext;
}

Vector2D GameWorld::GetViewSize()
{
    return _vSize;
}

Vector2D GameWorld::GetCameraPos()
{
    return _vCamera;
}

User2DComponent* GameWorld::GetUserPtr()
{
    return _pUser;
}

void GameWorld::SetCameraPos(const Vector2D& vCameraPos)
{
    _vCamera = vCameraPos;
}

void GameWorld::AddMonster(Monster* pMonster)
{
    _monsterList.push_back(pMonster);
}

bool GameWorld::CInit()
{
    I_EventManager.CInit();
    I_EventManager.GetInstance().AddListener(EventType::CreateObject, &(I_ObjectManager.GetInstance()));
    I_EventManager.GetInstance().AddListener(EventType::CreateObject, &(I_CollisionManager.GetInstance()));
    I_EventManager.GetInstance().AddListener(EventType::CreateObject, &(I_MapManager.GetInstance()));
    I_EventManager.GetInstance().AddListener(EventType::CreateObject, &(I_UIManager.GetInstance()));
    I_ObjectManager.CInit();
    I_CollisionManager.CInit();
    I_MapManager.CInit();
    I_UIManager.CInit();
    AddComponent(&I_EventManager);
    AddComponent(&I_ObjectManager);
    AddComponent(&I_CollisionManager);
    AddComponent(&I_MapManager); //Render시스템이 없어 Map부터 넣어줘야 된다.(뒤에서 깔아줘야 되서)
    AddComponent(&I_UIManager);
    _pUser = I_ObjectManager.CreateObject<User2DComponent>();
    _vCamera = _pUser->_vPos;

    /*Texture* pMaskTex = I_Tex.Load(L"../../data/bitmap2.bmp");
    _pUser = new User2D;
    _pUser->Create(_pd3dDevice, _pImmediateContext,
        L"../../data/shader/DefaultShapeMask.txt",
        L"../../data/bitmap1.bmp");
    _pUser->SetMask(pMaskTex);
    _pUser->_fSpeed = 300.0f;
    _pUser->SetRect({ 90, 2, 40, 60 });
    _pUser->SetPosition({ 0.0f,0.0f });
    _vCamera = _pUser->_vPos;*/
    return true;
}

bool GameWorld::CFrame()
{
    I_CollisionManager.CFrame();
    I_EventManager.CFrame();
    I_MapManager.CFrame();
    I_ObjectManager.CFrame();
    I_UIManager.CFrame();
    /*_pUser->Frame();
    _vCamera = _pUser->_vPos;
    _pUser->SetCameraSize(_vSize);
    _pUser->SetCameraPos(_vCamera);
    _pUser->SetPosition(_pUser->_vPos, _vCamera);
    for (auto pMonster : _monsterList)
    {
        pMonster->Frame();
        pMonster->SetCameraSize(_vSize);
        pMonster->SetCameraPos(_vCamera);
        pMonster->SetPosition(pMonster->_vPos, _vCamera);
    }*/
    return true;
}

bool GameWorld::CRender()
{
    ComponentObject::CRender();
    /*_pUser->PreRender();
    _pImmediateContext->PSSetShaderResources(1, 1,
        &_pUser->_pMaskTex->_pTextureSRV);
    _pUser->PostRender();
    for (auto pMonster : _monsterList)
    {
        pMonster->Render();
    }*/
    return true;
}

bool GameWorld::CRelease()
{
    ComponentObject::CRelease();
    /*for (auto pMonster : _monsterList)
    {
        pMonster->Release();
        delete pMonster;
    }
    _monsterList.clear();*/
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
    CRelease();
}
