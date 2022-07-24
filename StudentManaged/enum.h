#pragma once
#include <iostream>
enum class ESubjectType : int
{
	None = 0,
	Korean = 1,
	English = 2,
	Math = 3,
	MAX = INT_MAX
};

enum class EStudentManaged : int
{
	None = 0,
	Create = 1,
	Delete = 2,
	Sort = 3,
	Find = 4,
	MAX = INT_MAX
};
