#include <conio.h>
#include "SceneLoad.h"
#include "SceneMain.h"
#include "StudentManager.h"
#include "StudentManagedAppllication.h"
#include "ConsoleManager.h"
#include "PacketAssist.h"

SceneLoad::SceneLoad()
{

}

SceneLoad::~SceneLoad()
{

}

void SceneLoad::Construct()
{

}

void SceneLoad::Destruct()
{

}

void SceneLoad::OnEnter()
{
	ConsoleManager::Instance()->Pause();
}

void SceneLoad::OnLeave()
{
	ConsoleManager::Instance()->Resume();
}

void SceneLoad::DoUpdate()
{
	std::cout << "파일 로드하시려면 아무키나 눌러주세요" << std::endl;
	std::cout << "저장하지 않은 사항은 지워집니다.!!" << std::endl;
	std::cout << "뒤로 돌아가시려면 esc를 눌러주세요.!!" << std::endl;
	char ch = _getch();
	if (ch == 27)
	{
		StudentManagedApplication::Instance()->LoadScene<SceneMain>();
		return;
	}
	StudentManager::Instance()->Clear();
	PacketAssist* packetAssist = StudentManager::Instance();
	packetAssist->Deserialize();
	std::cout << "파일을 다시 로드하였습니다." << std::endl;
	std::cout << "아무키나 눌러주세요." << std::endl;
	_getch();
	StudentManagedApplication::Instance()->LoadScene<SceneMain>();
}