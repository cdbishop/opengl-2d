#include "BoundingBox.hpp"
#include <object/Sprite.hpp>

BoundingBox::BoundingBox(std::shared_ptr<Sprite> owner, glm::vec2 dimensions)
  :_owner(owner),
   _dimensions(dimensions)
{
}

inline const glm::vec2 & BoundingBox::GetPosition() const {
  return _owner->GetPosition();
}

bool BoundingBox::Intersects(const BoundingBox& other)
{
  const auto otherPos = other.GetPosition();
  const auto otherSize = other.GetDimensions();

  const auto left = Left();
  const auto otherRight = Right();
  const auto right = Right();
  const auto otherLeft = other.Left();
  const auto top = Top();
  const auto otherBtm = other.Bottom();
  const auto btm = Bottom();
  const auto otherTop = Top();

  return Left() < other.Right() && Right() > other.Left() &&
    Top() < other.Bottom() && Bottom() > other.Top();
}

bool BoundingBox::Contains(const glm::vec2& point)
{
  return point.x >= Left() && point.x <= Right() && point.y >= Top() && point.y <= Bottom();
}
