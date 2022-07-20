#include <iostream>
#include "LinkedList.h"
#include "Singleton.h"

class TestManager : public Singleton<TestManager>
{
public:
	int main = 0;
};

int main()
{
	LinkedList<int> test;
	test.push_back(1);
	test.push_back(2);
	test.push_back(3);
	test.push_back(4);
	test.push_back(5);
	test.push_back(6);
	test.push_back(7);
	test.push_back(8);
	test.push_back(9);
	test.push_back(10);
	for (Iterator<int> iter = test.begin(); iter != test.end(); ++iter)
	{
		std::cout << *iter << std::endl;
	}

	auto findIter = test.find(5);
	if (test.end() != findIter)
	{
		auto nextIter = test.erase(findIter);
		std::cout << *nextIter << std::endl;
	}

	for (auto iter = test.begin(); iter != test.end(); ++iter)
	{
		std::cout << *iter << std::endl;
	}

	test.clear();
	std::cout << test.size() << std::endl;
	for (auto iter = test.begin(); iter != test.end(); ++iter)
	{
		std::cout << *iter << std::endl;
	}


	TestManager::Instance()->main = 1;
	std::cout << TestManager::Instance()->main << std::endl;
}