#include "SpriteManager.h"
Sprite  SpriteManager::_NullSprite;
bool SpriteManager::GameDataLoad(const TCHAR* pszLoad)
{
    TCHAR pBuffer[256] = { 0 };
    TCHAR pTemp[256] = { 0 };
    TCHAR pTexturePath[256] = { 0 };
    TCHAR pMaskTexturePath[256] = { 0 };
    TCHAR pShaderPath[256] = { 0 };

    int iNumSprite = 0;
    FILE* fp_src;
    _wfopen_s(&fp_src, pszLoad, _T("rt"));
    if (fp_src == NULL) return false;

    _fgetts(pBuffer, _countof(pBuffer), fp_src);
    _stscanf_s(pBuffer, _T("%s"), pTemp, (unsigned int)_countof(pTemp));
    //m_rtSpriteList.resize(iNumSprite);

    int iIsTexAnimation = 0;
    for (;;)
    {
        int iNumFrame = 0;
        _fgetts(pBuffer, _countof(pBuffer), fp_src);
        _stscanf_s(pBuffer, _T("%s %d%d %s%s%s"),
            pTemp, (unsigned int)_countof(pTemp), &iNumFrame,
            &iIsTexAnimation,
            pTexturePath, (unsigned int)_countof(pTexturePath),
            pMaskTexturePath, (unsigned int)_countof(pMaskTexturePath),
            pShaderPath, (unsigned int)_countof(pShaderPath));

        W_STR name = pTemp;
        if (name == L"#END")
        {
            break;
        }
        _iSpriteTypeList.push_back(iIsTexAnimation);
        _rtNameList.push_back(pTemp);
        _textureNameList.push_back(pTexturePath);
        _maskTextureNameList.push_back(pMaskTexturePath);
        _shaderNameList.push_back(pShaderPath);

        int iReadFrame = 0;
        if (iIsTexAnimation == 0)
        {
            RECT_ARRAY rtList;
            RECT rt;
            for (int iFrame = 0; iFrame < iNumFrame; iFrame++)
            {
                _fgetts(pBuffer, _countof(pBuffer), fp_src);
                _stscanf_s(pBuffer, _T("%d %d %d %d %d"),
                    &iReadFrame,
                    &rt.left, &rt.top, &rt.right, &rt.bottom);
                rtList.push_back(rt);
            }
            _rtSpriteList.push_back(rtList);
        }
        else
        {
            TCHAR_STRING_VECTOR list;
            for (int iFrame = 0; iFrame < iNumFrame; iFrame++)
            {
                _fgetts(pBuffer, _countof(pBuffer), fp_src);
                _stscanf_s(pBuffer, _T("%d %s"),
                    &iReadFrame,
                    pTemp, (unsigned int)_countof(pTemp));
                list.push_back(pTemp);
            }
            _szSpriteList.push_back(list);
        }
    }
    fclose(fp_src);


    return true;
}
void SpriteManager::SetDevice(
    ID3D11Device* pd3dDevice,
    ID3D11DeviceContext* pContext)
{
    _pd3dDevice = pd3dDevice;
    _pImmediateContext = pContext;
}
bool SpriteManager::Load(std::wstring filename)
{
    _rtSpriteList.clear();
    _szSpriteList.clear();
    _iSpriteTypeList.clear();
    _rtNameList.clear();
    _textureNameList.clear();
    _maskTextureNameList.clear();
    _shaderNameList.clear();

    if (GameDataLoad(filename.c_str()) == false)
    {
        return false;
    }

    for (int ifile = 0; ifile < filelist.size(); ifile++)
    {
        if (filelist[ifile] == filename)
        {
            return true;
        }
    }
    filelist.push_back(filename);

    HRESULT hr;
    UINT iCurrentTexIndex = 0;
    UINT iCurrentUVIndex = 0;
    for (int iSp = 0; iSp < _rtNameList.size(); iSp++)
    {
        // 중복제거
        auto data = Find(_rtNameList[iSp]);
        if (data != nullptr) continue;

        std::unique_ptr<Sprite> pNewData = nullptr;
        if (_iSpriteTypeList[iSp] == 0)
            pNewData = std::make_unique<Sprite>();
        else
            pNewData = std::make_unique<SpriteTexture>();

        pNewData->_szName = _rtNameList[iSp];
        pNewData->_szTexturePath = _textureNameList[iSp];
        pNewData->_szMaskTexturePath = _maskTextureNameList[iSp];
        pNewData->_szShaderPath = _shaderNameList[iSp];

        if (_iSpriteTypeList[iSp] == 1)
        {
            pNewData->_texArray = _szSpriteList[iCurrentTexIndex++];
        }
        else
        {
            pNewData->_uvArray = _rtSpriteList[iCurrentUVIndex++];
        }
        if (pNewData)
        {
            bool bRet = pNewData->Load(_pd3dDevice, _pImmediateContext, filename);
            if (bRet)
            {
                _List.insert(std::make_pair(pNewData->_szName, std::move(pNewData)));
            }
            else
            {
                pNewData->Release();
                pNewData.reset();
            }
        }
    }
    return true;
}
Sprite& SpriteManager::Get(W_STR name)
{
    auto iter = _List.find(name);
    if (iter != _List.end())
    {
        Sprite* pData = iter->second.get();
        return *pData;
    }
    return _NullSprite;
}
Sprite* SpriteManager::GetPtr(W_STR name)
{
    auto iter = _List.find(name);
    if (iter != _List.end())
    {
        Sprite* pData = iter->second.get();
        return pData;
    }
    return nullptr;
}
Sprite* SpriteManager::Find(std::wstring name)
{
    auto iter = _List.find(name);
    if (iter != _List.end())
    {
        return iter->second.get();
    }
    return nullptr;
}
SpriteManager::SpriteManager()
{
}
bool SpriteManager::Release()
{
    for (auto& data : _List)
    {
        data.second->Release();
    }
    _List.clear();
    return true;
}
SpriteManager::~SpriteManager()
{
    Release();
}
