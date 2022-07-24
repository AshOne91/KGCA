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
	_entryLogo += "====   성적 관리 프로그램      ====\n";
	_entryLogo += "===================================\n";
	_entryLogo += "       Create By 권성호\n";
	_entryLogo += "       2022년 07월 25일\n";
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