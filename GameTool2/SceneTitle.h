#pragma once
#include "Scene.h"
#include "Interface.h"
#include "Projectile2D.h"
#include "Object3D.h"
#include "CameraDebug.h"
#include "Map.h"
#include "Input.h"

class KUser : public ObjectBox
{
public:
	bool Frame()
	{
        if (I_Input.GetKey('W') == KEY_HOLD)
        {
            TVector3 v = _vLook * g_fSecondPerFrame * 50.0f;
            _vPos += v;
        }
        if (I_Input.GetKey('S') == KEY_HOLD)
        {
            TVector3 v = -_vLook * g_fSecondPerFrame * 50.0f;
            _vPos += v;
        }

        /*    if (I_Input.GetKey('Q') == KEY_HOLD)
            {
                TVector3 v = m_vUp * m_fSpeed * g_fSecondPerFrame* 50.0f;
                m_vPos += v;
            }
            if (I_Input.GetKey('E') == KEY_HOLD)
            {
                TVector3 v = m_vUp * -m_fSpeed * g_fSecondPerFrame* 50.0f;
                m_vPos += v;
            }*/

        D3DXMatrixTranslation(&_matWorld, _vPos.x, _vPos.y, _vPos.z);
        Update();
        return true;
	}

    void Update()
    {
        _vRight.x = _matWorld._11;
        _vRight.y = _matWorld._12;
        _vRight.z = _matWorld._13;

        _vUp.x = _matWorld._21;
        _vUp.y = _matWorld._22;
        _vUp.z = _matWorld._23;

        _vLook.x = _matWorld._31;
        _vLook.y = _matWorld._32;
        _vLook.z = _matWorld._33;

        D3DXVec3Normalize(&_vRight, &_vRight);
        D3DXVec3Normalize(&_vUp, &_vUp);
        D3DXVec3Normalize(&_vLook, &_vLook);
    }
};

class SceneTitle : public Scene
{
public:
    TVector3 vBeforePos;
	BaseObject* _pBG;
	Map* _pMap = nullptr;
    KUser* _pUser = nullptr;

public:
	virtual bool		Init();
	virtual bool		Frame();
	virtual bool		Render();
	virtual bool		Release();

public:
	virtual bool IsNextScene();
};

