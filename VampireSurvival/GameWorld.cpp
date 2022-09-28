#include "GameWorld.h"
#include "User2D.h"
#include "Monster.h"

void GameWorld::Set(ID3D11Device* pd3dDevice, ID3D11DeviceContext* pImmediateContext)
{
    _pd3dDevice = pd3dDevice;
    _pImmediateContext = pImmediateContext;
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

User2D* GameWorld::GetUserPtr()
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

bool GameWorld::Init()
{
    
    Texture* pMaskTex = I_Tex.Load(L"../../data/bitmap2.bmp");
    _pUser = new User2D;
    _pUser->Create(_pd3dDevice, _pImmediateContext,
        L"../../data/shader/DefaultShapeMask.txt",
        L"../../data/bitmap1.bmp");
    _pUser->SetMask(pMaskTex);
    _pUser->_fSpeed = 300.0f;
    _pUser->SetRect({ 90, 2, 40, 60 });
    _pUser->SetPosition({ 0.0f,0.0f });
    _vCamera = _pUser->_vPos;
    return true;
}

bool GameWorld::Frame()
{
    _pUser->Frame();
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
    }
    return true;
}

bool GameWorld::Render()
{
    _pUser->PreRender();
    _pImmediateContext->PSSetShaderResources(1, 1,
        &_pUser->_pMaskTex->_pTextureSRV);
    _pUser->PostRender();
    for (auto pMonster : _monsterList)
    {
        pMonster->Render();
    }
    return true;
}

bool GameWorld::Release()
{
    for (auto pMonster : _monsterList)
    {
        pMonster->Release();
        delete pMonster;
    }
    _monsterList.clear();
    return true;
}

GameWorld::GameWorld()
{

}

GameWorld::~GameWorld()
{
    Release();
}
