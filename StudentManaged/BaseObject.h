#pragma once

class BaseObject abstract
{
public:
	void Awake();
	void OnDestroy();

public:
	BaseObject() = default;
	virtual ~BaseObject() = default;

protected:
	virtual void Construct() = 0;
	virtual void Destruct() = 0;
};
