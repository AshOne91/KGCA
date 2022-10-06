#pragma once
enum class EventType
{
	None = 0,
	CreateObject = 1,
	DestroyObject = 2,
	CreateComponent = 3,
	AddComponent = 4,
	ReleaseComponent = 5,
	CollisionIn = 6,
	CollisionOut = 7,
	ChangeScene = 8,
	CreateObjectInComponent = 9,
	DestroyObjectInComponent = 10,

	//유저영역(나중에는 분리)
	HpChange = 11
};

enum class NotifyType
{
	Mono = 0,
	BroadCast
};

enum class MapRotateType
{
	Up = 0,
	Right,
	Down,
	Left
};