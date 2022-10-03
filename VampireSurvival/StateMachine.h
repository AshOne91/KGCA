#pragma once
#include "Component.h"
#include "State.h"

template <typename T>
class StateMachine
{
private:
	State* _pCurrentState = nullptr;
	State* _pPreviousState = nullptr;

public:
	StateMachine() = default;
	virtual ~StateMachine() = default;
	void SetCurrentState(State* pCurrentSate) { _pCurrentState = pCurrentSate; }
	void SetPreviousState(State* pPreviousState) { _pPreviousState = pPreviousState; }
	void ChangeState(State* pNewState)
	{
		_pPreviousState = _pCurrentState;

		_pCurrentState->Exit();

		_pCurrentState = pNewState;

		_pCurrentState->Enter();
	}
	State* CurrentState() const { return _pCurrentState; }
	State* PreviousState() const { return _pPreviousState; }

	bool isInState(const State& st) const
	{
		return (&st == _pCurrentState);
	}


public:
	bool Excute()
	{
		if (_pCurrentState) _pCurrentState->Execute();
		return true;
	};
};

