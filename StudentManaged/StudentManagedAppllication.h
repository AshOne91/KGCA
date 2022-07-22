#pragma once
#include "Application.h"

class StudentManagedApplication : public Application<StudentManagedApplication>
{
public:
	int Test;
public:
	StudentManagedApplication();
	virtual ~StudentManagedApplication();
};