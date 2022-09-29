#pragma once
#include "SpriteManager.h"
#include "SoundManager.h"
//https://www.vectorstock.com/

enum class UIState
{
	UI_NORMAL = 0,
	UI_HOVER,
	UI_PUSH,
	UI_DIS,
	UI_SELECT,
	UI_MAXSTATE
};
struct UIEvent
{
	std::vector<Texture*> _pStateList;
	std::vector<Sound*> _pSoundStateList;
	Sprite* _pSprite;
	Sprite* _pEffect;
	UIEvent()
	{
		_pStateList.resize((int)UIState::UI_MAXSTATE);
		_pSprite = nullptr;
		_pEffect = nullptr;
	}
};
class Interface : public Object2D
{
public:
	UIState _currentState;
	UIEvent _eventState;
	Texture* _pCurrentTex = nullptr;
	Sprite* _pSprite = nullptr;

public:
	std::vector<Interface*> _rtDrawList;
	std::vector<Interface*> _pChildList;

public:
	virtual bool Frame() override;

public:
	virtual void FadeInOut(float fAlpha);
	virtual void SetEvent(UIEvent& event)
	{
		_eventState = event;
	}
	virtual void AddChild(Interface* pUI);
	virtual bool SetTextureState(const std::vector<W_STR>& texStateList);
	virtual bool SetAttribute(const Vector2D& vPos, const Rect& rt, const std::vector<W_STR>& texStateList = {});
	virtual bool SetAttribute(const Vector2D& vPos, const Rect& rt, Sprite* pSprite);
	virtual bool SetAttribute(const Vector2D& vPos, const std::vector<W_STR>& texStateList = std::vector<W_STR>());
	virtual bool SetDrawList(
		float fScaleX0, float fScaleX1,
		float fScaleY0, float fScaleY1,
		float fScaleU0, float fScaleU1,
		float fScaleV0, float fScaleV1);

public:
	Interface()
	{
		_currentState = UIState::UI_NORMAL;
	}
};

class Button : public Interface
{
public:
	virtual bool Init() override;
	virtual bool Frame() override;
	virtual bool Render() override;
	virtual bool Release() override;
	virtual void SetRect(const Rect& rt) override;
};

class ListControl : public Interface
{
public:
	virtual bool Init() override;
	virtual bool Frame() override;
	virtual bool Render() override;
	virtual bool Release() override;
	virtual void SetRect(const Rect& rt) override;
};

class Dialog : public Interface
{
public:
	virtual bool Init() override;
	virtual bool Frame() override;
	virtual bool Render() override;
	virtual bool Release() override;
};

