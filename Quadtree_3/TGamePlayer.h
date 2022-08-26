#pragma once
#include "TObject.h"
class TGamem_player :  public TObject
{
public:
	void	Frame(float fDeltaTime, float fGameTime) override;
};

