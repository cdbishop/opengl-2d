#pragma once
#include <memory>

#include "InputHandler.hpp"

class Application;

class Scene
{
public:
	Scene() {}

	void SetApp(std::shared_ptr<Application> app) {
		_app = app;
    _inputHandler = std::make_shared<InputHandler>(_app);
	}	
	
	virtual ~Scene() { }

	virtual void Init() { }

	virtual void Update() { }

	virtual void Render() { }

protected:
  std::shared_ptr<Application> GetApplication() {
		return _app;
	}

  std::shared_ptr<InputHandler> GetInputHandler() {
    return _inputHandler;
  }

private:
  std::shared_ptr<Application> _app;
  std::shared_ptr<InputHandler> _inputHandler;
};
