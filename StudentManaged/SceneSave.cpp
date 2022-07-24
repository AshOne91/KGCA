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
	std::cout << "���Ϸ� �����Ͻ÷��� �ƹ�Ű�� �����ּ���" << std::endl;
	_getch();
	PacketAssist* packetAssist = StudentManager::Instance();
	packetAssist->Serialize();
	std::cout << "���� �Ǿ����ϴ�." << std::endl;
	std::cout << "�ƹ�Ű�� �����ּ���." << std::endl;
	_getch();
	StudentManagedApplication::Instance()->LoadScene<SceneMain>();
}