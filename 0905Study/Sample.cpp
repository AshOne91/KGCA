#include "Sample.h"
#include "TextureManager.h"
#include "ShaderManager.h"
#include "Input.h"
#include "Timer.h"
#include "Collision.h"

bool Object2D::Frame()
{
    return true;
}

void Object2D::SetRect(const Rect& rt)
{
    _rtInit = rt;
    //텍스쳐 크기
    _ptImageSize.x = _pTexture->_Desc.Width;
    _ptImageSize.y = _pTexture->_Desc.Height;

    //전체 텍스쳐 크기에서 0~1사이의 값 셋팅(얻어올 텍스쳐 스프라이트의 좌표)
    // 90 -> 0 ~ 1
    _rtUV.x1 = rt.x1 / _ptImageSize.x; // u
    _rtUV.y1 = rt.y1 / _ptImageSize.y; // v
    _rtUV.w = rt.w / _ptImageSize.x;
    _rtUV.h = rt.h / _ptImageSize.y;
}

// 화면 좌표 -> NDC(Noramlize Device Coordinate)이며, 이 공간은 투영(Projection) 행렬에 정의
void Object2D::SetPosition(const Vector2D& vPos)
{
    _vPos = vPos;
    // 0 ~ 800 -> 0~1 -> -1 ~ + 1
    _vDrawPos.x = (vPos.x / g_rtClient.right) * 2.0f - 1.0f;
    _vDrawPos.y = -((vPos.y / g_rtClient.bottom) * 2.0f - 1.0f);
    _vDrawSize.x = (_rtInit.w / g_rtClient.right) * 2.0f;
    _vDrawSize.y = (_rtInit.h / g_rtClient.bottom) * 2.0f;

    UpdateVertexBuffer();
}

void Object2D::SetDirection(const Vector2D& vDir)
{
    _vDir = vDir;
}

void Object2D::UpdateVertexBuffer()
{
    _vertexList[0].p = { _vDrawPos.x, _vDrawPos.y, 0.0f };
    _vertexList[0].t = { _rtUV.x1, _rtUV.y1 };

    _vertexList[1].p = { _vDrawPos.x + _vDrawSize.x, _vDrawPos.y,  0.0f };
    _vertexList[1].t = { _rtUV.x1 + _rtUV.w, _rtUV.y1 };

    _vertexList[2].p = { _vDrawPos.x, _vDrawPos.y - _vDrawSize.y, 0.0f };
    _vertexList[2].t = { _rtUV.x1, _rtUV.y1 + _rtUV.h };

    _vertexList[3].p = _vertexList[2].p;
    _vertexList[3].t = _vertexList[2].t;

    _vertexList[4].p = _vertexList[1].p;
    _vertexList[4].t = _vertexList[1].t;

    _vertexList[5].p = { _vDrawPos.x + _vDrawSize.x, _vDrawPos.y - _vDrawSize.y, 0.0f };
    _vertexList[5].t = { _rtUV.x1 + _rtUV.w, _rtUV.y1 + _rtUV.h};

    _pImmediateContext->UpdateSubresource(_pVertexBuffer, 0, NULL, &_vertexList.at(0), 0, 0);
}

void Object2D::SetMask(Texture* pMaskTex)
{
    _pMaskTex = pMaskTex;
}
bool User2D::Frame()
{
    Vector2D vPos = _vPos;
    if (I_Input.GetKey('W'))
    {
        vPos.y += -1.0f * g_fSecondPerFrame * _fSpeed;
    }
    if (I_Input.GetKey('S'))
    {
        vPos.y += 1.0f * g_fSecondPerFrame * _fSpeed;
    }
    if (I_Input.GetKey('A'))
    {
        vPos.x += -1.0f * g_fSecondPerFrame * _fSpeed;
    }
    if (I_Input.GetKey('D'))
    {
        vPos.x += 1.0f * g_fSecondPerFrame * _fSpeed;
    }

    SetPosition(vPos);
    return true;
}

bool Npc2D::Frame()
{
    Vector2D vPos = _vPos;
    //벡터의 직선의 방정식 &  시간의 동기화
    Vector2D _vVelocity = _vDir * _fSpeed * g_fSecondPerFrame;
    vPos = vPos + _vVelocity;

    if (vPos.x > g_rtClient.right)
    {
        vPos.x = g_rtClient.right;
        _vDir.x *= -1.0f;
    }
    if (vPos.x < 0.0f)
    {
        vPos.x = 0.0f;
        _vDir.x *= -1.0f;
    }
    if (vPos.y > g_rtClient.bottom)
    {
        vPos.y = g_rtClient.bottom;
        _vDir.y *= -1.0f;
    }
    if (vPos.y < 0.0f)
    {
        vPos.y = 0.0f;
        _vDir.y *= -1.0f;
    }

    SetPosition(vPos);
    return true;
}

bool Sample::Init()
{
    Texture* pMaskTex = I_Tex.Load(L"../../data/bitmap2.bmp");

    _pMap = new BaseObject;
    _pMap->Create(_pd3dDevice, _pImmediateContext,
        L"../../data/kgcabk.bmp",
        L"../../data/shader/DefaultShape.txt");

    for (int iNpc = 0; iNpc < 37; iNpc++)
    {
        Npc2D* npc = new Npc2D;
        npc->Create(_pd3dDevice, _pImmediateContext,
            L"../../data/bitmap1.bmp",
            L"DefaultShapeMask.txt");
        if (iNpc % 2 == 0)
        {
            npc->SetRect({ 46, 62, 68, 79 });
        }
        else
        {
            npc->SetRect({ 115, 62, 37, 35 });
        }
        npc->SetDirection({ randstep(-1.0f, 1.0f),
            randstep(-1.0f, 1.0f) });
        npc->SetPosition({ 100.0f + iNpc * 100.0f, 100.0f });
        npc->SetMask(pMaskTex);
        _pNpcList.push_back(npc);
    }
    /*I_Tex.Load(L"../../data/0.bmp");
    I_Tex.Load(L"../../data/1.bmp");
    I_Tex.Load(L"../../data/2.bmp");
    I_Tex.Load(L"../../data/3.bmp");
    I_Tex.Load(L"../../data/4.bmp");
    I_Tex.Load(L"../../data/5.bmp");
    I_Tex.Load(L"../../data/6.bmp");
    I_Tex.Load(L"../../data/7.bmp");
    I_Tex.Load(L"../../data/8.bmp");
    I_Tex.Load(L"../../data/9.bmp");
    I_Tex.Load(L"../../data/sprite/shine0.bmp");
    I_Tex.Load(L"../../data/sprite/shine1.bmp");
    I_Tex.Load(L"../../data/sprite/shine2.bmp");
    I_Tex.Load(L"../../data/sprite/shine3.bmp");
    I_Tex.Load(L"../../data/sprite/shine4.bmp");
    I_Tex.Load(L"../../data/sprite/shine5.bmp");
    I_Tex.Load(L"../../data/sprite/shine6.bmp");
    I_Tex.Load(L"../../data/sprite/shine7.bmp");
    I_Tex.Load(L"../../data/sprite/shine8.bmp");
    I_Tex.Load(L"../../data/sprite/shine9.bmp");*/

    /*for (int iObj = 0; iObj < 10; iObj++)
    {
        BaseObject* pObject = new BaseObject;
        pObject->Create(_pd3dDevice, _pImmediateContext,
            L"../../data/kgcabk.bmp",
            L"../../data/shader/DefaultShape.txt");
        _pObjectList.push_back(pObject);
    }*/

    // user character
    // {90, 1, 40, 60} //이미지의 영역, {400, 300} //화면 좌표계
    // -1 ~ +1
    /*_pObject = new User2D;
    _pObject->Create(_pd3dDevice, _pImmediateContext, L"../../data/bitmap1.bmp", L"../../data/shader/DefaultShape.txt");
    _pObject->SetRect({ 90, 1, 40, 60 });
    _pObject->SetPosition({g_rtClient.right/2.0f, g_rtClient.bottom/2.0f});*/
    // user character
// { 90, 1, 40, 60 } , { 400,300 }
// -1 ~ +1
    _pUser = new User2D;
    _pUser->Create(_pd3dDevice, _pImmediateContext,
        L"../../data/bitmap1.bmp",
        L"DefaultShapeMask.txt");
    _pUser->SetMask(pMaskTex);
    _pUser->_fSpeed = 300.0f;
    _pUser->SetRect({ 91, 2, 39, 59 });
    _pUser->SetPosition({ g_rtClient.right / 2.0f,
                           g_rtClient.bottom - 100.0f });
    return true;
}

bool Sample::Frame()
{
    _pMap->Frame();
    for (auto obj : _pNpcList)
    {
        obj->Frame();
    }
    _pUser->Frame();
    return true;
}

bool Sample::Render()
{
    _pMap->Render();

    for (auto obj : _pNpcList)
    {
        obj->Render();
    }

    _pUser->PreRender();
    _pImmediateContext->PSSetShaderResources(1, 1,
        &_pUser->_pMaskTex->_pTextureSRV);
    _pUser->PostRender();

    /*std::wstring name = L"../../data/sprite/shine";//0.bmp";
    name += std::to_wstring(_iTexIndex);
    name += L".bmp";
    _pObjectList[0]->_pTexture = I_Tex.Find(name);
    _pObjectList[0]->Render();*/
    return true;
}

bool Sample::Release()
{
    for (auto obj : _pObjectList)
    {
        obj->Release();
        delete obj;
    }
    return true;
}

GAME_RUN(GameTest, 1024, 768)
