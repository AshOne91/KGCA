#include "Param.h"

Param* Param::Instance()
{
	static Param instance;

	return &instance;
}