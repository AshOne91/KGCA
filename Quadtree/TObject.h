#pragma once
#include "TShape.h"
#include <vector>
#include <string>
class TObject
{
public:
	TRect _rt;
	std::wstring m_csName;
	int _iIndex; //유니크한 인덱스
public:
	void Create(TRect rt);
	void SetPos(float x, float y);
public:
	TObject();
	TObject(TRect& rt);
	~TObject();
};

