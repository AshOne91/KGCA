#include "KFbxFile.h"

HRESULT KFbxFile::CreateConstantBuffer(ID3D11Device* pDevice)
{
    HRESULT hr;
    for (int iBone = 0; iBone < 255; ++iBone)
    {
        D3DXMatrixIdentity(&_cbDataBone.matBone[iBone]);
    }

    D3D11_BUFFER_DESC bd;
    ZeroMemory(&bd, sizeof(bd));
    bd.ByteWidth = sizeof(VS_CONSTANT_BONE_BUFFER) * 1; // 바이트 용량
    //GPU 메모리에 할당
    bd.Usage = D3D11_USAGE_DEFAULT; // 버퍼의 할당 장소 내지는 버퍼용도
    bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;

    D3D11_SUBRESOURCE_DATA sd;
    ZeroMemory(&sd, sizeof(sd));
    sd.pSysMem = &_cbDataBone;
    hr = pDevice->CreateBuffer(
        &bd, // 버퍼 할당
        &sd, // 초기 할당된 버퍼를 채우는 CPU메모리 주소
        &_pConstantBufferBone);
    return hr;
}

bool KFbxFile::UpdateFrame(ID3D11DeviceContext* pContext)
{
    _fAnimFrame = _fAnimFrame +
        g_fSecondPerFrame * _fAnimSpeed * _AnimScene.fFrameSpeed * _fAnimInverse;
    if (_fAnimFrame > _AnimScene.iEndFrame ||
        _fAnimFrame < _AnimScene.iStartFrame)
    {
        _fAnimFrame = min(_fAnimFrame, _AnimScene.iEndFrame);
        _fAnimFrame = max(_fAnimFrame, _AnimScene.iStartFrame);
        _fAnimInverse *= -1.0f;
    }

    /*for (int iBone = 0; iBone < _pObjectList.size(); ++iBone)
    {
        TMatrix matAnim = _pObjectList[iBone]->Interplate(_fAnimFrame, _AnimScene);
        D3DXMatrixTranspose(&_cbDataBone.matBone[iBone], &matAnim);
    }*/

    for (int iBone = 0; iBone < _pObjectList.size(); ++iBone)
    {
        TMatrix matAnim2 = _pObjectList[iBone]->Interplate(_fAnimFrame, _AnimScene);
        if (_pObjectList[iBone]->_dxMatrixBindPseMap.size())
        {
            auto iter = _pObjectList[iBone]->_dxMatrixBindPseMap.find(iBone);
            if (iter != _pObjectList[iBone]->_dxMatrixBindPseMap.end())
            {
                TMatrix matBind = iter->second;
                TMatrix matAnim = matBind * matAnim2;
                D3DXMatrixTranspose(&_cbDataBone.matBone[iBone], &matAnim);
            }
        }
    }
    pContext->UpdateSubresource(_pConstantBufferBone, 0, nullptr, &_cbDataBone, 0, 0);
    return true;
}

bool KFbxFile::Render()
{
    for (auto obj : _pDrawObjList)
    {
        obj->Render();
    }
    return true;
}

