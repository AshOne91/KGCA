#pragma once
#include "Object2DComponent.h"

class Hit : public Object2DComponent
{
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

