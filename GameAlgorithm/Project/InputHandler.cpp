#include "InputHandler.h"
#include "GameObject.h"
#include "Player.h"
#include <Windows.h>

#define dfSCREEN_WIDTH 50
#define dfSCREEN_HEIGHT 50

MoveUnitCommand::MoveUnitCommand(float x, float y)
{
	m_MoveX = x;
	m_MoveY = y;
}

void MoveUnitCommand::execute(GameObject* obj, float dt)
{
	float posX = obj->GetPosition().x + (float)(m_MoveX * dt * 5.0f);
	float posY = obj->GetPosition().y + (float)(m_MoveY * dt * 5.0f);
	float posZ = obj->GetPosition().z;
	if (posY < 0)
		return;
	if (posY >= dfSCREEN_HEIGHT)
		return;
	if (posX < 0)
		return;
	if (posX > dfSCREEN_WIDTH)
		return;
	obj->SetPosition({ posX, posY, posZ });
}

void SpaceCommand::execute(GameObject* obj, float dt)
{
	Player* player = dynamic_cast<Player*>(obj);
	if (player != nullptr)
	{
		player->FireMissile();
	}
}

InputHandler::~InputHandler()
{
	delete m_Up;
	delete m_Down;
	delete m_Left;
	delete m_Right;
	delete m_Space;
}

Command* InputHandler::handleInput()
{
	if (GetAsyncKeyState(VK_UP))
	{
		return m_Up;
	}

	if (GetAsyncKeyState(VK_DOWN))
	{
		return m_Down;
	}

	if (GetAsyncKeyState(VK_LEFT))
	{
		return m_Left;
	}

	if (GetAsyncKeyState(VK_RIGHT))
	{
		return m_Right;
	}

	if ((GetAsyncKeyState(VK_SPACE) & 0x8000))
	{
		return m_Space;
	}
	return nullptr;
}

