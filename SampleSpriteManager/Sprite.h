#pragma once
#include "Object2D.h"
typedef std::vector<RECT> RECT_ARRAY;

class Sprite : public Object2D
{
public:
	W_STR _szName;
	UINT _IIndex;

public:
	RECT_ARRAY _uvArray;
	std::vector<Sprite*> _pChild;
	Rect _rtCollision;

public:
	HRESULT Load(ID3D11Device* pd3dDevce, ID3D11DeviceContext* pImmediateContext, std::wstring name);
	void SetPosition(Vector2D vPos)
	{
		_vPos = vPos;
		Vector2D vDrawSize;
		vDrawSize.x = _rtInit.w / 2.0f;
		vDrawSize.y = _rtInit.h / 2.0f;
		_rtCollision.Set(vPos.x - vDrawSize.x, vPos.y - vDrawSize.y, _rtInit.w, _rtInit.h);

		_vDrawPos.x = (_rtCollision.x1 / g_rtClient.right) * 2.0f - 1.0f;
		_vDrawPos.y = -((_rtCollision.y1 / g_rtClient.bottom) * 2.0f - 1.0f);
		_vDrawSize.x = (_rtInit.w / g_rtClient.right) * 2.0f;
		_vDrawSize.y = (_rtInit.h / g_rtClient.bottom) * 2.0f;
		UpdateVertexBuffer();
	}
};