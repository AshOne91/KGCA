#include <conio.h>
#include <string>
#include "SceneSort.h"
#include "SceneMain.h"
#include "StudentManager.h"
#include "StudentManagedAppllication.h"
#include "ConsoleManager.h"

SceneSort::SceneSort()
{

}
	
SceneSort::~SceneSort()
{

}

void SceneSort::Construct()
{

}

void SceneSort::Destruct()
{

}

void SceneSort::OnEnter()
{
	ConsoleManager::Instance()->Pause();
}

void SceneSort::OnLeave()
{
	ConsoleManager::Instance()->Resume();
}

void SceneSort::DoUpdate()
{
	int i;
	std::cout << "총점 1.오름차순 2.내림차순" << std::endl;
	std::cin >> i;
	LinkedList<unsigned __int64> orderNo;
	switch (i)
	{
	case 1:
		StudentManager::Instance()->SortStudent(true, orderNo);
		break;
	case 2:
		StudentManager::Instance()->SortStudent(false, orderNo);
		break;
	}
	std::cout << "no\t이름\t국어\t영어\t수학\t총점\t평균\n";
	for (auto iter = orderNo.begin(); iter != orderNo.end(); ++iter)
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