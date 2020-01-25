#pragma once
#include <functional>
#include <map>
#include <memory>
#include <typeindex>
#include <vector>

class Sprite;

class CollisionFunctorBase {
public:
  CollisionFunctorBase() {}
  virtual ~CollisionFunctorBase() {}

  void SetContext(std::shared_ptr<Sprite> target) { _context = target; }

  std::shared_ptr<Sprite> GetContext() { return _context; }

  virtual void operator()(std::shared_ptr<Sprite> other) = 0;

protected:
  std::shared_ptr<Sprite> _context;
};

template <typename T>
class CollisionFunctor : public CollisionFunctorBase {
public:
  CollisionFunctor(std::function<void(std::shared_ptr<T>)> fn) : _fn(fn) {}

  void operator()(std::shared_ptr<Sprite> other) {
    _fn(std::static_pointer_cast<T>(other));
  }

private:
  std::function<void(std::shared_ptr<T>)> _fn;
};

class BoundingBox;

class CollisionManager final {
public:
  using Ptr = std::shared_ptr<CollisionManager>;

  CollisionManager();
  ~CollisionManager();

  void Update();

  template <typename T>
  void OnHit(std::shared_ptr<Sprite> context,
    std::function<void(std::shared_ptr<T>)> cb) {
    auto fn = std::make_shared<CollisionFunctor<T>>(cb);
    fn->SetContext(context);
    _callbacks.push_back(std::tie(fn, typeid(T)));
  }

  void Register(std::type_index id, std::shared_ptr<BoundingBox> collidable) {
    _collidables[id].push_back(collidable);
  }

private:
  std::map<std::type_index, std::vector<std::shared_ptr<BoundingBox>>>
    _collidables;

  std::vector<
    std::tuple<std::shared_ptr<CollisionFunctorBase>, std::type_index>>
    _callbacks;
};