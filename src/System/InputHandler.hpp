#pragma once
#include <memory>
#include <functional>
#include <unordered_map>
#include <vector>
#include <glad/glad.h>

class Application;

class InputHandler {
public:
  using Ptr = std::shared_ptr<InputHandler>;  
  using Callback = std::function<void()>;

  InputHandler(std::shared_ptr<Application> app);
  ~InputHandler();

  void RegisterKey(int key, Callback cb);

  void Update();
  
private:
  std::unordered_map<int, std::vector<Callback>> _callbacks;
  std::shared_ptr<Application> _application;
};