#include <iostream>
#include <array>
#include <vector>
#include <string>
#include <map>

template<typename component>
int test(component* test)
{
	std::cout << typeid(component*).hash_code() << std::endl;
}


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
		/*int* intPtr = new int[10];
		int ptrSize = _msize(intPtr) / sizeof(int);
		std::cout <<"arraySize:" << ptrSize << std::endl;*/
		
		this->size = size;
		std::cout << typeid(*this).hash_code() << std::endl;
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
	Container()
	{
		std::cout << typeid(*this).hash_code() << std::endl;
	}
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

	/*std::string test = {"Å×½ºÆ®"};
	std::cout << test.size() << std::endl;
	std::cout << test.length() << std::endl;

	std::map<std::string, int> te;
	te["È«±æµ¿"] = 1;
	te["°¨ÀÚÈ«"] = 2;
	te["È«±æµ¿"] = 3;

	te.emplace( "È«±æµ¿", 4 );
	return 0;*/

	/*Array* pTest = dynamic_cast<Array*>(pContainer);
	Container* pTestContainer = dynamic_cast<Container*>(pArray);
	if (pTestContainer == nullptr)
	{
		std::cout << "YES";
	}*/
	//std::cout << test.test.size << std::endl;
	
}