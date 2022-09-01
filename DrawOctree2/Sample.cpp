#include "Sample.h"
#include "TextureManager.h"
#include "ShaderManager.h"

bool Sample::Init()
{
	I_Tex.SetDevice(_pd3dDevice, _pImmediateContext);
	I_Shader.SetDevice(_pd3dDevice, _pImmediateContext);

    I_Tex.Load(L"../../data/0.bmp");
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
    I_Tex.Load(L"../../data/sprite/shine9.bmp");

    for (int iObj = 0; iObj < 10; iObj++)
    {
        BaseObject* pObject = new BaseObject;
        pObject->Create(_pd3dDevice, _pImmediateContext,
            L"../../data/kgcabk.bmp",
            L"../../data/shader/DefaultShape.txt");
        _pObjectList.push_back(pObject);
    }
    return true;
}

bool Sample::Frame()
{
    for (auto obj : _pObjectList)
    {
        obj->Frame();
    }
    return true;
}

bool Sample::Render()
{
    static float fTime = 0.0f;
    fTime += _fElapseTimer;
    if (fTime >= 0.1f)
    {
        _iTexIndex++;
        if (_iTexIndex >= 10) _iTexIndex = 0;
        fTime = fTime - 0.1f;
    }

    std::wstring name = L"../../data/sprite/shine";//0.bmp";
    name += std::to_wstring(_iTexIndex);
    name += L".bmp";
    _pObjectList[0]->_pTexture = I_Tex.Find(name);
    _pObjectList[0]->Render();
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
