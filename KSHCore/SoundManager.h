#pragma once
#include "Sound.h"

class SoundManager : public Singleton<SoundManager>
{
private:
	FMOD::System* _pSystem = nullptr;
	std::list<std::wstring> _fileList;

private:
	friend class Singleton<SoundManager>;
	std::map<std::wstring, Sound*> _List;

public:
	T_STR GetSplitName(const std::wstring& name);
	void LoadDir(const std::wstring& path);
	void LoadAll(const std::wstring& path);
	bool Init();
	bool Frame();
	Sound* Load(const std::wstring& filename);
	bool Release();
	Sound* GetPtr(const W_STR& name);

private:
	SoundManager();
public:
	~SoundManager();
};

#define I_Sound SoundManager::GetInstance()

