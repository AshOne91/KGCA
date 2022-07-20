#include <iostream>
#include <array>
#include <vector>

class Array
{
public:
	int size;
public:
	Array()
	{

	}
	Array(int size)
	{
		this->size = size;
	}
};

class Container
{
public:
	Array test = ( 30 );
};

int main()
{
	Container test;
	std::cout << test.test.size << std::endl;
	
}