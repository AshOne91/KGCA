#include "SoundManager.h"
#include <tchar.h>
#include <io.h>//_findclose
T_STR SoundManager::GetSplitName(const std::wstring& name)
{
    W_STR tempName;
    TCHAR drive[MAX_PATH] = {0,};
    TCHAR dir[MAX_PATH] = { 0, };
    TCHAR filename[MAX_PATH] = { 0, };
    TCHAR ext[MAX_PATH] = { 0, };
    _tsplitpath_s(name.c_str(), drive, dir, filename, ext);
    tempName = name;
    tempName += ext;
    return tempName;
}

void SoundManager::LoadDir(const std::wstring& path)
{
    W_STR dirpath = path + L"*.*";
    intptr_t handle;
    struct _wfinddata_t fd;
    handle = _wfindfirst(dirpath.c_str(), &fd);
    if (handle == -1L)
    {
        return;
    }

    do
    {
        if ((fd.attrib & _A_SUBDIR) && fd.name[0] != '.')
        {
            LoadDir(path + fd.name + L"/");
        }
        else if (fd.name[0] != '.')
        {
            _fileList.push_back(path + fd.name);
        }
    } while (_wfindnext(handle, &fd) == 0);
    _findclose(handle);
}

void SoundManager::LoadAll(const std::wstring& path)
{
    LoadDir(path);
    for (auto& data : _fileList)
    {
        Load(data);
    }
}

bool SoundManager::Init()
{
    FMOD::System_Create(&_pSystem);
    _pSystem->init(32, FMOD_INIT_NORMAL, 0);
    return true;
}

bool SoundManager::Frame()
{
    return true;
}

Sound* SoundManager::Load(const std::wstring& filename)
{
    HRESULT hr;
    W_STR name = GetSplitName(filename);
    auto iter = _List.find(name);
    if (iter != _List.end())
    {
        return iter->second;
    }

    Sound* pNewData = new Sound;
    pNewData->_szName = filename;
    if (pNewData != nullptr)
    {
        bool isLoad = pNewData->Load(_pSystem, filename);
        if (isLoad == true)
        {
            _List.insert(std::make_pair(name, pNewData));
        }
    }
    return pNewData;
}

bool SoundManager::Release()
{
    _pSystem->update();
    for (auto& data : _List)
    {
        Sound* pData = data.second;
        if (pData != nullptr)
        {
            pData->Frame();
        }
    }
    return true;
}

Sound* SoundManager::GetPtr(const W_STR& name)
{
    auto iter = _List.find(name);
    if (iter == _List.end())
    {
        return nullptr;
    }

    return iter->second;
}

SoundManager::SoundManager()
{
}

SoundManager::~SoundManager()
{
    Release();
}
