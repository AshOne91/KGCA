#include "Effect2D.h"

Rect Effect2D::convert(RECT rt)
{
	Rect tRt;
	tRt.x1 = rt.left;
	tRt.y1 = rt.top;
	tRt.w = rt.right;
	tRt.h = rt.bottom;
	return tRt;
}
bool Effect2D::Update()
{
	_fEffectTimer += g_fSecondPerFrame;
	if (_fStep <= _fEffectTimer)
	{
		_fEffectTimer -= _fStep;
		_iIndex++;
	}
	if (_iIndex >= _iMaxIndex)
	{
		return false;
	}
	RECT rt = _pSprite->_uvArray[_iIndex];
	_tRect = convert(rt);

	TVector2	vDrawSize;
	vDrawSize.x = _pSprite->_rtInit.w / 2.0f;
	vDrawSize.y = _pSprite->_rtInit.h / 2.0f;
	_rtCollision.Set(
		_vPos.x - vDrawSize.x,
		_vPos.y - vDrawSize.y,
		_pSprite->_rtInit.w,
		_pSprite->_rtInit.h);
	return true;
}