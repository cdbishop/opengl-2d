#include <Windows.h>
#include <stdexcept>
#include <iostream>
#include <System/Application.hpp>

#include <scenes/mainScene.hpp>

int main(int argc, char** argv) {
  std::shared_ptr<Application> app = Application::Create(1280, 720);
  app->RegisterScene("gameScene", std::move(std::make_unique<MainScene>()));

	try {
		app->SetScene("gameScene");
		app->Run();
	}
	catch (const std::exception& e) {
		std::cerr << "Failed to run application: " << e.what() << std::endl;
  		return -1;
	}

	return 0;
}
