#include "Projectile2D.h"

bool Projectile2D::Update()
{
	_fEffectTimer += g_fSecondPerFrame;
	if (_fLifeTime <= _fEffectTimer)
	{
		return false;
	}
	if (_fStep <= _fEffectTimer)
	{
		_fEffectTimer -= _fStep;
		_iIndex++;
	}
	if (_iIndex >= _iMaxIndex)
	{
		_iIndex = 0;
	}
	RECT rt = _pSprite->_uvArray[_iIndex];
	_tRect = convert(rt);
	Vector2D vAdd = _vDir * _fSpeed * g_fSecondPerFrame;
	_vPos = _vPos + vAdd;

	Vector2D	vDrawSize;
	vDrawSize.x = _pSprite->_rtInit.w / 2.0f;
	vDrawSize.y = _pSprite->_rtInit.h / 2.0f;
	_rtCollision.Set(
		_vPos.x - vDrawSize.x,
		_vPos.y - vDrawSize.y,
		_pSprite->_rtInit.w,
		_pSprite->_rtInit.h);
	return true;
}
Projectile2D::Projectile2D()
{
	_fLifeTime = 3.33f;
	_fSpeed = 600.0f;
}
