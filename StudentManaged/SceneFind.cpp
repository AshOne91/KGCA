#include <conio.h>
#include <string>
#include "SceneFind.h"
#include "SceneMain.h"
#include "StudentManager.h"
#include "StudentManagedAppllication.h"
#include "ConsoleManager.h"

SceneFind::SceneFind()
{

}

SceneFind::~SceneFind()
{

}

void SceneFind::Construct()
{

}

void SceneFind::Destruct()
{

}

void SceneFind::OnEnter()
{
	ConsoleManager::Instance()->Pause();
}

void SceneFind::OnLeave()
{
	ConsoleManager::Instance()->Resume();
}

void SceneFind::DoUpdate()
{
	std::string name;
	std::cout << "검색 할 학생 이름을 적어주세요." << std::endl;
	std::cin >> name;
	LinkedList<unsigned __int64> linkedList;
	StudentManager::Instance()->FindStudnet(name, linkedList);
	if (linkedList.size() < 0)
	{
		std::cout << "no data!!" << std::endl;
		std::cout << "press any key" << std::endl;
		_getch();
		StudentManagedApplication::Instance()->LoadScene<SceneMain>();
		return;
	}
	std::cout << "no\t이름\t국어\t영어\t수학\t총점\t평균\n";
	for (auto iter = linkedList.begin(); iter != linkedList.end(); ++iter)
	{
		std::cout << std::to_string(*iter);
		std::cout << "\t";
		std::cout << StudentManager::Instance()->GetName((*iter));
		std::cout << "\t";
		std::cout << std::to_string(StudentManager::Instance()->GetSubjectScore((*iter), ESubjectType::Korean));
		std::cout << "\t";
		std::cout << std::to_string(StudentManager::Instance()->GetSubjectScore((*iter), ESubjectType::English));
		std::cout << "\t";
		std::cout << std::to_string(StudentManager::Instance()->GetSubjectScore((*iter), ESubjectType::Math));
		std::cout << "\t";
		LinkedList<ESubjectType> subjectTypes;
		subjectTypes.push_back(ESubjectType::Korean);
		subjectTypes.push_back(ESubjectType::English);
		subjectTypes.push_back(ESubjectType::Math);
		std::cout << std::to_string(StudentManager::Instance()->GetTotalScore((*iter), subjectTypes));
		std::cout << "\t";
		std::cout << std::to_string(StudentManager::Instance()->GetAverage((*iter), subjectTypes));
		std::cout << "\n";
	}
	std::cout << "press any key" << std::endl;
	_getch();
	StudentManagedApplication::Instance()->LoadScene<SceneMain>();
}