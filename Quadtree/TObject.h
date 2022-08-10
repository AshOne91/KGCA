#pragma once
#include "TShape.h"
#include <vector>
#include <string>
class TObject
{
public:
	TRect _rt;
	std::wstring m_csName;
	int _iIndex; //����ũ�� �ε���
public:
	void Create(TRect rt);
	void SetPos(float x, float y);
public:
	TObject();
	TObject(TRect& rt);
	~TObject();
};

