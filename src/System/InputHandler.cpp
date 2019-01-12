#include "InputHandler.hpp"
#include "Application.hpp"
#include <GLFW/glfw3.h>

InputHandler::InputHandler(std::shared_ptr<Application> app)
  :_application(app)
{
}

InputHandler::~InputHandler()
{
}

void InputHandler::RegisterKey(int key, Callback cb)
{
  _callbacks[key].push_back(cb);
}

void InputHandler::Update()
{
  for (auto& handler : _callbacks) {
    if (glfwGetKey(_application->GetWindow(), handler.first) == GLFW_PRESS) {
      for (auto& cb : handler.second) {
        cb();
      }
    }
  }
}
