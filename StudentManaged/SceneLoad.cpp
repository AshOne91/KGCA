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
	std::cout << "���� �ε��Ͻ÷��� �ƹ�Ű�� �����ּ���" << std::endl;
	std::cout << "�������� ���� ������ �������ϴ�.!!" << std::endl;
	std::cout << "�ڷ� ���ư��÷��� esc�� �����ּ���.!!" << std::endl;
	char ch = _getch();
	if (ch == 27)
	{
		StudentManagedApplication::Instance()->LoadScene<SceneMain>();
		return;
	}
	StudentManager::Instance()->Clear();
	PacketAssist* packetAssist = StudentManager::Instance();
	packetAssist->Deserialize();
	std::cout << "������ �ٽ� �ε��Ͽ����ϴ�." << std::endl;
	std::cout << "�ƹ�Ű�� �����ּ���." << std::endl;
	_getch();
	StudentManagedApplication::Instance()->LoadScene<SceneMain>();
}