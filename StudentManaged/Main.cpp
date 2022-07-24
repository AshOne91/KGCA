#include <iostream>
#include <Windows.h>
#include "StudentManagedAppllication.h"
#include "StudentManager.h"

/*BOOL CtrlHandler(DWORD fdwCtrlType)
{
	switch (fdwCtrlType)
	{
	case CTRL_CLOSE_EVENT:
		StudentManagedApplication::Instance()->OnApplicationQuit();
		break;
	}
	return FALSE;
}*/

int main()
{
	//SetConsoleCtrlHandler((PHANDLER_ROUTINE)CtrlHandler, TRUE);
	StudentManagedApplication::Instance();
	StudentManagedApplication::Instance()->Construct();
	for (;;)
	{
		StudentManagedApplication::Instance()->Update();
	}
	StudentManagedApplication::Instance()->Destruct();
	StudentManagedApplication::Instance()->OnApplicationQuit();
}