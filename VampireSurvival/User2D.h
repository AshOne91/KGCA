#pragma once
#include "Object2D.h"

class User2D : public Object2D
{
public:
	void UpdateVertexBuffer() override;
	bool Frame() override;
};

