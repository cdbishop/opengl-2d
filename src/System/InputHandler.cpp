#include "InputHandler.hpp"
#include <GLFW/glfw3.h>
#include "Application.hpp"

static unsigned int NextId = 0;

InputHandler::InputHandler(std::shared_ptr<Application> app)
    : _application(app) {}

InputHandler::~InputHandler() {}

InputHandler::Id InputHandler::RegisterKey(int key, Callback cb) {
  _callbacks[key].insert(std::make_pair(NextId, cb));
  return NextId++;
}

void InputHandler::UnregisterKey(int key) { _callbacks[key].clear(); }

void InputHandler::UnregisterKey(int key, Id id) { _callbacks[key].erase(id); }

void InputHandler::Update(float dt) {
  for (auto& handler : _callbacks) {
    if (glfwGetKey(_application->GetWindow(), handler.first) == GLFW_PRESS) {
      for (auto& cb : handler.second) {
        cb.second(dt);
      }
    }
  }
}
