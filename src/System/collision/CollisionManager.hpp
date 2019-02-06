#pragma once
#include <system/collision/BoundingBox.hpp>

class CollisionManager {
public:
  CollisionManager();
  ~CollisionManager();

private:
  std::vector<BoundingBox::Ptr> _collidables;
};