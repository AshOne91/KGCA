#pragma once


class GameObject;
class Player;
class Command
{
public:
	virtual ~Command() {}
	virtual void execute(GameObject* obj, float dt) = 0;
};

class MoveUnitCommand : public Command
{
public:
	MoveUnitCommand(float x, float y);
	virtual void execute(GameObject* obj, float dt);

private:
	float m_MoveX;
	float m_MoveY;
};

class SpaceCommand : public Command
{
public:
	float _fireDelay;
public:
	virtual void execute(GameObject* obj, float dt);
};

class InputHandler
{
public:
	virtual ~InputHandler();
	Command* handleInput();

private:
	Command* m_Up = new MoveUnitCommand(0, -1.0f);
	Command* m_Down = new MoveUnitCommand(0, 1.0f);
	Command* m_Left = new MoveUnitCommand(-1.0f, 0.0f);
	Command* m_Right = new MoveUnitCommand(1.0f, 0.0f);
	Command* m_Space = new SpaceCommand();
};