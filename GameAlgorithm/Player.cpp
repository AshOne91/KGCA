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
	GameObject* missile = new Missile(GetApp(), GetFaction(), _box3d.min, _box3d.size);
	GetApp()->AddObject(missile);
}
