#pragma once
#include "Object2D.h"
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

class Interface : public Object2D
{
public:
	UIState _currentState;
	std::vector<Texture*> _pStateList;
	Texture* _pCurrentTex = nullptr;

public:
	virtual void AddChild(Interface* pUI) {};
	virtual bool SetTextureState(const std::vector<W_STR>& texStateList);
	virtual bool SetAttribute(const Vector2D vPos, const Rect& rt, const std::vector<W_STR>& texStateList = {});
	virtual bool SetAttribute(const Vector2D vPos, const std::vector<W_STR>& texStateList = std::vector<W_STR>());
	virtual bool SetDrawList(
		float fScaleX0, float fScaleX1,
		float fScaleY0, float fScaleY1,
		float fScaleU0, float fScaleU1,
		float fScaleV0, float fScaleV1) {
		return true;
	}

public:
	Interface()
	{
		_currentState = UIState::UI_NORMAL;
		_pStateList.resize((int)UIState::UI_MAXSTATE);
	}
};

class Button : public Interface
{
public:
	virtual bool Init() override;
	virtual bool Frame() override;
	virtual bool Render() override;
	virtual bool Release() override;
};

class ListControl : public Interface
{
public:
	std::vector<Interface*> _pChildList;

public:
	virtual bool Init() override;
	virtual bool Frame() override;
	virtual bool Render() override;
	virtual bool Release() override;
	virtual void SetRect(const Rect& rt) override;
	virtual void AddChild(Interface* pUI)
	{
		_pChildList.push_back(pUI);
	}
};

class Dialog : public Interface
{
public:
	std::vector<Interface*> _rtDrawList;
	std::vector<Interface*> _pChildList;
	virtual void AddChild(Interface* pUI)
	{
		_pChildList.push_back(pUI);
	}

public:
	virtual bool Frame() override;
	virtual bool Render() override;
	virtual bool Release() override;
	virtual void SetRect(const Rect& rt) override;
	virtual bool SetDrawList(
		float fScaleX0, float fScaleX1,
		float fScaleY0, float fScaleY1,
		float fScaleU0, float fScaleU1,
		float fScaleV0, float fScaleV1);

};

