#include "Shape.h"
#include "Input.h"

void ShapeBox::CreateVertexData()
{
	// »ó´Ü
  // 5    6
  // 1    2
  // ÇÏ´Ü
  // 4    7
  // 0    3  
  // ¾Õ¸é
	_VertexList.resize(24);
	_VertexList[0] = SimpleVertex(Vector3D(-1.0f, 1.0f, -1.0f), Vector4D(1.0f, 0.0f, 0.0f, 1.0f), Vector2D(0.0f, 0.0f));
	_VertexList[1] = SimpleVertex(Vector3D(1.0f, 1.0f, -1.0f), Vector4D(1.0f, 0.0f, 0.0f, 1.0f), Vector2D(1.0f, 0.0f));
	_VertexList[2] = SimpleVertex(Vector3D(1.0f, -1.0f, -1.0f), Vector4D(1.0f, 0.0f, 0.0f, 1.0f), Vector2D(1.0f, 1.0f));
	_VertexList[3] = SimpleVertex(Vector3D(-1.0f, -1.0f, -1.0f), Vector4D(1.0f, 0.0f, 0.0f, 1.0f), Vector2D(0.0f, 1.0f));
	// µÞ¸é
	_VertexList[4] = SimpleVertex(Vector3D(1.0f, 1.0f, 1.0f), Vector4D(0.0f, 0.0f, 0.0f, 1.0f), Vector2D(0.0f, 0.0f));
	_VertexList[5] = SimpleVertex(Vector3D(-1.0f, 1.0f, 1.0f), Vector4D(0.0f, 1.0f, 0.0f, 1.0f), Vector2D(1.0f, 0.0f));
	_VertexList[6] = SimpleVertex(Vector3D(-1.0f, -1.0f, 1.0f), Vector4D(0.0f, 1.0f, 0.0f, 1.0f), Vector2D(1.0f, 1.0f));
	_VertexList[7] = SimpleVertex(Vector3D(1.0f, -1.0f, 1.0f), Vector4D(0.0f, 1.0f, 0.0f, 1.0f), Vector2D(0.0f, 1.0f));

	// ¿À¸¥ÂÊ
	_VertexList[8] = SimpleVertex(Vector3D(1.0f, 1.0f, -1.0f), Vector4D(0.0f, 0.0f, 1.0f, 1.0f), Vector2D(0.0f, 0.0f));
	_VertexList[9] = SimpleVertex(Vector3D(1.0f, 1.0f, 1.0f), Vector4D(0.0f, 0.0f, 1.0f, 1.0f), Vector2D(1.0f, 0.0f));
	_VertexList[10] = SimpleVertex(Vector3D(1.0f, -1.0f, 1.0f), Vector4D(0.0f, 0.0f, 1.0f, 1.0f), Vector2D(1.0f, 1.0f));
	_VertexList[11] = SimpleVertex(Vector3D(1.0f, -1.0f, -1.0f), Vector4D(0.0f, 0.0f, 1.0f, 1.0f), Vector2D(0.0f, 1.0f));

	// ¿ÞÂÊ
	_VertexList[12] = SimpleVertex(Vector3D(-1.0f, 1.0f, 1.0f), Vector4D(1.0f, 1.0f, 0.0f, 1.0f), Vector2D(0.0f, 0.0f));
	_VertexList[13] = SimpleVertex(Vector3D(-1.0f, 1.0f, -1.0f), Vector4D(1.0f, 1.0f, 0.0f, 1.0f), Vector2D(1.0f, 0.0f));
	_VertexList[14] = SimpleVertex(Vector3D(-1.0f, -1.0f, -1.0f), Vector4D(1.0f, 1.0f, 0.0f, 1.0f), Vector2D(1.0f, 1.0f));
	_VertexList[15] = SimpleVertex(Vector3D(-1.0f, -1.0f, 1.0f), Vector4D(1.0f, 1.0f, 0.0f, 1.0f), Vector2D(0.0f, 1.0f));

	// À­¸é
	_VertexList[16] = SimpleVertex(Vector3D(-1.0f, 1.0f, 1.0f), Vector4D(1.0f, 0.5f, 1.0f, 1.0f), Vector2D(0.0f, 0.0f));
	_VertexList[17] = SimpleVertex(Vector3D(1.0f, 1.0f, 1.0f), Vector4D(1.0f, 0.5f, 1.0f, 1.0f), Vector2D(1.0f, 0.0f));
	_VertexList[18] = SimpleVertex(Vector3D(1.0f, 1.0f, -1.0f), Vector4D(1.0f, 0.5f, 1.0f, 1.0f), Vector2D(1.0f, 1.0f));
	_VertexList[19] = SimpleVertex(Vector3D(-1.0f, 1.0f, -1.0f), Vector4D(1.0f, 0.5f, 1.0f, 1.0f), Vector2D(0.0f, 1.0f));

	// ¾Æ·§¸é
	_VertexList[20] = SimpleVertex(Vector3D(-1.0f, -1.0f, -1.0f), Vector4D(0.0f, 1.0f, 1.0f, 1.0f), Vector2D(0.0f, 0.0f));
	_VertexList[21] = SimpleVertex(Vector3D(1.0f, -1.0f, -1.0f), Vector4D(0.0f, 1.0f, 1.0f, 1.0f), Vector2D(1.0f, 0.0f));
	_VertexList[22] = SimpleVertex(Vector3D(1.0f, -1.0f, 1.0f), Vector4D(0.0f, 1.0f, 1.0f, 1.0f), Vector2D(1.0f, 1.0f));
	_VertexList[23] = SimpleVertex(Vector3D(-1.0f, -1.0f, 1.0f), Vector4D(0.0f, 1.0f, 1.0f, 1.0f), Vector2D(0.0f, 1.0f));


	_InitVertexList = _VertexList;
}

void ShapeBox::CreateIndexData()
{
	_IndexList.resize(36);
	int iIndex = 0;
	_IndexList[iIndex++] = 0;  _IndexList[iIndex++] = 1;  _IndexList[iIndex++] = 2;  _IndexList[iIndex++] = 0;	_IndexList[iIndex++] = 2;  _IndexList[iIndex++] = 3;
	_IndexList[iIndex++] = 4;  _IndexList[iIndex++] = 5;  _IndexList[iIndex++] = 6;  _IndexList[iIndex++] = 4;	_IndexList[iIndex++] = 6;  _IndexList[iIndex++] = 7;
	_IndexList[iIndex++] = 8;  _IndexList[iIndex++] = 9;  _IndexList[iIndex++] = 10; _IndexList[iIndex++] = 8;	_IndexList[iIndex++] = 10; _IndexList[iIndex++] = 11;
	_IndexList[iIndex++] = 12; _IndexList[iIndex++] = 13; _IndexList[iIndex++] = 14; _IndexList[iIndex++] = 12;	_IndexList[iIndex++] = 14; _IndexList[iIndex++] = 15;
	_IndexList[iIndex++] = 16; _IndexList[iIndex++] = 17; _IndexList[iIndex++] = 18; _IndexList[iIndex++] = 16;	_IndexList[iIndex++] = 18; _IndexList[iIndex++] = 19;
	_IndexList[iIndex++] = 20; _IndexList[iIndex++] = 21; _IndexList[iIndex++] = 22; _IndexList[iIndex++] = 20;	_IndexList[iIndex++] = 22; _IndexList[iIndex++] = 23;
}

bool ShapeBox::Frame()
{
	//Matrix m, s, t, c;
	//float fScale = cos(g_fGameTimer) * 0.5f + 0.5f;
	//s = TMath::Scale(400, 300, 10);
	//m = TMath::RotationZ(g_fGameTimer);
	//t = TMath::Translation(0.0f, 0, 0);
	//_matWorld = s * m * t;
	_cbData.fTimer = g_fGameTimer;
	return true;
}

bool ShapeBox::Render()
{
	PreRender();
	PostRender();
	return true;
}
