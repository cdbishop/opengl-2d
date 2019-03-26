#pragma once

#include <memory>
#include <map>
#include <vector>
#include <typeindex>
#include <functional>

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

  virtual void operator()(std::shared_ptr<Sprite> other) = 0;

protected:
  std::shared_ptr<Sprite> _context;
};

template<typename T>
class EventFunctor : public EventFunctorBase {
public:
  EventFunctor(std::function<void(std::shared_ptr<T>)> fn)
    :_fn(fn) { }

  void operator()(std::shared_ptr<Sprite> other) {
    _fn(std::static_pointer_cast<T>(other));
  }

private:
  std::function<void(std::shared_ptr<T>)> _fn;
};


class BoundingBox;

class EventManager final {
public:
  using Ptr = std::shared_ptr<EventManager>;

  EventManager() { }
  ~EventManager() { }

  template<typename T>
  void Notify(const T& msg) {
    
  }

  void Register(std::type_index id, std::shared_ptr<BoundingBox> collidable) {
    _collidables[id].push_back(collidable);
  }

private:
  std::map<std::type_index, std::vector<std::shared_ptr<BoundingBox>>> _collidables;

  std::vector<std::tuple<std::shared_ptr<EventFunctorBase>, std::type_index>> _callbacks;
};