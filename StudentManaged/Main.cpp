#include <iostream>
#include <filesystem>
#include "StudentManager.h"
#include "StudentManagedAppllication.h"
#include "Subject.h"

/*class testSceneSubSystem : SceneSubSystem<testSceneSubSystem>
{
public:  
	void DoUpdate() {};

public:
	virtual bool OnMessage(BaseObject* sender, const std::string& message)
	{
		return false;
	}
};*/

int main()
{
	std::string aa = std::filesystem::current_path().string();
	aa += "\\Record.bin";
	std::cout << aa;

	StudentManager::Instance();
	StudentManager::Instance()->Construct();
	Subject* pSubject = new Subject();
	pSubject->SetScore(100);
	pSubject->SetType(ESubjectType::Korean);
	Subject* pESubject = new Subject();
	pESubject->SetScore(50);
	pESubject->SetType(ESubjectType::English);
	LinkedList<Subject*> list;
	list.push_back(pSubject);
	list.push_back(pESubject);
	StudentManager::Instance()->CreateStudent("ksh", list);
	StudentManager::Instance()->Destruct();
	/*StudentManagedApplication::Instance()->Test = 1;
	std::cout << StudentManagedApplication::Instance()->Test << std::endl;*/
	//testSceneSubSystem test;
}