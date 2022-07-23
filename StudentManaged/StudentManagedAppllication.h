#pragma once
#include "Application.h"
#include "PacketAssist.h"

class StudentManagedApplication : public Application<StudentManagedApplication>
{
public:
	StudentManagedApplication();
	virtual ~StudentManagedApplication();

protected:
	virtual void OnInit();
	virtual void OnDeinit();
	virtual void DoUpdate();
};