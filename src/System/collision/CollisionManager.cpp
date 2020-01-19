#include "CollisionManager.hpp"
#include "BoundingBox.hpp"

#include <object/Sprite.hpp>

CollisionManager::CollisionManager() {}

CollisionManager::~CollisionManager() {}

void CollisionManager::Update() {
  for (auto&[cb, type] : _callbacks) {
    const auto& targets = _collidables[type];

    for (const auto& target : targets) {
      if (target->Intersects(*cb->GetContext()->GetBounds())) {
        (*cb)(target->GetOwner());
      }
    }
  }
}
