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
	~Array() 
	{
		std::cout << "Array";
	}
};

class Container : public Array
{
public:
	Array test = ( 30 );

public:
	~Container()
	{
		std::cout << "Container";
	}
};

int main()
{
	Container* pContainer = new Container();
	delete pContainer;
	return 0;

	/*Array* pTest = dynamic_cast<Array*>(pContainer);
	Container* pTestContainer = dynamic_cast<Container*>(pArray);
	if (pTestContainer == nullptr)
	{
		std::cout << "YES";
	}*/
	//std::cout << test.test.size << std::endl;
	
}