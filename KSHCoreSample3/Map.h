#pragma once
#include "BaseObject.h"
#include "CameraDebug.h"

class Map : public BaseObject
{
public:
	//DWORD _dwNumRows;
	//DWORD _dwNumColumns;
	UINT _iNumCellCols;
	UINT _iNumCellRows;
	DWORD _iNumRows;
	DWORD _iNumCols;
	float _fCellDistance = 1.0f;
	float _fScaleHeight = 100.0f;
	DWORD_VECTOR indexlist;
	std::vector<float> _fHeightList;

public:
	bool Build(UINT iWidth, UINT iHeight);
	bool UpdateBuffer(CameraDebug* pMainCamera);
	bool LoadHeightMap(ID3D11Device* p3d3Device, // 디바이스 객체
		ID3D11DeviceContext* pImmediateContext, W_STR loadTexture);
	void GenVertexNormal();
	TVector3 ComputeFaceNormal(UINT i0, UINT i1, UINT i2);
	float GetHeight(float fPosX, float fPosZ);
	float GetHeightmap(int row, int col);
	float Lerp(float fStart, float fEnd, float fTangent);
};

