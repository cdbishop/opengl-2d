#pragma once
#include <memory>
#include <system/EntityManager.hpp>

class Entity : public std::enable_shared_from_this<Entity>
{
public:
  Entity(std::shared_ptr<EntityManager> manager)
    :_manager(manager) {}

protected:
  EntityManager& GetEntitySystem() {
    return *_manager;
  }

  std::shared_ptr<EntityManager> GetEntitySystemPtr() {
    return _manager;
  }

private:
  std::shared_ptr<EntityManager> _manager;
};
