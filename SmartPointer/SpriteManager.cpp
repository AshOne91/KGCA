#include "SpriteManager.h"

bool SpriteManager::GameDataLoad(const TCHAR* pszLoad)
{
    TCHAR pBuffer[500] = { 0 };
    TCHAR pTemp[500] = { 0 };

    int iNumSprite = 0;
    FILE* fp_src;
    _wfopen_s(&fp_src, pszLoad, _T("rt"));
    if (fp_src == NULL) return false;

    _fgetts(pBuffer, _countof(pBuffer), fp_src);
    _stscanf_s(pBuffer, _T("%s%d%s"), pTemp, (unsigned int)_countof(pTemp), &iNumSprite);
    _rtSpriteList.resize(iNumSprite);


    for (int iCnt = 0; iCnt < iNumSprite; iCnt++)
    {
        int iNumFrame = 0;
        _fgetts(pBuffer, _countof(pBuffer), fp_src);
        _stscanf_s(pBuffer, _T("%s %d"), pTemp, (unsigned int)_countof(pTemp), &iNumFrame);
        //m_rtSpriteList[iCnt].resize(iNumFrame);
        _rtNameList.push_back(pTemp);

        RECT rt;
        for (int iFrame = 0; iFrame < iNumFrame; iFrame++)
        {
            _fgetts(pBuffer, _countof(pBuffer), fp_src);
            _stscanf_s(pBuffer, _T("%s %d %d %d %d"), pTemp, (unsigned int)_countof(pTemp),
                &rt.left, &rt.top, &rt.right, &rt.bottom);
            _rtSpriteList[iCnt].push_back(rt);
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
    _rtNameList.clear();

    if (GameDataLoad(filename.c_str()) == false)
    {
        return false;
    }
    filelist.push_back(filename);

    HRESULT hr;
    for (int iSp = 0; iSp < _rtSpriteList.size(); iSp++)
    {
        // �ߺ�����
        auto data = Find(_rtNameList[iSp]);
        if (data != nullptr) continue;

        //Sprite* pNewData = new Sprite;
        std::unique_ptr<Sprite> pNewData = std::make_unique<Sprite>();
        pNewData->_szName = _rtNameList[iSp];
        pNewData->_uvArray = _rtSpriteList[iSp];

        if (pNewData)
        {
            hr = pNewData->Load(_pd3dDevice, _pImmediateContext,
                filename);
            if (SUCCEEDED(hr))
            {
                _List.insert(std::make_pair(pNewData->_szName, std::move(pNewData)));
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