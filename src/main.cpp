#include <Windows.h>
#include <stdexcept>
#include <iostream>
#include <System/Application.hpp>

#include <scenes/TexturedQuadScene.hpp>

int main(int argc, char** argv) {
	Application app(1280, 720);
  app.RegisterScene("gameScene", std::move(std::make_unique<TexturedQuadScene>()));

	try {
		app.SetScene("gameScene");
		app.Run();
	}
	catch (const std::exception& e) {
		std::cerr << "Failed to run application: " << e.what() << std::endl;
  		return -1;
	}

	return 0;
}
