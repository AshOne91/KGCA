#include "Monster.h"
#include "Spawner.h"
#include "GameWorld.h"

Monster* Monster::Clone(Spawner* pSpawner)
{
	Texture* pMaskTex = I_Tex.Load(L"../../data/bitmap2.bmp");
	auto pMonster = new Monster(_iHearth, _iAttack);
	pMonster->Create(I_GameWorld.GetDevice(), I_GameWorld.GetDeviceImmediateContext(),
		L"../../data/shader/DefaultShapeMask.txt",
		L"../../data/bitmap1.bmp");
	if (rand() % 2 == 0)
	{
		pMonster->SetRect({ 46, 62, 68, 79 });
	}
	else
	{
		pMonster->SetRect({ 115, 62, 37, 35 });
	}
	pMonster->SetCameraSize(I_GameWorld.GetViewSize());
	pMonster->SetCameraPos(I_GameWorld.GetCameraPos());
	pMonster->SetPosition(pSpawner->_vPos, I_GameWorld.GetCameraPos());
	pMonster->SetMask(pMaskTex);
	return pMonster;
}

void Monster::UpdateVertexBuffer()
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

bool Monster::Frame()
{
	SetPosition(_vPos, _vCameraPos);
	return true;
}

Monster::Monster(int iHearth, int iAttack) : _iHearth(iHearth), _iAttack(_iAttack)
{

}

Monster::~Monster()
{

}
