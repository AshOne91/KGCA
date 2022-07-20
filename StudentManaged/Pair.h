#pragma once

template <typename T1, typename T2>
class Pair
{
public:
	T1 _first;
	T2 _second;

public:
	Pair();
	Pair(T1 first, T2 second);
};

#include "Pair.hpp"
