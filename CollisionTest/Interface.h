#pragma once
#include "Object2D.h"

enum class UIState
{
	UI_NORMAL = 0,
	UI_HOVER,
	UI_PUSH,
	UI_DIS,
	UI_SELECT
};

class Interface : public Object2D
{
public:
	UIState _currentState;
	std::vector<Texture*> _pStateList;
	Texture* _pCurrentTex = nullptr;

public:
	virtual void Rotation();
};

class Button : public Interface
{
public:
	virtual bool Init() override;
	virtual bool Frame() override;
	virtual bool Render() override;
	virtual bool Release() override;

public:
	Button()
	{
		_currentState = UIState::UI_NORMAL;
	}
};

class ListControl : public Button
{
public:
	std::vector<Button*> _btnList;

public:
	virtual bool Init() override;
	virtual bool Frame() override;
	virtual bool Render() override;
	virtual bool Release() override;

	virtual void UpdateVertexBuffer() override;
	virtual void SetRect(const Rect& rt) override;
	virtual void ScreenToNDC() override;
};

class Dialog : public Interface
{
public:
	std::vector<ListControl*> _listctlList;
	std::vector<Button*> _btnList;
};

