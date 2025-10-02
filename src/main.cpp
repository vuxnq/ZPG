#include "Application.h"

int main() {
	Application* app = new Application();

	app->Init();
    app->SetUpCallbacks();
    app->CreateModels();
    app->Run();
    app->Shutdown();

	delete app;
}
