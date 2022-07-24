#include <conio.h>
#include <string>
#include "SceneDelete.h"
#include "SceneMain.h"
#include "StudentManager.h"
#include "StudentManagedAppllication.h"
#include "ConsoleManager.h"

SceneDelete::SceneDelete()
{

}

SceneDelete::~SceneDelete()
{

}

void SceneDelete::Construct()
{

}

void SceneDelete::Destruct()
{

}

void SceneDelete::OnEnter()
{
	ConsoleManager::Instance()->Pause();
}

void SceneDelete::OnLeave()
{
	ConsoleManager::Instance()->Resume();
}

void SceneDelete::DoUpdate()
{
	std::cout << "삭제 할 학생의 고유번호를 입력해주세요." << std::endl;
	std::cout << "뒤로 돌아가시려면 esc를 눌러주세요." << std::endl;
	std::cout << "계속 진행 하시려면 아무키나 눌러주세요." << std::endl;
	std::string input;
	char ch = _getch();
	if (ch == 27)
	{
		StudentManagedApplication::Instance()->LoadScene<SceneMain>();
		return;
	}
	std::cout << "고유번호:";
	std::cin >> input;
	bool find = StudentManager::Instance()->DeleteStudnet(strtoll(input.c_str(), NULL, 0));
	if (find == true)
	{
		std::cout << "삭제되었습니다. 아무키나 눌러주세요." << std::endl;
	}
	else
	{
		std::cout << "삭제 실패 하였습니다. 아무키나 눌러주세요." << std::endl;
	}
	_getch();
	StudentManagedApplication::Instance()->LoadScene<SceneMain>();
	return;
}