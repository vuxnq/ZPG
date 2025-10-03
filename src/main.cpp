#include "Application.h"

int main() {
	Application* app = new Application();

	app->Init();
    app->SetUpCallbacks();
    app->OnCreate();
    app->Run();
    app->Shutdown();

	delete app;
}
