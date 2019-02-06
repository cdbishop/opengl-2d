#pragma once
#include <object/Sprite.hpp>

class BoundingBox {
public:
  using Ptr = std::shared_ptr<BoundingBox>;

  BoundingBox(Sprite::Ptr owner, glm::vec2 dimensions);

  const glm::vec2& GetPosition() const {
    return _owner->GetPosition();
  }

  const glm::vec2& GetDimensions() const {
    return _dimensions;
  }

  bool Intersects(const BoundingBox& other);
  bool Contains(const glm::vec2& point);

  float Top() const {
    return GetPosition().y;
  }

  float Left() const {
    return GetPosition().x;
  }

  float Bottom() const {
    return GetPosition().y + GetDimensions().y;
  }

  float Right() const {
    return GetPosition().x + GetDimensions().x;
  }

private:
  glm::vec2 _dimensions;
  Sprite::Ptr _owner;
};