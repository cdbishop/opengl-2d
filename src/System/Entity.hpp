#pragma once
#include <memory>
#include <system/EntityManager.hpp>
#include <system/collision/CollisionManager.hpp>

class Scene;

class Entity : public std::enable_shared_from_this<Entity>
{
public:
  Entity(std::shared_ptr<EntityManager> entity_manager)
    :_entity_manager(entity_manager) {}

  void SetCollisionManager(std::shared_ptr<CollisionManager> mgr) {
    _collision_manager = mgr;
  }

  void SetScene(std::shared_ptr<Scene> scene) {
    _scene = scene;
  }

  template<typename T>
  std::shared_ptr<T> GetPtr() {
    return std::static_pointer_cast<T>(shared_from_this());
  }

protected:
  EntityManager& GetEntitySystem() {
    return *_entity_manager;
  }

  std::shared_ptr<EntityManager> GetEntitySystemPtr() {
    return _entity_manager;
  }

  CollisionManager& GetCollisionSystem() {
    return *_collision_manager;
  }

  std::shared_ptr<CollisionManager> GetCollisionSystemPtr() {
    return _collision_manager;
  }

  Scene& GetScene() {
    return *_scene;
  }

  std::shared_ptr<Scene> GetScenePtr() {
    return _scene;
  }

  virtual std::type_index GetId() = 0;

  template<typename T>
  bool Is() {
    return std::type_info(T) == GetId();
  }

  template<typename T>
  T& As() {
    return static_cast<T&>(*this);
  }

private:  
  std::shared_ptr<EntityManager> _entity_manager;
  std::shared_ptr<CollisionManager> _collision_manager;
  std::shared_ptr<Scene> _scene;
};
