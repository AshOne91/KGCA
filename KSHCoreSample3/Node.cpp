#include "Node.h"
void Node::CreateIndexData(Map* pMap, DWORD dwNumCols, DWORD dwNumRows)
{
	// 0  1   2   3   4
	// 5  6   7   8   9
	// 10 11  12  13  14
	// 15 16  17  18  19
	// 20  21 22  23  24
	DWORD dwTL = _Corner[0];
	DWORD dwTR = _Corner[1];
	DWORD dwBL = _Corner[2];
	DWORD dwBR = _Corner[3];
	DWORD dwNumRowCell = (dwBL - dwTL) / dwNumCols;
	DWORD dwNumColCell = dwTR - dwTL;
	DWORD dwNumCells = dwNumRowCell * dwNumColCell;
	_IndexList.resize(dwNumCells * 2 * 3);
	int iIndex = 0;

	_kBox.vMin.x = pMap->_VertexList[dwTL].p.x;
	_kBox.vMin.y = 100000.0f;
	_kBox.vMin.z = pMap->_VertexList[dwBL].p.z;
	_kBox.vMax.x = pMap->_VertexList[dwTR].p.x;
	_kBox.vMax.y = -100000.0f;
	_kBox.vMax.z = pMap->_VertexList[dwTL].p.z;
	for (int dwRow = 0; dwRow < dwNumRowCell; ++dwRow)
	{
		for (int dwCol = 0; dwCol < dwNumColCell; ++dwCol)
		{
			_IndexList[iIndex + 0] = dwTL + dwCol + (dwRow * dwNumCols);
			_IndexList[iIndex + 1] = _IndexList[iIndex + 0] + 1;
			_IndexList[iIndex + 2] = dwTL + dwCol + ((dwRow + 1) * dwNumCols);

			_IndexList[iIndex + 3] = _IndexList[iIndex + 2];
			_IndexList[iIndex + 4] = _IndexList[iIndex + 1];
			_IndexList[iIndex + 5] = _IndexList[iIndex + 2] + 1;

			for (DWORD dwVertex = 0; dwVertex < 6; ++dwVertex)
			{
				if (_kBox.vMin.y > pMap->_VertexList[_IndexList[iIndex + dwVertex]].p.y)
				{
					_kBox.vMin.y = pMap->_VertexList[_IndexList[iIndex + dwVertex]].p.y;
				}
				if (_kBox.vMax.y < pMap->_VertexList[_IndexList[iIndex + dwVertex]].p.y)
				{
					_kBox.vMax.y = pMap->_VertexList[_IndexList[iIndex + dwVertex]].p.y;
				}
			}
			iIndex += 6;
		}
	}
	_dwFace = _IndexList.size() / 3;
	_kBox.vCenter = (_kBox.vMax + _kBox.vMin) * 0.5f;
	_kBox.vAxis[0] = { 1, 0, 0 };
	_kBox.vAxis[1] = { 0, 1, 0 };
	_kBox.vAxis[2] = { 0, 0, 1 };
	_kBox.fExtent[0] = _kBox.vMax.x - _kBox.vCenter.x;
	_kBox.fExtent[1] = _kBox.vMax.y - _kBox.vCenter.y;
	_kBox.fExtent[2] = _kBox.vMax.z - _kBox.vCenter.z;

}

HRESULT Node::CreateIndexBuffer(Map* pMap, DWORD dwNumRows, DWORD dwNumCols)
{
	HRESULT hr;
	CreateIndexData(pMap, dwNumRows, dwNumCols);
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.ByteWidth = sizeof(DWORD) * _IndexList.size();
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.BindFlags = D3D11_BIND_INDEX_BUFFER;

	D3D11_SUBRESOURCE_DATA sd;
	ZeroMemory(&sd, sizeof(sd));
	sd.pSysMem = &_IndexList.at(0);
	hr = pMap->_pd3dDevice->CreateBuffer(&bd, &sd, &_pIndexBuffer);
	return hr;
}

void Node::CreateChildNode(Node* pParent, Map* pMap, DWORD dwNumCols, DWORD dwNumRows)
{
	// 0  1   2   3   4
	// 5  6   7   8   9
	// 10 11  12  13  14
	// 15 16  17  18  19
	// 20  21 22  23  24
	Rect rt = pParent->_rt;
	DWORD dwLT = pParent->_Corner[0];
	DWORD dwRT = pParent->_Corner[1];
	DWORD dwLB = pParent->_Corner[2];
	DWORD dwRB = pParent->_Corner[3];
	DWORD dwTopCenter = (dwLT + dwRT) / 2;
	DWORD dwRightCenter = (dwRB + dwRT) / 2;
	DWORD dwBottomCenter = (dwLB + dwRB) / 2;
	DWORD dwLeftCenter = (dwLB + dwLT) / 2;
	DWORD dwCenter = (dwRT + dwLT + dwRB + dwLB) / 4;
	_pChild[0] = new Node(pParent, pMap, dwLT, dwTopCenter, dwLeftCenter, dwCenter, dwNumCols, dwNumRows);
	_pChild[1] = new Node(pParent, pMap, dwTopCenter, dwRT, dwCenter, dwRightCenter, dwNumCols, dwNumRows);
	_pChild[2] = new Node(pParent, pMap, dwLeftCenter, dwCenter, dwLB, dwBottomCenter, dwNumCols, dwNumRows);
	_pChild[3] = new Node(pParent, pMap, dwCenter, dwRightCenter, dwBottomCenter, dwRB, dwNumCols, dwNumRows);
}

//  0, 1
//  2, 3
Node::Node(Node* pParent, Map* pMap, DWORD dwLT, DWORD dwRT, DWORD dwRB, DWORD dwLB, DWORD dwNumCols, DWORD dwNumRows)
{
	if (pParent != nullptr)
	{
		_iDepth = pParent->_iDepth + 1;
	}
	_Corner[0] = dwLT;
	_Corner[1] = dwRT;
	_Corner[2] = dwRB;
	_Corner[3] = dwLB;
	_bLeaf = false;
	_pChild.resize(4);
	// boundingBox(aabb, obb)
	// 0  1   2   3   4
	// 5  6   7   8   9
	// 10 11  12  13  14
	// 15 16  17  18  19
	// 20  21 22  23  24

	CreateIndexBuffer(pMap, dwNumCols, dwNumRows);
}

Node::~Node()
{
	if (_pIndexBuffer) _pIndexBuffer->Release();
	delete _pChild[0];
	delete _pChild[1];
	delete _pChild[2];
	delete _pChild[3];
	_pChild[0] = nullptr;
	_pChild[1] = nullptr;
	_pChild[2] = nullptr;
	_pChild[3] = nullptr;
	_pIndexBuffer = nullptr;
}