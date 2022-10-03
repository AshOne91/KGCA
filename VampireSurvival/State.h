#pragma once
class State
{
public:
	virtual void Enter() = 0;
	virtual void Execute() = 0;
	virtual void Exit() = 0;

public:
	State() = default;
	virtual ~State() = default;
};

