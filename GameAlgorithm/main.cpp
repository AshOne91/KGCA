#include "GameApp.h"
#include "Config.h"

int main()
{
	Config config;
	config._frame = 5;

	GameApp app;
	app.Create(config);
	app.Run();
}