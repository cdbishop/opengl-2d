#pragma once
#include <glad/glad.h>
#include <functional>
#include <map>
#include <memory>
#include <unordered_map>
#include <vector>

class Application;

class InputHandler {
 public:
  using Ptr = std::shared_ptr<InputHandler>;
  using Callback = std::function<void(float)>;
  using CallbackList = std::map<unsigned int, Callback>;
  using Id = CallbackList::size_type;

  InputHandler(std::shared_ptr<Application> app);
  ~InputHandler();

  Id RegisterKey(int key, Callback cb);
  void UnregisterKey(int key, Id id);
  void UnregisterKey(int key);

  void Update(float dt);

 private:
  std::unordered_map<int, CallbackList> _callbacks;
  std::shared_ptr<Application> _application;
};