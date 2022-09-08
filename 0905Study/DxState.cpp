#include "DxState.h"
ID3D11SamplerState* DxState::g_pDefaultSS = nullptr;

bool DxState::SetState(ID3D11Device* p3d3Device)
{
    // SS
    D3D11_SAMPLER_DESC sd;
    /*ZeroMemory(&sd, sizeof(sd));
    D3D11_FILTER Filter;
    D3D11_TEXTURE_ADDRESS_MODE AddressU;
    D3D11_TEXTURE_ADDRESS_MODE AddressV;
    D3D11_TEXTURE_ADDRESS_MODE AddressW;
    FLOAT MipLODBias;
    UINT MaxAnisotropy;
    D3D11_COMPARISON_FUNC ComparisonFunc;
    FLOAT BorderColor[4];
    FLOAT MinLOD;
    FLOAT MaxLOD;*/
    sd.Filter = D3D11_FILTER_MIN_MAG_MIP_POINT;//(�ֱ��� ���͸�)� �ȼ��� �۾��� �� Ŭ �� �Ҹ��� ��� �ҷ�?
    sd.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
    sd.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
    sd.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;

    p3d3Device->CreateSamplerState(&sd, &g_pDefaultSS);
    return true;
}

bool DxState::Release()
{
    if (g_pDefaultSS) g_pDefaultSS->Release();
    return true;
}
