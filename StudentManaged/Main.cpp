#include <iostream>
#include "StudentManagedAppllication.h"

class testSceneSubSystem : SceneSubSystem<testSceneSubSystem>
{
public:  
	void DoUpdate() {};
};

int main()
{
	/*StudentManagedApplication::Instance()->Test = 1;
	std::cout << StudentManagedApplication::Instance()->Test << std::endl;*/
	testSceneSubSystem test;
}