#include "Sample.h"

bool Sample::Init()
{
	return true;
}

bool Sample::Frame()
{
	return true;
}

bool Sample::Render()
{
	return true;
}

bool Sample::Release()
{
	return true;
}

GAME_RUN(KSHCoreSample, 1024, 768)