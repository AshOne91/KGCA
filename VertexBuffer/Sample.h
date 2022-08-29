#pragma once
#include "TDevice.h"
struct SimpleVertex
{
	float x;
	float y;
	float z;
	float r;
	float g;
	float b;
	float a;
};
class Sample : public TDevice
{
	ID3D11Buffer* m_pVertexBuffer = nullptr;
	ID3D11InputLayout* m_pVertexLayout = nullptr;
	ID3D11VertexShader* m_pVertexShader = nullptr;
	ID3D11PixelShader* m_pPixelShader = nullptr;
	ID3DBlob* m_pVSCode = nullptr;
	ID3DBlob* m_pPSCode = nullptr;
public:
	HRESULT CreateVertexBuffer();
	HRESULT CreateShader();
	HRESULT CreateVertexLayout();
	bool		Init(); // 초기화
	bool		Frame();// 실시간 계산
	bool		Render();// 실시간 랜더링
	bool		Release();// 소멸 및 삭제
};

