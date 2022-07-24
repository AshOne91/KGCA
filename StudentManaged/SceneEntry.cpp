#include <conio.h>
#include "SceneEntry.h"
#include "ConsoleManager.h"
#include "StudentManagedAppllication.h"
#include "SceneMain.h"

SceneEntry::SceneEntry()
{

}

SceneEntry::~SceneEntry()
{

}

void SceneEntry::Construct()
{
	SceneController::Construct();
}

void SceneEntry::Destruct()
{
	SceneController::Destruct();
}

void SceneEntry::OnEnter()
{
	_entryLogo += "===================================\n";
	_entryLogo += "====   ���� ���� ���α׷�      ====\n";
	_entryLogo += "===================================\n";
	_entryLogo += "       Create By �Ǽ�ȣ\n";
	_entryLogo += "       2022�� 07�� 25��\n";
	_entryLogo += "        PressAnyKey\n";

}

void SceneEntry::OnLeave()
{
	_entryLogo.clear();
	ConsoleManager::Instance()->ConsoleClear();
}

void SceneEntry::DoUpdate()
{
	ConsoleManager::Instance()->SetBuffer(_entryLogo);
	if (_kbhit())
	{
		StudentManagedApplication::Instance()->LoadScene<SceneMain>();
	}
}