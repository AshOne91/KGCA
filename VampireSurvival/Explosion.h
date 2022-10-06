#pragma once
#include "Object2DComponent.h"
#include <unordered_map>

class Sound;
class Explosion : public Object2DComponent
{
private:
	static bool _bSoundInit;
	static std::vector<int> _blankIndexList;
	static Sound* pSound[2];
	int _allockSoundIndex = -1;

public:
	virtual void UpdateVertexBuffer() override;
	virtual bool Frame() override;
	virtual void SetPosition(const Vector2D& vPos, const Vector2D& vCamera) override;
	virtual bool Render() override;

public:
	virtual bool CInit() override;
	virtual bool CFrame() override;
	virtual bool CRender() override;
	virtual bool CRelease() override;
	virtual bool OnEvent(EventType eventType, ComponentObject* pSender, Message* msg) override;
};

