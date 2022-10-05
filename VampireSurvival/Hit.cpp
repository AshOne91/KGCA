#include "Hit.h"
#include "Sprite.h"
#include "GameWorld.h"

void Hit::SetPosition(const Vector2D& vPos, const Vector2D& vCamera)
{
	Object2DComponent::SetPosition(vPos, vCamera);
	_transform.SetPostion(vPos);
	_vMovingPos = _vPos;
}

bool Hit::Render()
{
	_pSprite->SetCameraSize(I_GameWorld.GetViewSize());
	_pSprite->SetCameraPos(I_GameWorld.GetCameraPos());
	_pSprite->SetRect(_tRect);
	_pSprite->SetPosition(_vMovingPos, _vCameraPos);
	if (_bFlip == true)
	{
		_pSprite->UpdateVertexBufferFlip();
	}
	_pSprite->Render();
	return true;
}

bool Hit::EffectUpdate()
{
	_fEffectTimer += g_fSecondPerFrame;
	if (_fStep <= _fEffectTimer)
	{
		_fEffectTimer -= _fStep;
		_iIndex++;
	}
	if (_iIndex >= _iMaxIndex)
	{
		DestroyObject(GetIndex());
		return true;
	}
	if (_bAnimation == false)
	{
		_iIndex = 0;
	}
	RECT rt = _pSprite->_uvArray[_iIndex];
	_tRect = convert(rt);

	Vector2D	vDrawSize;
	vDrawSize.x = _rtInit.w / 2.0f;
	vDrawSize.y = _rtInit.h / 2.0f;
	_rtCollision.Set(
		_vPos.x - vDrawSize.x,
		_vPos.y - vDrawSize.y,
		_rtInit.w,
		_rtInit.h);
	//_pSprite->SetCameraSize(_vViewSize);
	//_pSprite->SetCameraPos(_vCameraPos);
	//_pSprite->SetRect(_tRect);
	//_pSprite->SetPosition(_vPos, _vCameraPos);
	//if (_bFlip == true)
	//{
	//	_pSprite->UpdateVertexBufferFlip();
	//}
	return true;
}

void Hit::UpdateVertexBuffer()
{
	_VertexList[0].p = { _vNDCPos.x, _vNDCPos.y, 0.0f };
	_VertexList[0].t = { _rtUV.x1, _rtUV.y1 };

	_VertexList[1].p = { _vNDCPos.x + _vDrawSize.x, _vNDCPos.y,  0.0f };
	_VertexList[1].t = { _rtUV.x1 + _rtUV.w, _rtUV.y1 };

	_VertexList[2].p = { _vNDCPos.x, _vNDCPos.y - _vDrawSize.y, 0.0f };
	_VertexList[2].t = { _rtUV.x1, _rtUV.y1 + _rtUV.h };

	_VertexList[3].p = { _vNDCPos.x + _vDrawSize.x, _vNDCPos.y - _vDrawSize.y, 0.0f };
	_VertexList[3].t = { _rtUV.x1 + _rtUV.w , _rtUV.y1 + _rtUV.h };

	Rotation();

	_pImmediateContext->UpdateSubresource(_pVertexBuffer, NULL, NULL, &_VertexList.at(0), 0, 0);
}

bool Hit::Frame()
{
	SetCameraSize(I_GameWorld.GetViewSize());
	SetCameraPos(I_GameWorld.GetCameraPos());
	SetPosition(_vMovingPos, _vCameraPos);
	EffectUpdate();
	return true;
}

bool Hit::CInit()
{
	Hit::Init();
	_fLifeTime = 0.2f;
	_bAnimation = true;
	_pSprite = I_Sprite.GetPtr(L"rtHit");
	Create(I_GameWorld.GetDevice(), I_GameWorld.GetDeviceImmediateContext(), L"../../data/shader/DefaultShapeMask.txt", L"../../data/bitmap1.bmp");
	Object2D::SetPosition(Vector2D(0.0f, 0.0f));
	InitSprite();
	return true;
}

bool Hit::CFrame()
{
	Hit::Frame();
	return true;
}

bool Hit::CRender()
{
	Hit::Render();
	return true;
}

bool Hit::CRelease()
{
	Hit::Release();
	ComponentObject::CRelease();
	return true;
}

bool Hit::OnEvent(EventType eventType, ComponentObject* pSender, Message* msg)
{
	return true;
}
