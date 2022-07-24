#include <conio.h>
#include "SceneSave.h"
#include "SceneMain.h"
#include "ConsoleManager.h"
#include "StudentManager.h"
#include "PacketAssist.h"
#include "StudentManagedAppllication.h"

SceneSave::SceneSave()
{

}

SceneSave::~SceneSave()
{

}

void SceneSave::Construct()
{

}

void SceneSave::Destruct()
{

}

void SceneSave::OnEnter()
{
	ConsoleManager::Instance()->Pause();
}

void SceneSave::OnLeave()
{
	ConsoleManager::Instance()->Resume();
}

void SceneSave::DoUpdate()
{
	std::cout << "파일로 저장하시려면 아무키나 눌러주세요" << std::endl;
	_getch();
	PacketAssist* packetAssist = StudentManager::Instance();
	packetAssist->Serialize();
	std::cout << "저장 되었습니다." << std::endl;
	std::cout << "아무키나 눌러주세요." << std::endl;
	_getch();
	StudentManagedApplication::Instance()->LoadScene<SceneMain>();
}