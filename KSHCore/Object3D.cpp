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

void ObjectBox::SetMatrix(Matrix* matWorld, Matrix* matView, Matrix* matProj)
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

	Vector3D  _vUp;// y
	Vector3D  _vRight; //z

	Matrix matLineWorld;
	matLineWorld.Scale(2.0f, 2.0f, 2.0f);
	matLineWorld = matLineWorld * _matWorld;
	if (_pDirLineShape)_pDirLineShape->SetMatrix(&matLineWorld, matView, matProj);
}

void ObjectBox::CreateVertexData()
{
	// »ó´Ü
// 5    6
// 1    2
// ÇÏ´Ü
// 4    7
// 0    3  
// ¾Õ¸é
	_VertexList.resize(24);
	_VertexList[0] = PNCT_VERTEX(Vector3D(-1.0f, 1.0f, -1.0f), Vector3D(0.0f, 0.0f, -1.0f), Vector4D(1.0f, 0.0f, 0.0f, 1.0f), Vector2D(0.0f, 0.0f));
	_VertexList[1] = PNCT_VERTEX(Vector3D(1.0f, 1.0f, -1.0f), Vector3D(0.0f, 0.0f, -1.0f), Vector4D(1.0f, 0.0f, 0.0f, 1.0f), Vector2D(1.0f, 0.0f));
	_VertexList[2] = PNCT_VERTEX(Vector3D(1.0f, -1.0f, -1.0f), Vector3D(0.0f, 0.0f, -1.0f), Vector4D(1.0f, 0.0f, 0.0f, 1.0f), Vector2D(1.0f, 1.0f));
	_VertexList[3] = PNCT_VERTEX(Vector3D(-1.0f, -1.0f, -1.0f), Vector3D(0.0f, 0.0f, -1.0f), Vector4D(1.0f, 0.0f, 0.0f, 1.0f), Vector2D(0.0f, 1.0f));
	// µÞ¸é
	_VertexList[4] = PNCT_VERTEX(Vector3D(1.0f, 1.0f, 1.0f), Vector3D(0.0f, 0.0f, 1.0f), Vector4D(0.0f, 0.0f, 0.0f, 1.0f), Vector2D(0.0f, 0.0f));
	_VertexList[5] = PNCT_VERTEX(Vector3D(-1.0f, 1.0f, 1.0f), Vector3D(0.0f, 0.0f, 1.0f), Vector4D(0.0f, 1.0f, 0.0f, 1.0f), Vector2D(1.0f, 0.0f));
	_VertexList[6] = PNCT_VERTEX(Vector3D(-1.0f, -1.0f, 1.0f), Vector3D(0.0f, 0.0f, 1.0f), Vector4D(0.0f, 1.0f, 0.0f, 1.0f), Vector2D(1.0f, 1.0f));
	_VertexList[7] = PNCT_VERTEX(Vector3D(1.0f, -1.0f, 1.0f), Vector3D(0.0f, 0.0f, 1.0f), Vector4D(0.0f, 1.0f, 0.0f, 1.0f), Vector2D(0.0f, 1.0f));

	// ¿À¸¥ÂÊ
	_VertexList[8] = PNCT_VERTEX(Vector3D(1.0f, 1.0f, -1.0f), Vector3D(1.0f, 0.0f, 0.0f), Vector4D(0.0f, 0.0f, 1.0f, 1.0f), Vector2D(0.0f, 0.0f));
	_VertexList[9] = PNCT_VERTEX(Vector3D(1.0f, 1.0f, 1.0f), Vector3D(1.0f, 0.0f, -1.0f), Vector4D(0.0f, 0.0f, 1.0f, 1.0f), Vector2D(1.0f, 0.0f));
	_VertexList[10] = PNCT_VERTEX(Vector3D(1.0f, -1.0f, 1.0f), Vector3D(1.0f, 0.0f, -1.0f), Vector4D(0.0f, 0.0f, 1.0f, 1.0f), Vector2D(1.0f, 1.0f));
	_VertexList[11] = PNCT_VERTEX(Vector3D(1.0f, -1.0f, -1.0f), Vector3D(1.0f, 0.0f, -1.0f), Vector4D(0.0f, 0.0f, 1.0f, 1.0f), Vector2D(0.0f, 1.0f));

	// ¿ÞÂÊ
	_VertexList[12] = PNCT_VERTEX(Vector3D(-1.0f, 1.0f, 1.0f), Vector3D(-1.0f, 0.0f, 0.0f), Vector4D(1.0f, 1.0f, 0.0f, 1.0f), Vector2D(0.0f, 0.0f));
	_VertexList[13] = PNCT_VERTEX(Vector3D(-1.0f, 1.0f, -1.0f), Vector3D(-1.0f, 0.0f, 0.0f), Vector4D(1.0f, 1.0f, 0.0f, 1.0f), Vector2D(1.0f, 0.0f));
	_VertexList[14] = PNCT_VERTEX(Vector3D(-1.0f, -1.0f, -1.0f), Vector3D(-1.0f, 0.0f, 0.0f), Vector4D(1.0f, 1.0f, 0.0f, 1.0f), Vector2D(1.0f, 1.0f));
	_VertexList[15] = PNCT_VERTEX(Vector3D(-1.0f, -1.0f, 1.0f), Vector3D(-1.0f, 0.0f, 0.0f), Vector4D(1.0f, 1.0f, 0.0f, 1.0f), Vector2D(0.0f, 1.0f));

	// À­¸é
	_VertexList[16] = PNCT_VERTEX(Vector3D(-1.0f, 1.0f, 1.0f), Vector3D(0.0f, 1.0f, 0.0f), Vector4D(1.0f, 0.5f, 1.0f, 1.0f), Vector2D(0.0f, 0.0f));
	_VertexList[17] = PNCT_VERTEX(Vector3D(1.0f, 1.0f, 1.0f), Vector3D(0.0f, 1.0f, 0.0f), Vector4D(1.0f, 0.5f, 1.0f, 1.0f), Vector2D(1.0f, 0.0f));
	_VertexList[18] = PNCT_VERTEX(Vector3D(1.0f, 1.0f, -1.0f), Vector3D(0.0f, 1.0f, 0.0f), Vector4D(1.0f, 0.5f, 1.0f, 1.0f), Vector2D(1.0f, 1.0f));
	_VertexList[19] = PNCT_VERTEX(Vector3D(-1.0f, 1.0f, -1.0f), Vector3D(0.0f, 1.0f, 0.0f), Vector4D(1.0f, 0.5f, 1.0f, 1.0f), Vector2D(0.0f, 1.0f));

	// ¾Æ·§¸é
	_VertexList[20] = PNCT_VERTEX(Vector3D(-1.0f, -1.0f, -1.0f), Vector3D(0.0f, -1.0f, 0.0f), Vector4D(0.0f, 1.0f, 1.0f, 1.0f), Vector2D(0.0f, 0.0f));
	_VertexList[21] = PNCT_VERTEX(Vector3D(1.0f, -1.0f, -1.0f), Vector3D(0.0f, -1.0f, 0.0f), Vector4D(0.0f, 1.0f, 1.0f, 1.0f), Vector2D(1.0f, 0.0f));
	_VertexList[22] = PNCT_VERTEX(Vector3D(1.0f, -1.0f, 1.0f), Vector3D(0.0f, -1.0f, 0.0f), Vector4D(0.0f, 1.0f, 1.0f, 1.0f), Vector2D(1.0f, 1.0f));
	_VertexList[23] = PNCT_VERTEX(Vector3D(-1.0f, -1.0f, 1.0f), Vector3D(0.0f, -1.0f, 0.0f), Vector4D(0.0f, 1.0f, 1.0f, 1.0f), Vector2D(0.0f, 1.0f));


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

	_BoxCollision.vMin = Vector3D(100000, 100000, 100000);
	_BoxCollision.vMax = Vector3D(-100000, -100000, -100000);
	for (int iV = 0; iV < 8; ++iV)
	{
		Vector3D pos;
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

	Vector3D vHalf = _BoxCollision.vMax - _BoxCollision.vCenter;
	_BoxCollision.fExtent[0] = fabs(TBASIS_EX::D3DXVec3Dot((TBASIS_EX::TVector3*)&_BoxCollision.vAxis[0], (TBASIS_EX::TVector3*)&vHalf));
	_BoxCollision.fExtent[1] = fabs(TBASIS_EX::D3DXVec3Dot((TBASIS_EX::TVector3*)&_BoxCollision.vAxis[1], (TBASIS_EX::TVector3*)&vHalf));
	_BoxCollision.fExtent[2] = fabs(TBASIS_EX::D3DXVec3Dot((TBASIS_EX::TVector3*)&_BoxCollision.vAxis[2], (TBASIS_EX::TVector3*)&vHalf));
	_BoxCollision.vCenter = (_BoxCollision.vMin + _BoxCollision.vMax);
	_BoxCollision.vCenter /= 2.0f;
}

void Object3D::GenAABB()
{
	_BoxCollision.vMin = Vector3D(100000, 100000, 100000);
	_BoxCollision.vMax = Vector3D(-100000, -100000, -100000);
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
	_BoxCollision.vPos[0] = Vector3D(_BoxCollision.vMin.x,
	_BoxCollision.vMax.y,		   
	_BoxCollision.vMin.z);		   
	_BoxCollision.vPos[1] = Vector3D(_BoxCollision.vMax.x,
	_BoxCollision.vMax.y,		   
	_BoxCollision.vMin.z);		   
	_BoxCollision.vPos[2] = Vector3D(_BoxCollision.vMin.x,
	_BoxCollision.vMin.y,		   
	_BoxCollision.vMin.z);		   
	_BoxCollision.vPos[3] = Vector3D(_BoxCollision.vMax.x,
	_BoxCollision.vMin.y,		   
	_BoxCollision.vMin.z);		   
								   
	_BoxCollision.vPos[4] = Vector3D(_BoxCollision.vMin.x,
	_BoxCollision.vMax.y,		   
	_BoxCollision.vMax.z);		   
	_BoxCollision.vPos[5] = Vector3D(_BoxCollision.vMax.x,
	_BoxCollision.vMax.y,		   
	_BoxCollision.vMax.z);		   
	_BoxCollision.vPos[6] = Vector3D(_BoxCollision.vMin.x,
	_BoxCollision.vMin.y,		   
	_BoxCollision.vMax.z);		   
	_BoxCollision.vPos[7] = Vector3D(_BoxCollision.vMax.x,
		_BoxCollision.vMin.y,
		_BoxCollision.vMax.z);
}
