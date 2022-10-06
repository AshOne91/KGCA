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
