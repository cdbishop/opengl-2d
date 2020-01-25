#include "InputHandler.hpp"
#include <GLFW/glfw3.h>
#include "Application.hpp"

static unsigned int NextId = 0;

InputHandler::InputHandler(std::shared_ptr<Application> app)
  : _application(app) {}

InputHandler::~InputHandler() {}

InputBinding::Ptr InputHandler::RegisterKey(int key, Callback cb) {
  _callbacks[key].insert(std::make_pair(NextId, cb));
  return InputBinding::Ptr(new InputBinding(key, NextId++, *this));
}

void InputHandler::UnregisterKey(int key) {
  _callbacks[key].clear();
}

void InputHandler::UnregisterKey(const InputBinding& binding) { 
  _callbacks[binding.GetKey()].erase(binding.GetId()); 
}

void InputHandler::Update(float dt) {
  for (auto& handler : _callbacks) {
    if (glfwGetKey(_application->GetWindow().get(), handler.first) == GLFW_PRESS) {
      for (auto& cb : handler.second) {
        cb.second(dt);
      }
    }
  }
}

InputBinding::InputBinding(int key, Id id, InputHandler& inputHandler)
  :_inputHandler(inputHandler),
  _key(key),
  _id(id) {}

inline InputBinding::~InputBinding() {
  _inputHandler.UnregisterKey(*this);
}
