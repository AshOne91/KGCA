#include "Shape.h"
#include "Input.h"

void ShapeBox::CreateVertexData()
{// 상단
// 5    6
// 1    2
// 하단
// 4    7
// 0    3  
// 앞면
	_VertexList.resize(24);
	_VertexList[0] = PNCT_VERTEX(Vector3D(-1.0f, 1.0f, -1.0f), Vector3D(0.0f, 0.0f, -1.0f), Vector4D(1.0f, 0.0f, 0.0f, 1.0f), Vector2D(0.0f, 0.0f));
	_VertexList[1] = PNCT_VERTEX(Vector3D(1.0f, 1.0f, -1.0f), Vector3D(0.0f, 0.0f, -1.0f), Vector4D(1.0f, 0.0f, 0.0f, 1.0f), Vector2D(1.0f, 0.0f));
	_VertexList[2] = PNCT_VERTEX(Vector3D(1.0f, -1.0f, -1.0f), Vector3D(0.0f, 0.0f, -1.0f), Vector4D(1.0f, 0.0f, 0.0f, 1.0f), Vector2D(1.0f, 1.0f));
	_VertexList[3] = PNCT_VERTEX(Vector3D(-1.0f, -1.0f, -1.0f), Vector3D(0.0f, 0.0f, -1.0f), Vector4D(1.0f, 0.0f, 0.0f, 1.0f), Vector2D(0.0f, 1.0f));
	// 뒷면
	_VertexList[4] = PNCT_VERTEX(Vector3D(1.0f, 1.0f, 1.0f), Vector3D(0.0f, 0.0f, 1.0f), Vector4D(0.0f, 0.0f, 0.0f, 1.0f), Vector2D(0.0f, 0.0f));
	_VertexList[5] = PNCT_VERTEX(Vector3D(-1.0f, 1.0f, 1.0f), Vector3D(0.0f, 0.0f, 1.0f), Vector4D(0.0f, 1.0f, 0.0f, 1.0f), Vector2D(1.0f, 0.0f));
	_VertexList[6] = PNCT_VERTEX(Vector3D(-1.0f, -1.0f, 1.0f), Vector3D(0.0f, 0.0f, 1.0f), Vector4D(0.0f, 1.0f, 0.0f, 1.0f), Vector2D(1.0f, 1.0f));
	_VertexList[7] = PNCT_VERTEX(Vector3D(1.0f, -1.0f, 1.0f), Vector3D(0.0f, 0.0f, 1.0f), Vector4D(0.0f, 1.0f, 0.0f, 1.0f), Vector2D(0.0f, 1.0f));

	// 오른쪽
	_VertexList[8] = PNCT_VERTEX(Vector3D(1.0f, 1.0f, -1.0f), Vector3D(1.0f, 0.0f, 0.0f), Vector4D(0.0f, 0.0f, 1.0f, 1.0f), Vector2D(0.0f, 0.0f));
	_VertexList[9] = PNCT_VERTEX(Vector3D(1.0f, 1.0f, 1.0f), Vector3D(1.0f, 0.0f, -1.0f), Vector4D(0.0f, 0.0f, 1.0f, 1.0f), Vector2D(1.0f, 0.0f));
	_VertexList[10] = PNCT_VERTEX(Vector3D(1.0f, -1.0f, 1.0f), Vector3D(1.0f, 0.0f, -1.0f), Vector4D(0.0f, 0.0f, 1.0f, 1.0f), Vector2D(1.0f, 1.0f));
	_VertexList[11] = PNCT_VERTEX(Vector3D(1.0f, -1.0f, -1.0f), Vector3D(1.0f, 0.0f, -1.0f), Vector4D(0.0f, 0.0f, 1.0f, 1.0f), Vector2D(0.0f, 1.0f));

	// 왼쪽
	_VertexList[12] = PNCT_VERTEX(Vector3D(-1.0f, 1.0f, 1.0f), Vector3D(-1.0f, 0.0f, 0.0f), Vector4D(1.0f, 1.0f, 0.0f, 1.0f), Vector2D(0.0f, 0.0f));
	_VertexList[13] = PNCT_VERTEX(Vector3D(-1.0f, 1.0f, -1.0f), Vector3D(-1.0f, 0.0f, 0.0f), Vector4D(1.0f, 1.0f, 0.0f, 1.0f), Vector2D(1.0f, 0.0f));
	_VertexList[14] = PNCT_VERTEX(Vector3D(-1.0f, -1.0f, -1.0f), Vector3D(-1.0f, 0.0f, 0.0f), Vector4D(1.0f, 1.0f, 0.0f, 1.0f), Vector2D(1.0f, 1.0f));
	_VertexList[15] = PNCT_VERTEX(Vector3D(-1.0f, -1.0f, 1.0f), Vector3D(-1.0f, 0.0f, 0.0f), Vector4D(1.0f, 1.0f, 0.0f, 1.0f), Vector2D(0.0f, 1.0f));

	// 윗면
	_VertexList[16] = PNCT_VERTEX(Vector3D(-1.0f, 1.0f, 1.0f), Vector3D(0.0f, 1.0f, 0.0f), Vector4D(1.0f, 0.5f, 1.0f, 1.0f), Vector2D(0.0f, 0.0f));
	_VertexList[17] = PNCT_VERTEX(Vector3D(1.0f, 1.0f, 1.0f), Vector3D(0.0f, 1.0f, 0.0f), Vector4D(1.0f, 0.5f, 1.0f, 1.0f), Vector2D(1.0f, 0.0f));
	_VertexList[18] = PNCT_VERTEX(Vector3D(1.0f, 1.0f, -1.0f), Vector3D(0.0f, 1.0f, 0.0f), Vector4D(1.0f, 0.5f, 1.0f, 1.0f), Vector2D(1.0f, 1.0f));
	_VertexList[19] = PNCT_VERTEX(Vector3D(-1.0f, 1.0f, -1.0f), Vector3D(0.0f, 1.0f, 0.0f), Vector4D(1.0f, 0.5f, 1.0f, 1.0f), Vector2D(0.0f, 1.0f));

	// 아랫면
	_VertexList[20] = PNCT_VERTEX(Vector3D(-1.0f, -1.0f, -1.0f), Vector3D(0.0f, -1.0f, 0.0f), Vector4D(0.0f, 1.0f, 1.0f, 1.0f), Vector2D(0.0f, 0.0f));
	_VertexList[21] = PNCT_VERTEX(Vector3D(1.0f, -1.0f, -1.0f), Vector3D(0.0f, -1.0f, 0.0f), Vector4D(0.0f, 1.0f, 1.0f, 1.0f), Vector2D(1.0f, 0.0f));
	_VertexList[22] = PNCT_VERTEX(Vector3D(1.0f, -1.0f, 1.0f), Vector3D(0.0f, -1.0f, 0.0f), Vector4D(0.0f, 1.0f, 1.0f, 1.0f), Vector2D(1.0f, 1.0f));
	_VertexList[23] = PNCT_VERTEX(Vector3D(-1.0f, -1.0f, 1.0f), Vector3D(0.0f, -1.0f, 0.0f), Vector4D(0.0f, 1.0f, 1.0f, 1.0f), Vector2D(0.0f, 1.0f));


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
	_dwFace = _IndexList.size() / 3;
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

void ShapeLine::CreateVertexData()
{
	_VertexList.resize(2);
	_VertexList[0] = PNCT_VERTEX(Vector3D(0.0f, 0.0f, 0.0f), Vector3D(0.0f, 0.0f, -1.0f), Vector4D(1.0f, 0.0f, 0.0f, 1.0f), Vector2D(0.0f, 0.0f));
	_VertexList[1] = PNCT_VERTEX(Vector3D(0.0f, 0.0f, 1000.0f), Vector3D(0.0f, 0.0f, -1.0f), Vector4D(1.0f, 0.0f, 0.0f, 1.0f), Vector2D(1.0f, 0.0f));
	_InitVertexList = _VertexList;
}

void ShapeLine::CreateIndexData()
{
	_IndexList.resize(2);
	int iIndex = 0;
	_IndexList[iIndex++] = 0; 	_IndexList[iIndex++] = 1;
	_dwFace = _IndexList.size() / 3;
}

bool ShapeLine::Frame()
{
	_cbData.fTimer = g_fGameTimer;
	return true;
}

bool ShapeLine::Render()
{
	_pImmediateContext->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_LINELIST);
	PreRender();
	PostRender();
	_pImmediateContext->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	return true;
}

void ShapeDirectionLine::CreateVertexData()
{
	// 상단
  // 5    6
  // 1    2
  // 하단
  // 4    7
  // 0    3  
  // 앞면
	_VertexList.resize(6);
	_VertexList[0] = PNCT_VERTEX(Vector3D(0.0f, 0.0f, 0.0f), Vector3D(0.0f, 0.0f, -1.0f), Vector4D(1.0f, 0.0f, 0.0f, 1.0f), Vector2D(0.0f, 0.0f));
	_VertexList[1] = PNCT_VERTEX(Vector3D(1.0f, 0.0f, 0.0f), Vector3D(0.0f, 0.0f, -1.0f), Vector4D(1.0f, 0.0f, 0.0f, 1.0f), Vector2D(1.0f, 0.0f));
	_VertexList[2] = PNCT_VERTEX(Vector3D(0.0f, 0.0f, 0.0f), Vector3D(0.0f, 0.0f, -1.0f), Vector4D(0.0f, 1.0f, 0.0f, 1.0f), Vector2D(0.0f, 0.0f));
	_VertexList[3] = PNCT_VERTEX(Vector3D(0.0f, 1.0f, 0.0f), Vector3D(0.0f, 0.0f, -1.0f), Vector4D(0.0f, 1.0f, 0.0f, 1.0f), Vector2D(1.0f, 0.0f));
	_VertexList[4] = PNCT_VERTEX(Vector3D(0.0f, 0.0f, 0.0f), Vector3D(0.0f, 0.0f, -1.0f), Vector4D(0.0f, 0.0f, 1.0f, 1.0f), Vector2D(0.0f, 0.0f));
	_VertexList[5] = PNCT_VERTEX(Vector3D(0.0f, 0.0f, 1.0f), Vector3D(0.0f, 0.0f, -1.0f), Vector4D(0.0f, 0.0f, 1.0f, 1.0f), Vector2D(1.0f, 0.0f));
	_InitVertexList = _VertexList;
}

void ShapeDirectionLine::CreateIndexData()
{
	_IndexList.resize(6);
	int iIndex = 0;
	_IndexList[iIndex++] = 0; 	_IndexList[iIndex++] = 1;
	_IndexList[iIndex++] = 2; 	_IndexList[iIndex++] = 3;
	_IndexList[iIndex++] = 4; 	_IndexList[iIndex++] = 5;
	_dwFace = _IndexList.size() / 3;
}
