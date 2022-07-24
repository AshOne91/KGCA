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
	std::cout << "���� �� �л��� ������ȣ�� �Է����ּ���." << std::endl;
	std::cout << "�ڷ� ���ư��÷��� esc�� �����ּ���." << std::endl;
	std::cout << "��� ���� �Ͻ÷��� �ƹ�Ű�� �����ּ���." << std::endl;
	std::string input;
	char ch = _getch();
	if (ch == 27)
	{
		StudentManagedApplication::Instance()->LoadScene<SceneMain>();
		return;
	}
	std::cout << "������ȣ:";
	std::cin >> input;
	bool find = StudentManager::Instance()->DeleteStudnet(strtoll(input.c_str(), NULL, 0));
	if (find == true)
	{
		std::cout << "�����Ǿ����ϴ�. �ƹ�Ű�� �����ּ���." << std::endl;
	}
	else
	{
		std::cout << "���� ���� �Ͽ����ϴ�. �ƹ�Ű�� �����ּ���." << std::endl;
	}
	_getch();
	StudentManagedApplication::Instance()->LoadScene<SceneMain>();
	return;
}