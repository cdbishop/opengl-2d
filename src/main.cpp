#include <Windows.h>
#include <stdexcept>
#include <iostream>
#include <System/Application.hpp>

#include <scenes/mainScene.hpp>
#include <scenes/menuScene.hpp>
#include <scenes/gameOverScene.hpp>

int main(int argc, char** argv) {
  std::shared_ptr<Application> app = Application::Create(1280, 720);
  app->RegisterScene(MenuScene::Name, std::make_shared<MenuScene>());
  app->RegisterScene(MainScene::Name, std::make_shared<MainScene>());
  app->RegisterScene(GameOverScene::Name, std::make_shared<GameOverScene>());

	try {
		app->SetScene(MenuScene::Name);
		app->Run();
	}
	catch (const std::exception& e) {
		std::cerr << "Failed to run application: " << e.what() << std::endl;
  		return -1;
	}

	return 0;
}
