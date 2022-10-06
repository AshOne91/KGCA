#pragma once
#include "Object2DComponent.h"
#include <vector>

class Sound;
class DeadMonster : public Object2DComponent
{
private:
	static bool _bSoundInit;
	static std::vector<int> _blankIndexList;
	static Sound* pSound[5];
	int _allockSoundIndex = -1;

public:
	virtual void UpdateVertexBuffer() override;
	virtual bool Frame() override;
	virtual void SetPosition(const Vector2D& vPos, const Vector2D& vCamera) override;
	virtual bool Render() override;
	virtual bool EffectUpdate() override;

public:
	virtual bool CInit() override;
	virtual bool CFrame() override;
	virtual bool CRender() override;
	virtual bool CRelease() override;
	virtual bool OnEvent(EventType eventType, ComponentObject* pSender, Message* msg) override;
};

