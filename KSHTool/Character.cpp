#include "pch.h"
#include "Character.h"

HRESULT Character::CreateConstantBuffer(ID3D11Device* pDevice)
{
	HRESULT hr;
	for (int iBone = 0; iBone < 255; ++iBone)
	{
		D3DXMatrixIdentity(&_cbDataBone.matBone[iBone]);
	}

	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.ByteWidth = sizeof(VS_CONSTANT_BONE_BUFFER) * 1; // 바이트 용량
	bd.Usage = D3D11_USAGE_DEFAULT; // 버퍼의 할당 장소 내지는 버퍼 용량
	bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;

	D3D11_SUBRESOURCE_DATA sd;
	ZeroMemory(&sd, sizeof(sd));
	sd.pSysMem = &_cbDataBone;
	hr = pDevice->CreateBuffer(
		&bd, // 버퍼 할당
		&sd, // 초기 할당된 버퍼를 채우는 CPU메모리 주소
		&_pAnimBoneCB);

	_pSkinBoneCB.resize(_pFbxFile->_pDrawObjList.size());
	_cbDrawGeom.resize(_pFbxFile->_pDrawObjList.size());
	for (int iMesh = 0; iMesh < _pFbxFile->_pDrawObjList.size(); ++iMesh)
	{
		D3D11_SUBRESOURCE_DATA sd;
		ZeroMemory(&sd, sizeof(sd));
		sd.pSysMem = &_cbDataBone;
		hr = pDevice->CreateBuffer(
			&bd, // 버퍼 할당
			&sd, // 초기 할당된 버퍼를 채우는 CPU메모리 주소
			&_pSkinBoneCB[iMesh]);
	}

	return hr;
}

bool Character::UpdateFrame(ID3D11DeviceContext* pContext)
{
	_fAnimFrame = _fAnimFrame + g_fSecondPerFrame * _fAnimSpeed * _AnimScene.fFrameSpeed;// * _fAnimInverse;
	if (_fAnimFrame > _ActionCurrent.iEndFrame || _fAnimFrame < _ActionCurrent.iStartFrame)
	{
		_fAnimFrame = min(_fAnimFrame, _ActionCurrent.iEndFrame);
		_fAnimFrame = max(_fAnimFrame, _ActionCurrent.iStartFrame);
		//_fAnimInverse *= -1.0f;
	}

	if (_ActionCurrent.bLoop)
	{
		if (_fAnimFrame >= _ActionCurrent.iEndFrame)
		{
			_fAnimFrame = _ActionCurrent.iStartFrame;
		}
	}
	else
	{
		if (_fAnimFrame >= _ActionCurrent.iEndFrame)
		{
			_fAnimFrame = _ActionCurrent.iStartFrame;
		}
	}

	if (_pAnionFbxFile)
	{
		_pAnionFbxFile->UpdateSkeleton(pContext, _fAnimFrame, _cbDataBone);
		_pFbxFile->UpdateSkinning(pContext, _cbDataBone, _cbDrawGeom);
	}
	else
	{
		_pFbxFile->UpdateSkeleton(pContext, _fAnimFrame, _cbDataBone);
		_pFbxFile->UpdateSkinning(pContext, _cbDataBone, _cbDrawGeom);
	}
	for (int ibone = 0; ibone < _pSkinBoneCB.size(); ++ibone)
	{
		pContext->UpdateSubresource(
			_pSkinBoneCB[ibone], 0, nullptr,
			&_cbDrawGeom[ibone], 0, 0);
	}

	for (int iBone = 0; iBone < _pFbxFile->_pObjectList.size(); ++iBone)
	{
		D3DXMatrixTranspose(&_cbDataBone.matBone[iBone], &_cbDataBone.matBone[iBone]);
	}
	pContext->UpdateSubresource(_pAnimBoneCB, 0, nullptr, &_cbDataBone, 0, 0);

	return true;
}

void Character::SetMatrix(TMatrix* matWorld, TMatrix* matView, TMatrix* matProj)
{
	if (matWorld != nullptr)
	{
		_matWorld = *matWorld;
	}

	if (matView != nullptr)
	{
		_matView = *matView;
	}

	if (matProj != nullptr)
	{
		_matProj = *matProj;
	}
}


bool Character::Render(ID3D11DeviceContext* pContext)
{
	pContext->VSSetConstantBuffers(1, 1, &_pAnimBoneCB);
	for (int iMesh = 0; iMesh < _pFbxFile->_pDrawObjList.size(); ++iMesh)
	{
		if (_pFbxFile->_pDrawObjList[iMesh]->_bSkinned)
		{
			pContext->VSSetConstantBuffers(1, 1, &_pSkinBoneCB[iMesh]);
		}
		_pFbxFile->_pDrawObjList[iMesh]->SetMatrix(&_matWorld, &_matView, &_matProj);
		_pFbxFile->_pDrawObjList[iMesh]->Render();
	}
	return true;
}

bool Character::Release()
{
	if (_pAnimBoneCB) _pAnimBoneCB->Release();
	for (auto bone : _pSkinBoneCB)
	{
		bone->Release();
	}
	return true;
}