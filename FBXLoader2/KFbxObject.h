#pragma once
#include <fbxsdk.h>
#include "Object3D.h"

struct AnimTrack
{
	UINT iFrame; //fTime;
	TBASIS_EX::TMatrix matAnim; // self * parent;
	TBASIS_EX::TMatrix matSelfAnim; // matAnim * inv(parent)
	TBASIS_EX::TVector3 t; // self
	TBASIS_EX::TQuaternion r; // self
	TBASIS_EX::TVector3 s; //self
};

struct AnimScene
{
	FbxTime::EMode TimeMode;
	UINT iStartFrame;
	UINT iEndFrame;
	float fTickPerFrame; // 160
	float fFrameSpeed; // 30
};

struct KWeight
{
	std::vector<int> Index;
	std::vector<float> weight;
	void insert(int iBone, float fWeight)
	{
		for (int i = 0; i < Index.size(); ++i)
		{
			if (fWeight > weight[i])
			{
				for (int j = Index.size() - 1; j > i; --j)
				{
					Index[j] = Index[j - 1];
					weight[j] = weight[j - 1];
				}
				Index[i] = iBone;
				weight[i] = fWeight;
				break;
			}
		}
	}
	KWeight()
	{
		Index.resize(8);
		weight.resize(8);
	}
};

class KFbxObject : public Object3D
{
public:
	UINT _iObjectBone;
	TMatrix _matAnim;
	TMatrix _matControl;

	FbxAMatrix _fbxLocalMatrix;
	FbxNode* _pFbxNode = nullptr;
	FbxNode* _pFbxParentNode = nullptr;
	KFbxObject* _pParent = nullptr;
	std::vector<KFbxObject*> _pFbxChilds;
	std::vector<AnimTrack> _AnimTracks;
	void SetParent(KFbxObject* pParentNode)
	{
		pParentNode->_pFbxChilds.push_back(this);
		_pParent = pParentNode;
	}

public:
	std::vector<ID3D11Buffer*> _pSubVB;
	std::vector<std::vector<PNCT_VERTEX>> vbDataList;
	std::vector<Texture*> _pSubTexture;
	std::vector<W_STR> vbTexList;

public:
	void CreateVertexData();
	HRESULT CreateVertexBuffer();
	HRESULT CreateIndexBuffer();
	bool LoadTexture(W_STR texturename);
	bool PostRender();
	bool Release();
	TMatrix Interplate(float fFrame, AnimScene tScene);
};

class FbxObjectSkinning : public KFbxObject
{
public:
	bool _bSkinned = false;
	// sub material
	std::vector<ID3D11Buffer*> _pSubVB_IW;
	std::vector<std::vector<IW_VERTEX>> vbDataList_IW;
	// single model
	std::vector<IW_VERTEX> _VertexListIW;
	ID3D11Buffer* _pVertexBufferIW;
	// skinning
	std::vector<KWeight> _WeightList;
	std::map<UINT, TMatrix> _dxMatrixBindPseMap;

public:
	VS_CONSTANT_BONE_BUFFER _cbDataBone;
	ID3D11Buffer* _pSkinBoneCB;

public:
	HRESULT CreateConstantBuffer()
	{
		Object3D::CreateConstantBuffer();

		HRESULT hr;
		for (int iBone = 0; iBone < 255; ++iBone)
		{
			D3DXMatrixIdentity(&_cbDataBone.matBone[iBone]);
		}

		D3D11_BUFFER_DESC bd;
		ZeroMemory(&bd, sizeof(bd));
		bd.ByteWidth = sizeof(VS_CONSTANT_BONE_BUFFER) * 1; // ����Ʈ �뷮
		// GPU �޸𸮿� �Ҵ�
		bd.Usage = D3D11_USAGE_DEFAULT; // ������ �Ҵ� ��� ������ ���ۿ뵵
		bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;

		D3D11_SUBRESOURCE_DATA sd;
		ZeroMemory(&sd, sizeof(sd));
		sd.pSysMem = &_cbDataBone;
		hr = _pd3dDevice->CreateBuffer(
			&bd, // ���� �Ҵ�
			&sd, // �ʱ� �Ҵ�� ���۸� ä��� CPU�޸� �ּ�
			&_pSkinBoneCB);
		return hr;
	}

	HRESULT CreateVertexLayout()
	{
		HRESULT hr;
		if (_pVSCode == nullptr)
		{
			return E_FAIL;
		}
		// �������̾ƿ��� �������̴� ������ ����.
		// �������̾ƿ� ������ ������ �������̴� ������ �ʿ��ϴ�.
		D3D11_INPUT_ELEMENT_DESC ied[] =
		{
			{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0,0,D3D11_INPUT_PER_VERTEX_DATA, 0},
			{ "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT,   0,12,D3D11_INPUT_PER_VERTEX_DATA, 0},
			{ "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0,24,D3D11_INPUT_PER_VERTEX_DATA, 0},
			{ "TEXTURE", 0, DXGI_FORMAT_R32G32_FLOAT,    0,40,D3D11_INPUT_PER_VERTEX_DATA, 0},

			{ "INDEX", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 1,0,D3D11_INPUT_PER_VERTEX_DATA, 0},
			{ "WEIGHT", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 1,16,D3D11_INPUT_PER_VERTEX_DATA, 0},
		};
		UINT NumElements = sizeof(ied) / sizeof(ied[0]);
		hr = _pd3dDevice->CreateInputLayout(
			ied,
			NumElements,
			_pVSCode->GetBufferPointer(),
			_pVSCode->GetBufferSize(),
			&_pVertexLayout);

		return hr;
	}

	HRESULT CreateVertexBuffer()
	{
		HRESULT hr = S_OK;
		KFbxObject::CreateVertexBuffer();

		if (vbDataList_IW.size() > 0)
		{
			_pSubVB_IW.resize(vbDataList_IW.size());
			for (int ivb = 0; ivb < vbDataList_IW.size(); ivb++)
			{
				if (vbDataList_IW[ivb].size() > 0)
				{
					_pSubVB_IW[ivb] =
						KDX::CreateVertexBuffer(_pd3dDevice,
							&vbDataList_IW[ivb].at(0),
							vbDataList_IW[ivb].size(),
							sizeof(IW_VERTEX));
				}
			}
		}
		else
		{
			_pVertexBufferIW = KDX::CreateVertexBuffer(_pd3dDevice, &_VertexListIW.at(0), _VertexListIW.size(), sizeof(IW_VERTEX));
		}
		return hr;
	}
	bool PostRender()
	{
		if (_bSkinned)
		{
			_pImmediateContext->VSSetConstantBuffers(1, 1, &_pSkinBoneCB);
		}
		if (_pIndexBuffer == nullptr)
		{
			if (vbDataList.size() > 0)
			{
				for (int iSubObj = 0; iSubObj < _pSubVB.size(); ++iSubObj)
				{
					if (vbDataList[iSubObj].size() <= 0)
					{
						continue;
					}
					UINT stride[2] = { sizeof(PNCT_VERTEX), sizeof(IW_VERTEX) }; // ����1���� ����Ʈ�뷮
					UINT offset[2] = { 0, 0 }; // �������ۿ��� �������(����Ʈ)
					//SLOT(�������͸�)
					ID3D11Buffer* buffer[2] = { _pSubVB[iSubObj], _pSubVB_IW[iSubObj] };
					_pImmediateContext->IASetVertexBuffers(0, 2, buffer, stride, offset);

					if (_pSubTexture.size() > 0 && _pSubTexture[iSubObj] != nullptr)
					{
						_pImmediateContext->PSSetShaderResources(0, 1, &_pSubTexture[iSubObj]->_pTextureSRV);
					}
					_pImmediateContext->Draw(vbDataList[iSubObj].size(), 0);
				}
			}
			else
			{
				UINT stride[2] = { sizeof(PNCT_VERTEX), sizeof(IW_VERTEX) }; // ����1���� ����Ʈ �뷮
				UINT offset[2] = { 0, 0 };
				//SLOT(�������͸�)
				ID3D11Buffer* buffer[2] = { _pVertexBuffer, _pVertexBufferIW };
				_pImmediateContext->IASetVertexBuffers(0, 2, buffer, stride, offset);
				_pImmediateContext->Draw(_VertexList.size(), 0);
			}
		}
		else
		{
			_pImmediateContext->DrawIndexed(_dwFace * 3, 0, 0);
		}
		return true;
	}
	bool Release()
	{
		if (_pSkinBoneCB)
		{
			_pSkinBoneCB->Release();
			_pSkinBoneCB = nullptr;
		}
		if (_pVertexBufferIW)
		{
			_pVertexBufferIW->Release();
			_pVertexBufferIW = nullptr;
		}
		for (int iSubObj = 0; iSubObj < _pSubVB_IW.size(); iSubObj++)
		{
			if (_pSubVB_IW[iSubObj])
			{
				_pSubVB_IW[iSubObj]->Release();
				_pSubVB_IW[iSubObj] = nullptr;
			}
		}
		_pSubVB_IW.clear();

		KFbxObject::Release();
		return true;
	}
};