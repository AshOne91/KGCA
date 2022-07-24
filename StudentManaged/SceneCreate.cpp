#include <conio.h>
#include "SceneCreate.h"
#include "ConsoleManager.h"
#include "StudentManager.h"
#include "Subject.h"
#include "StudentManagedAppllication.h"
#include "SceneMain.h"

SceneCreate::SceneCreate()
{

}

SceneCreate::~SceneCreate()
{

}

void SceneCreate::Construct()
{

}

void SceneCreate::Destruct()
{

}

void SceneCreate::OnEnter()
{
	ConsoleManager::Instance()->Pause();
}

void SceneCreate::OnLeave()
{
	ConsoleManager::Instance()->Resume();
}

Subject* SceneCreate::CreateSubject(ESubjectType type)
{

	short score = 0;
	switch (type)
	{
	case ESubjectType::Korean:
		std::cout << "����:";
		std::cin >> score;
		std::cout << std::endl;
		break;
	case ESubjectType::English:
		std::cout << "����:";
		std::cin >> score;
		std::cout << std::endl;
		break;
	case ESubjectType::Math:
		std::cout << "����:";
		std::cin >> score;
		std::cout << std::endl;
		break;
	default:
		std::cout << "Unknown:";
		std::cin >> score;
		std::cout << std::endl;
		break;
	}
	Subject* pSubject = new Subject();
	pSubject->SetType(type);
	pSubject->SetScore(score);
	return pSubject;
}

void SceneCreate::DoUpdate()
{
	std::string name;
	LinkedList<Subject*> listSubject;
	std::cout << "�л� ������ �Է��ϼ���\n";
	std::cout << "�̸�:";
	std::cin >> name;
	std::cout << std::endl;
	listSubject.push_back(CreateSubject(ESubjectType::Korean));
	listSubject.push_back(CreateSubject(ESubjectType::English));
	listSubject.push_back(CreateSubject(ESubjectType::Math));
	StudentManager::Instance()->CreateStudent(name, listSubject);
	std::cout << "�л� ������ �Ϸ� �Ǿ����ϴ�." << std::endl;
	std::cout << "�ƹ�Ű�� �����ּ���." << std::endl;
	_getch();
	StudentManagedApplication::Instance()->LoadScene<SceneMain>();
}