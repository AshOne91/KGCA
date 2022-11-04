#include "Object3D.h"

bool ObjectBox::Init()
{
	_pDirLineShape = new ShapeDirectionLine;
	_pDirLineShape->Create(_pd3dDevice, _pImmediateContext, L"DefaultShape.txt", L"");
	return true;
}

bool ObjectBox::Frame()
{
	return true;
}

bool ObjectBox::Render()
{
	BaseObject::Render();
	_pDirLineShape->Render();
	return true;
}

bool ObjectBox::Release()
{
	if (_pDirLineShape) _pDirLineShape->Release();
	delete _pDirLineShape;
	BaseObject::Release();
	return true;
}

void ObjectBox::SetMatrix(TMatrix* matWorld, TMatrix* matView, TMatrix* matProj)
{
	BaseObject::SetMatrix(matWorld, matView, matProj);
	_vPos.x = _matWorld._41;
	_vPos.y = _matWorld._42;
	_vPos.z = _matWorld._43;

	_vRight.x = _matWorld._11;
	_vRight.y = _matWorld._12;
	_vRight.z = _matWorld._13;

	_vUp.x = _matWorld._21;
	_vUp.y = _matWorld._22;
	_vUp.z = _matWorld._23;

	_vLook.x = _matWorld._31;
	_vLook.y = _matWorld._32;
	_vLook.z = _matWorld._33;

	TVector3  _vUp;// y
	TVector3  _vRight; //z

	TMatrix matLineWorld;
	//matLineWorld.Scale(2.0f, 2.0f, 2.0f);
	D3DXMatrixScaling(&matLineWorld, 2.0f, 2.0f, 2.0f);
	matLineWorld = matLineWorld * _matWorld;
	if (_pDirLineShape)_pDirLineShape->SetMatrix(&matLineWorld, matView, matProj);
}

void ObjectBox::CreateVertexData()
{
	// ���
// 5    6
// 1    2
// �ϴ�
// 4    7
// 0    3  
// �ո�
	_VertexList.resize(24);
	_VertexList[0] = PNCT_VERTEX(TVector3(-1.0f, 1.0f, -1.0f), TVector3(0.0f, 0.0f, -1.0f), TVector4(1.0f, 0.0f, 0.0f, 1.0f), TVector2(0.0f, 0.0f));
	_VertexList[1] = PNCT_VERTEX(TVector3(1.0f, 1.0f, -1.0f), TVector3(0.0f, 0.0f, -1.0f), TVector4(1.0f, 0.0f, 0.0f, 1.0f), TVector2(1.0f, 0.0f));
	_VertexList[2] = PNCT_VERTEX(TVector3(1.0f, -1.0f, -1.0f), TVector3(0.0f, 0.0f, -1.0f), TVector4(1.0f, 0.0f, 0.0f, 1.0f), TVector2(1.0f, 1.0f));
	_VertexList[3] = PNCT_VERTEX(TVector3(-1.0f, -1.0f, -1.0f), TVector3(0.0f, 0.0f, -1.0f), TVector4(1.0f, 0.0f, 0.0f, 1.0f), TVector2(0.0f, 1.0f));
	// �޸�
	_VertexList[4] = PNCT_VERTEX(TVector3(1.0f, 1.0f, 1.0f), TVector3(0.0f, 0.0f, 1.0f), TVector4(0.0f, 0.0f, 0.0f, 1.0f), TVector2(0.0f, 0.0f));
	_VertexList[5] = PNCT_VERTEX(TVector3(-1.0f, 1.0f, 1.0f), TVector3(0.0f, 0.0f, 1.0f), TVector4(0.0f, 1.0f, 0.0f, 1.0f), TVector2(1.0f, 0.0f));
	_VertexList[6] = PNCT_VERTEX(TVector3(-1.0f, -1.0f, 1.0f), TVector3(0.0f, 0.0f, 1.0f), TVector4(0.0f, 1.0f, 0.0f, 1.0f), TVector2(1.0f, 1.0f));
	_VertexList[7] = PNCT_VERTEX(TVector3(1.0f, -1.0f, 1.0f), TVector3(0.0f, 0.0f, 1.0f), TVector4(0.0f, 1.0f, 0.0f, 1.0f), TVector2(0.0f, 1.0f));

	// ������
	_VertexList[8] = PNCT_VERTEX(TVector3(1.0f, 1.0f, -1.0f), TVector3(1.0f, 0.0f, 0.0f), TVector4(0.0f, 0.0f, 1.0f, 1.0f), TVector2(0.0f, 0.0f));
	_VertexList[9] = PNCT_VERTEX(TVector3(1.0f, 1.0f, 1.0f), TVector3(1.0f, 0.0f, -1.0f), TVector4(0.0f, 0.0f, 1.0f, 1.0f), TVector2(1.0f, 0.0f));
	_VertexList[10] = PNCT_VERTEX(TVector3(1.0f, -1.0f, 1.0f), TVector3(1.0f, 0.0f, -1.0f), TVector4(0.0f, 0.0f, 1.0f, 1.0f), TVector2(1.0f, 1.0f));
	_VertexList[11] = PNCT_VERTEX(TVector3(1.0f, -1.0f, -1.0f), TVector3(1.0f, 0.0f, -1.0f), TVector4(0.0f, 0.0f, 1.0f, 1.0f), TVector2(0.0f, 1.0f));

	// ����
	_VertexList[12] = PNCT_VERTEX(TVector3(-1.0f, 1.0f, 1.0f), TVector3(-1.0f, 0.0f, 0.0f), TVector4(1.0f, 1.0f, 0.0f, 1.0f), TVector2(0.0f, 0.0f));
	_VertexList[13] = PNCT_VERTEX(TVector3(-1.0f, 1.0f, -1.0f), TVector3(-1.0f, 0.0f, 0.0f), TVector4(1.0f, 1.0f, 0.0f, 1.0f), TVector2(1.0f, 0.0f));
	_VertexList[14] = PNCT_VERTEX(TVector3(-1.0f, -1.0f, -1.0f), TVector3(-1.0f, 0.0f, 0.0f), TVector4(1.0f, 1.0f, 0.0f, 1.0f), TVector2(1.0f, 1.0f));
	_VertexList[15] = PNCT_VERTEX(TVector3(-1.0f, -1.0f, 1.0f), TVector3(-1.0f, 0.0f, 0.0f), TVector4(1.0f, 1.0f, 0.0f, 1.0f), TVector2(0.0f, 1.0f));

	// ����
	_VertexList[16] = PNCT_VERTEX(TVector3(-1.0f, 1.0f, 1.0f), TVector3(0.0f, 1.0f, 0.0f), TVector4(1.0f, 0.5f, 1.0f, 1.0f), TVector2(0.0f, 0.0f));
	_VertexList[17] = PNCT_VERTEX(TVector3(1.0f, 1.0f, 1.0f), TVector3(0.0f, 1.0f, 0.0f), TVector4(1.0f, 0.5f, 1.0f, 1.0f), TVector2(1.0f, 0.0f));
	_VertexList[18] = PNCT_VERTEX(TVector3(1.0f, 1.0f, -1.0f), TVector3(0.0f, 1.0f, 0.0f), TVector4(1.0f, 0.5f, 1.0f, 1.0f), TVector2(1.0f, 1.0f));
	_VertexList[19] = PNCT_VERTEX(TVector3(-1.0f, 1.0f, -1.0f), TVector3(0.0f, 1.0f, 0.0f), TVector4(1.0f, 0.5f, 1.0f, 1.0f), TVector2(0.0f, 1.0f));

	// �Ʒ���
	_VertexList[20] = PNCT_VERTEX(TVector3(-1.0f, -1.0f, -1.0f), TVector3(0.0f, -1.0f, 0.0f), TVector4(0.0f, 1.0f, 1.0f, 1.0f), TVector2(0.0f, 0.0f));
	_VertexList[21] = PNCT_VERTEX(TVector3(1.0f, -1.0f, -1.0f), TVector3(0.0f, -1.0f, 0.0f), TVector4(0.0f, 1.0f, 1.0f, 1.0f), TVector2(1.0f, 0.0f));
	_VertexList[22] = PNCT_VERTEX(TVector3(1.0f, -1.0f, 1.0f), TVector3(0.0f, -1.0f, 0.0f), TVector4(0.0f, 1.0f, 1.0f, 1.0f), TVector2(1.0f, 1.0f));
	_VertexList[23] = PNCT_VERTEX(TVector3(-1.0f, -1.0f, 1.0f), TVector3(0.0f, -1.0f, 0.0f), TVector4(0.0f, 1.0f, 1.0f, 1.0f), TVector2(0.0f, 1.0f));


	_InitVertexList = _VertexList;
}

void ObjectBox::CreateIndexData()
{
	_IndexList.resize(36);
	int iIndex = 0;
	_IndexList[iIndex++] = 0;  _IndexList[iIndex++] = 1;  _IndexList[iIndex++] = 2;  _IndexList[iIndex++] = 0;	_IndexList[iIndex++] = 2;  _IndexList[iIndex++] = 3;
	_IndexList[iIndex++] = 4;  _IndexList[iIndex++] = 5;  _IndexList[iIndex++] = 6;  _IndexList[iIndex++] = 4;	_IndexList[iIndex++] = 6;  _IndexList[iIndex++] = 7;
	_IndexList[iIndex++] = 8;  _IndexList[iIndex++] = 9;  _IndexList[iIndex++] = 10; _IndexList[iIndex++] = 8;	_IndexList[iIndex++] = 10; _IndexList[iIndex++] = 11;
	_IndexList[iIndex++] = 12; _IndexList[iIndex++] = 13; _IndexList[iIndex++] = 14; _IndexList[iIndex++] = 12;	_IndexList[iIndex++] = 14; _IndexList[iIndex++] = 15;
	_IndexList[iIndex++] = 16; _IndexList[iIndex++] = 17; _IndexList[iIndex++] = 18; _IndexList[iIndex++] = 16;	_IndexList[iIndex++] = 18; _IndexList[iIndex++] = 19;
	_IndexList[iIndex++] = 20; _IndexList[iIndex++] = 21; _IndexList[iIndex++] = 22; _IndexList[iIndex++] = 20;	_IndexList[iIndex++] = 22; _IndexList[iIndex++] = 23;
	_dwFace = _IndexList.size() / 3;
}

void Object3D::UpdateCollision()
{
	_BoxCollision.vAxis[0] = _vRight;
	_BoxCollision.vAxis[1] = _vUp;
	_BoxCollision.vAxis[2] = _vLook;

	_BoxCollision.vMin = TVector3(100000, 100000, 100000);
	_BoxCollision.vMax = TVector3(-100000, -100000, -100000);
	for (int iV = 0; iV < 8; ++iV)
	{
		TVector3 pos;
		TBASIS_EX::D3DXVec3TransformCoord((TBASIS_EX::TVector3*)&pos, (TBASIS_EX::TVector3*)&_BoxCollision.vPos[iV], (TBASIS_EX::TMatrix*)&_matWorld);
		if (_BoxCollision.vMin.x > pos.x)
		{
			_BoxCollision.vMin.x = pos.x;
		}
		if (_BoxCollision.vMin.y > pos.y)
		{
			_BoxCollision.vMin.y = pos.y;
		}
		if (_BoxCollision.vMin.z > pos.z)
		{
			_BoxCollision.vMin.z = pos.z;
		}

		if (_BoxCollision.vMax.x < pos.x)
		{
			_BoxCollision.vMax.x = pos.x;
		}
		if (_BoxCollision.vMax.y < pos.y)
		{
			_BoxCollision.vMax.y = pos.y;
		}
		if (_BoxCollision.vMax.z < pos.z)
		{
			_BoxCollision.vMax.z = pos.z;
		}
	}

	TVector3 vHalf = _BoxCollision.vMax - _BoxCollision.vCenter;
	_BoxCollision.fExtent[0] = fabs(TBASIS_EX::D3DXVec3Dot((TBASIS_EX::TVector3*)&_BoxCollision.vAxis[0], (TBASIS_EX::TVector3*)&vHalf));
	_BoxCollision.fExtent[1] = fabs(TBASIS_EX::D3DXVec3Dot((TBASIS_EX::TVector3*)&_BoxCollision.vAxis[1], (TBASIS_EX::TVector3*)&vHalf));
	_BoxCollision.fExtent[2] = fabs(TBASIS_EX::D3DXVec3Dot((TBASIS_EX::TVector3*)&_BoxCollision.vAxis[2], (TBASIS_EX::TVector3*)&vHalf));
	_BoxCollision.vCenter = (_BoxCollision.vMin + _BoxCollision.vMax);
	_BoxCollision.vCenter /= 2.0f;
}

void Object3D::GenAABB()
{
	_BoxCollision.vMin = TVector3(100000, 100000, 100000);
	_BoxCollision.vMax = TVector3(-100000, -100000, -100000);
	for (int i = 0; i < _VertexList.size(); ++i)
	{
		if (_BoxCollision.vMin.x > _VertexList[i].p.x)
		{						   
			_BoxCollision.vMin.x = _VertexList[i].p.x;
		}						   
		if (_BoxCollision.vMin.y > _VertexList[i].p.y)
		{						   
			_BoxCollision.vMin.y = _VertexList[i].p.y;
		}						   
		if (_BoxCollision.vMin.z > _VertexList[i].p.z)
		{						   
			_BoxCollision.vMin.z = _VertexList[i].p.z;
		}						   
								   
		if (_BoxCollision.vMax.x < _VertexList[i].p.x)
		{						   
			_BoxCollision.vMax.x = _VertexList[i].p.x;
		}						   
		if (_BoxCollision.vMax.y < _VertexList[i].p.y)
		{						   
			_BoxCollision.vMax.y = _VertexList[i].p.y;
		}						   
		if (_BoxCollision.vMax.z < _VertexList[i].p.z)
		{						   
			_BoxCollision.vMax.z = _VertexList[i].p.z;
		}
	}

	// 4      5
	// 6      7

	// 0     1
	// 2     3
	_BoxCollision.vPos[0] = TVector3(_BoxCollision.vMin.x,
	_BoxCollision.vMax.y,		   
	_BoxCollision.vMin.z);		   
	_BoxCollision.vPos[1] = TVector3(_BoxCollision.vMax.x,
	_BoxCollision.vMax.y,		   
	_BoxCollision.vMin.z);		   
	_BoxCollision.vPos[2] = TVector3(_BoxCollision.vMin.x,
	_BoxCollision.vMin.y,		   
	_BoxCollision.vMin.z);		   
	_BoxCollision.vPos[3] = TVector3(_BoxCollision.vMax.x,
	_BoxCollision.vMin.y,		   
	_BoxCollision.vMin.z);		   
								   
	_BoxCollision.vPos[4] = TVector3(_BoxCollision.vMin.x,
	_BoxCollision.vMax.y,		   
	_BoxCollision.vMax.z);		   
	_BoxCollision.vPos[5] = TVector3(_BoxCollision.vMax.x,
	_BoxCollision.vMax.y,		   
	_BoxCollision.vMax.z);		   
	_BoxCollision.vPos[6] = TVector3(_BoxCollision.vMin.x,
	_BoxCollision.vMin.y,		   
	_BoxCollision.vMax.z);		   
	_BoxCollision.vPos[7] = TVector3(_BoxCollision.vMax.x,
		_BoxCollision.vMin.y,
		_BoxCollision.vMax.z);
}
