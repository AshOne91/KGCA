#include "Sample.h"
#include "TextureManager.h"
#include "ShaderManager.h"
#include "Input.h"
#include "Timer.h"

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
    /*
 * VK_0 - VK_9 are the same as ASCII '0' - '9' (0x30 - 0x39)
 * 0x3A - 0x40 : unassigned
 * VK_A - VK_Z are the same as ASCII 'A' - 'Z' (0x41 - 0x5A)
 */
    POINT ptPos = I_Input._ptPos;
    if (I_Input.GetKey(VK_LBUTTON) == KEY_PUSH)
    {
        INT K = 0;
    }
    if (I_Input.GetKey(VK_LBUTTON) == KEY_UP)
    {
        INT K = 0;
    }
    for (auto obj : _pObjectList)
    {
        obj->Frame();
    }
    return true;
}

bool Sample::Render()
{
    if (I_Input.GetKey('W') == KEY_HOLD)
    {
        _writer.Draw(100, 100, L"WKEY_HOLD");
    }
    if (I_Input.GetKey('A') == KEY_HOLD)
    {
        _writer.Draw(100, 130, L"AKEY_HOLD");
    }
    if (I_Input.GetKey('S') == KEY_HOLD)
    {
        _writer.Draw(100, 160, L"SKEY_HOLD");
    }
    if (I_Input.GetKey('D') == KEY_HOLD)
    {
        _writer.Draw(100, 190, L"DKEY_HOLD");
    }

    
    static float fTime = 0.0f;
    fTime += I_Timer._fElapseTimer;
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
