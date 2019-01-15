#pragma once
#include <memory>
#include <system/EntityManager.hpp>

class Entity
{
public:
  Entity(std::shared_ptr<EntityManager> manager)
    :_manager(manager) {}

protected:
  EntityManager& GetEntitySystem() {
    return *_manager;
  }

private:
  std::shared_ptr<EntityManager> _manager;
};
