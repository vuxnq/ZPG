#include "Application.h"

int main()
{
	Application* app = new Application();

	app->Init();
    app->SetUpCallbacks();
    app->TyVeci();
    app->Run();
    app->Shutdown();

	delete app;
}
