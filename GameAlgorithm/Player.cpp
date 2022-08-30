#include "Player.h"
#include "Missile.h"
#include "GameApp.h"

Player::Player(GameApp* app, Vector3D pos, Vector3D size)
	: GameObject(app, enObjectType::Player, (unsigned __int64)enFaction::Player, pos, size)
{
}

Player::~Player()
{
}

void Player::Update(float dt)
{
}

void Player::FireMissile()
{
	Box3D box(_box3d);
	box.min.y += -1.0f;
	GameObject* missile = new Missile(GetApp(), GetFaction(), box.min, box.size);
	GetApp()->AddObject(missile);
}
