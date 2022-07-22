#pragma once
#include "Application.h"

class StudentManagedApplication : public Application<StudentManagedApplication>
{
public:
	StudentManagedApplication();
	virtual ~StudentManagedApplication();
};