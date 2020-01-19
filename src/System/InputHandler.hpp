#pragma once
#include <glad/glad.h>
#include <functional>
#include <map>
#include <memory>
#include <unordered_map>
#include <vector>

class Application;
class InputHandler;

class InputBinding {
public:
  using Ptr = std::shared_ptr<InputBinding>;

  ~InputBinding();

private:
  using Id = unsigned int;
  friend class InputHandler;

  InputBinding(int key, Id id, InputHandler& inputHandler);

  int GetKey() const {
    return _key;
  }

  Id GetId() const {
    return _id;
  }

private:
  InputHandler& _inputHandler;
  int _key;
  Id _id;
};

class InputHandler {
public: 
  using Ptr = std::shared_ptr<InputHandler>;
  using Callback = std::function<void(float)>;
  using CallbackList = std::map<unsigned int, Callback>;  

  InputHandler(std::shared_ptr<Application> app);
  ~InputHandler();

  InputBinding::Ptr RegisterKey(int key, Callback cb);
  void UnregisterKey(const InputBinding& binding);
  void UnregisterKey(int key);

  void Update(float dt);

private:
  std::unordered_map<int, CallbackList> _callbacks;
  std::shared_ptr<Application> _application;
};