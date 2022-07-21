#include "BaseObject.h"

void BaseObject::Awake()
{
	Construct();
}

void BaseObject::OnDestroy()
{
	Destruct();
}