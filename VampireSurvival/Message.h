#pragma once
#include "enum.h"

class Message
{
public:
	unsigned __int64 _uiSender = 0;
	unsigned __int64 _uiReceiver = 0;
	EventType eventType = EventType::None;
	void* _pExtraInfo = nullptr;
};

class CreateTextMessage
{
public:
	std::string font = "°íµñ";
	int size = 0;
	unsigned __int64 uiIndex = 0;
};

class DrawTextMessage
{
public:
	unsigned __int64 uiIndex = 0;
	D2D1_COLOR_F color = {1, 1, 1, 1};
};