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
		std::cout << "국어:";
		std::cin >> score;
		std::cout << std::endl;
		break;
	case ESubjectType::English:
		std::cout << "영어:";
		std::cin >> score;
		std::cout << std::endl;
		break;
	case ESubjectType::Math:
		std::cout << "수학:";
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
	std::cout << "학생 정보를 입력하세요\n";
	std::cout << "이름:";
	std::cin >> name;
	std::cout << std::endl;
	listSubject.push_back(CreateSubject(ESubjectType::Korean));
	listSubject.push_back(CreateSubject(ESubjectType::English));
	listSubject.push_back(CreateSubject(ESubjectType::Math));
	StudentManager::Instance()->CreateStudent(name, listSubject);
	std::cout << "학생 생성이 완료 되었습니다." << std::endl;
	std::cout << "아무키나 눌러주세요." << std::endl;
	_getch();
	StudentManagedApplication::Instance()->LoadScene<SceneMain>();
}