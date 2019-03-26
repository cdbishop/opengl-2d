#pragma once

#include <memory>
#include <map>
#include <vector>
#include <typeindex>
#include <functional>
#include <type_traits>

class Sprite;

class EventFunctorBase {
public:
  EventFunctorBase() { }

  void SetContext(std::shared_ptr<Sprite> target) {
    _context = target;
  }

  std::shared_ptr<Sprite> GetContext() {
    return _context;
  }

protected:
  std::shared_ptr<Sprite> _context;
};

template<typename T>
class EventFunctor : public EventFunctorBase {
public:
  EventFunctor(std::function<void(const T&)> fn)
    :_fn(fn) { }

  template<typename T>
  void operator()(const T& obj) {
    _fn(obj);
  }

private:
  std::function<void(const T&)> _fn;
};


class BoundingBox;

class EventManager final {
public:
  using Ptr = std::shared_ptr<EventManager>;

  EventManager() { }
  ~EventManager() { }

  template<typename T>
  void Notify(const T& msg) {
    auto id = std::type_index(typeid(msg));
    
    const auto& subs = _subscribers[id];
    for (auto&& sub : subs) {
      auto eventSub = std::static_pointer_cast<EventFunctor<T>>(sub);
      (*eventSub)(msg);
    }
  }

  template<typename T>
  void Register(std::type_index id, std::function<void(std::shared_ptr<T>)> cb) {
    auto fn = std::make_shared<EventFunctor<T>>(cb);
    _subscribers[id].push(fn);
  }

private:
  std::map<std::type_index, std::vector<std::shared_ptr<EventFunctorBase>>> _subscribers;
};