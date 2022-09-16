#pragma once
#include "BaseObject.h"


class BaseGameEntity : BaseObject
{
public:
	enum { default_entity_type = -1 };

private:
	int _ID;
	int _EntityType;
	bool _bTag;


};

