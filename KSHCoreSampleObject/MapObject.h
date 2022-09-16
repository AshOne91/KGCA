#pragma once
#include "Object2D.h"

class MapObject : public Object2D
{
	bool   FrameScroll();
public:
	bool   Frame() override;
	void  UpdateVertexBuffer() override;
};

