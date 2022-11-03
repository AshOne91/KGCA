#include "KFbxObject.h"

void KFbxObject::CreateVertexData()
{

}

HRESULT KFbxObject::CreateVertexBuffer()
{
	HRESULT hr = S_OK;
	if (vbDataList.size() > 0)
	{
		_pSubVB.resize(vbDataList.size());
		for (int ivb = 0; ivb < vbDataList.size(); ++ivb)
		{
			if (vbDataList[ivb].size() > 0)
			{
				_pSubVB[ivb] = 
					KDX::CreateVertexBuffer(_pd3dDevice, 
						&vbDataList[ivb].at(0), 
						vbDataList[ivb].size(), 
						sizeof(PNCT_VERTEX));
			}
		}
	}
	else
	{
		hr = Object3D::CreateVertexBuffer();
	}
	return hr;
}

HRESULT KFbxObject::CreateIndexBuffer()
{
	return S_OK;
}

bool KFbxObject::LoadTexture(W_STR texturename)
{
	if (vbTexList.size() > 0)
	{
		W_STR szDefaultDir = L"../../data/fbx/";
		_pSubTexture.resize(vbTexList.size());
		for (int ivb = 0; ivb < vbTexList.size(); ++ivb)
		{
			W_STR szLoadFile = szDefaultDir + vbTexList[ivb];
			_pSubTexture[ivb] = I_Tex.Load(szLoadFile);
		}
	}
	else
	{
		_pTexture = I_Tex.Load(texturename);
		if (_pTexture != nullptr)
		{
			_pTextureSRV = _pTexture->_pTextureSRV;
			return true;
		}
	}
	return false;
}

bool KFbxObject::PostRender()
{
	if (_pIndexBuffer == nullptr)
	{
		if (vbDataList.size() > 0)
		{
			for (int iSubObj = 0; iSubObj < _pSubVB.size(); ++iSubObj)
			{
				if (vbDataList[iSubObj].size() <= 0) continue;
				UINT stride = sizeof(PNCT_VERTEX); // 정점1개의 바이트 용량
				UINT offset = 0; // 정점버퍼에서 출발지점(바이트)
				//SLOT(레지스터리)
				_pImmediateContext->IASetVertexBuffers(0, 1, &_pSubVB[iSubObj], &stride, &offset);
				if (_pSubTexture[iSubObj] != nullptr)
				{
					_pImmediateContext->PSSetShaderResources(0, 1, &_pSubTexture[iSubObj]->_pTextureSRV);
				}
				_pImmediateContext->Draw(vbDataList[iSubObj].size(), 0);
			}
		}
		else
		{
			_pImmediateContext->Draw(_VertexList.size(), 0);
		}
	}
	else
	{
		_pImmediateContext->DrawIndexed(_dwFace * 3, 0, 0);
	}
	return true;
}

bool KFbxObject::Release()
{
	Object3D::Release();

	for (int iSubObj = 0; iSubObj < _pSubVB.size(); ++iSubObj)
	{
		if (_pSubVB[iSubObj])
		{
			_pSubVB[iSubObj]->Release();
		}
	}
	return true;
}