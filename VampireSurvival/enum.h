#pragma once
enum class EventType
{
	None = 0,
	CreateObject = 1,
	DestroyObject = 2
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