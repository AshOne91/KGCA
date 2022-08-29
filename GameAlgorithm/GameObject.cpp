#include "GameObject.h"

unsigned __int64 GameObject::GetFaction()
{
	return 0;
}

bool GameObject::CheckFaction(unsigned __int64 otherFaction)
{
	return false;
}

void GameObject::SetPosition(Vector3D position)
{
}

Vector3D GameObject::GetPosition()
{
	return Vector3D();
}

Vector3D GameObject::GetVelocity()
{
	return Vector3D();
}

float GameObject::GetMaxSpeed()
{
	return 0.0f;
}

Vector3D GameObject::GetHeading()
{
	return Vector3D();
}

enActive GameObject::GetActive()
{
	return enActive();
}

void GameObject::SetActive(enActive active)
{
}

enObjectType GameObject::GetType()
{
	return enObjectType();
}

unsigned __int64 GameObject::GetObjectIdx()
{
	return 0;
}
