#include <iostream>
#include <array>
#include <vector>
#include <string>
#include <map>

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
	/*Container* pContainer = new Container();
	delete pContainer;
	return 0;*/

	std::string test = { "�׽�Ʈ" };
	std::cout << test.size() << std::endl;
	std::cout << test.length() << std::endl;

	std::map<std::string, int> te;
	te["ȫ�浿"] = 1;
	te["����ȫ"] = 2;
	te["ȫ�浿"] = 3;

	te.emplace( "ȫ�浿", 4 );
	return 0;

	/*Array* pTest = dynamic_cast<Array*>(pContainer);
	Container* pTestContainer = dynamic_cast<Container*>(pArray);
	if (pTestContainer == nullptr)
	{
		std::cout << "YES";
	}*/
	//std::cout << test.test.size << std::endl;
	
}