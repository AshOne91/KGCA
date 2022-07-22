#include <iostream>
#include "StudentManagedAppllication.h"

class testSceneSubSystem : SceneSubSystem<testSceneSubSystem>
{
public:  
	void DoUpdate() {};

public:
	virtual bool OnMessage(BaseObject* sender, const std::string& message)
	{
		return false;
	}
};

int main()
{
	/*StudentManagedApplication::Instance()->Test = 1;
	std::cout << StudentManagedApplication::Instance()->Test << std::endl;*/
	testSceneSubSystem test;
}