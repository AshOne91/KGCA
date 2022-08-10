#include "TObject.h"
void TObject::Create(TRect rt)
{
	_rt = rt;
}
void TObject::SetPos(float x, float y)
{
	_rt.left = x;
	_rt.top = y;
}
TObject::TObject()
{
	
}
TObject::TObject(TRect& rt)
{
	_rt = rt;
}
TObject::~TObject()
{
}
