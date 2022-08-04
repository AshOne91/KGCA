#include "StudentManagedAppllication.h"
#include "StudentManager.h"
#include "ConsoleManager.h"
#include "SceneEntry.h"
#include "SceneMain.h"
#include "SceneCreate.h"
#include "SceneSave.h"
#include "SceneLoad.h"
#include "SceneDelete.h"
#include "SceneSort.h"
#include "SceneFind.h"

StudentManagedApplication::StudentManagedApplication() :Application("StudentManagedApp")
{

}

StudentManagedApplication::~StudentManagedApplication()
{

}

void StudentManagedApplication::OnInit()
{
	CreateAppSubSystem<StudentManager>();
	CreateAppSubSystem<ConsoleManager>();
	StudentManager::Instance()->Construct();
	ConsoleManager::Instance()->Construct();
	std::string appMessage = "OnSetParentName:";
	appMessage += GetApplicationName();
	OnMessage(this, appMessage);

	CreateScene<SceneEntry>();
	CreateScene<SceneMain>();
	CreateScene<SceneCreate>();
	CreateScene<SceneDelete>();
	CreateScene<SceneSave>();
	CreateScene<SceneLoad>();
	CreateScene<SceneSort>();
	CreateScene<SceneFind>();
	SceneEntry::Instance()->Construct();
	SceneMain::Instance()->Construct();
	SceneCreate::Instance()->Construct();
	SceneDelete::Instance()->Construct();
	SceneSave::Instance()->Construct();
	SceneLoad::Instance()->Construct();
	SceneSort::Instance()->Construct();
	SceneFind::Instance()->Construct();
	std::string sceneMessage = "OnSetApplicationName:";
	sceneMessage += GetApplicationName();
	OnMessage(this, sceneMessage);
	LoadScene<SceneEntry>();
}

void StudentManagedApplication::OnDeinit()
{
	ConsoleManager::Instance()->Destruct();
	StudentManager::Instance()->Destruct();
}

void StudentManagedApplication::DoUpdate()
{

}