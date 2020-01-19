#pragma once
#include <glm/vec2.hpp>
#include <memory>

class Sprite;

class BoundingBox {
public:
  using Ptr = std::shared_ptr<BoundingBox>;

  BoundingBox(std::shared_ptr<Sprite> owner, glm::vec2 dimensions);

  const std::shared_ptr<Sprite> GetOwner() { return _owner; }

  const glm::vec2& GetPosition() const;

  const glm::vec2& GetDimensions() const { return _dimensions; }

  bool Intersects(const BoundingBox& other);
  bool Intersects(const Ptr other);

  bool Contains(const glm::vec2& point);

  float Top() const { return GetPosition().y; }

  float Left() const { return GetPosition().x; }

  float Bottom() const { return GetPosition().y + GetDimensions().y; }

  float Right() const { return GetPosition().x + GetDimensions().x; }

private:
  glm::vec2 _dimensions;
  std::shared_ptr<Sprite> _owner;
};