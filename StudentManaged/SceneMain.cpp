#include <conio.h>
#include "SceneMain.h"
#include "SceneCreate.h"
#include "SceneSave.h"
#include "SceneLoad.h"
#include "SceneDelete.h"
#include "SceneSort.h"
#include "SceneFind.h"
#include "StudentManager.h"
#include "Subject.h"
#include "ConsoleManager.h"
#include "StudentManagedAppllication.h"

SceneMain::SceneMain()
{

}

SceneMain::~SceneMain()
{

}

void SceneMain::Construct()
{
	SceneController::Construct();
}

void SceneMain::Destruct()
{
	SceneController::Destruct();
}

std::string& SceneMain::DrawMain()
{
	_main.clear();
	_main += "===================================\n";
	_main += "====   성적 관리 프로그램      ====\n";
	_main += "===================================\n";
	LinkedList<unsigned __int64> indexList;
	StudentManager::Instance()->GetIndexList(indexList);
	if (indexList.size() <= 0)
	{
		_main += "      no data          \n";
	}
	else
	{
		_main += "no\t이름\t국어\t영어\t수학\t총점\t평균\n";
		for (auto iter = indexList.begin(); iter != indexList.end(); ++iter)
		{
			_main += std::to_string(*iter);
			_main += "\t";
			_main += StudentManager::Instance()->GetName((*iter));
			_main += "\t";
			_main += std::to_string(StudentManager::Instance()->GetSubjectScore((*iter), ESubjectType::Korean));
			_main += "\t";
			_main += std::to_string(StudentManager::Instance()->GetSubjectScore((*iter), ESubjectType::English));
			_main += "\t";
			_main += std::to_string(StudentManager::Instance()->GetSubjectScore((*iter), ESubjectType::Math));
			_main += "\t";
			LinkedList<ESubjectType> subjectTypes;
			subjectTypes.push_back(ESubjectType::Korean);
			subjectTypes.push_back(ESubjectType::English);
			subjectTypes.push_back(ESubjectType::Math);
			_main += std::to_string(StudentManager::Instance()->GetTotalScore((*iter), subjectTypes));
			_main += "\t";
			_main += std::to_string(StudentManager::Instance()->GetAverage((*iter), subjectTypes));
			_main += "\n";
		}
	}
	_main += "1.생성 2.저장 3.로드 4.삭제 5.정렬 6.검색 9.DummyCreate\n";
	return _main;
}

void SceneMain::OnEnter()
{
	ConsoleManager::Instance()->ConsoleClear();
}

void SceneMain::OnLeave()
{
	ConsoleManager::Instance()->ConsoleClear();
}

void SceneMain::DoUpdate()
{
	ConsoleManager::Instance()->SetBuffer(DrawMain());
	int key;
	if (_kbhit())
	{
		key = _getch();
		switch (key)
		{
			case 49:
				StudentManagedApplication::Instance()->LoadScene<SceneCreate>();
				break;
			case 50:
				StudentManagedApplication::Instance()->LoadScene<SceneSave>();
				break;
			case 51:
				StudentManagedApplication::Instance()->LoadScene<SceneLoad>();
				break;
			case 52:
				StudentManagedApplication::Instance()->LoadScene<SceneDelete>();
				break;
			case 53:
				StudentManagedApplication::Instance()->LoadScene<SceneSort>();
				break;
			case 54:
				StudentManagedApplication::Instance()->LoadScene<SceneFind>();
				break;
			case 57:
				ConsoleManager::Instance()->ConsoleClear();
				StudentManager::Instance()->CreateDummy();
				break;
		}
	}
}