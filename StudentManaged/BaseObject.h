#pragma once
#include <string>

class BaseObject abstract
{
public:
	BaseObject() = default;
	virtual ~BaseObject() = default;

public:
	//Active 될대
	virtual void OnEnable();
	//DeActive 될 때
	virtual void OnDisable();

public:
	//생성자 이 후 호출 해야할 것들 정
	virtual void Construct();
	//파괴자 호출에서 해야할 것들 정의
	virtual void Destruct();

public:
	virtual bool OnMessage(BaseObject* sender, const std::string& message) = 0;
};
