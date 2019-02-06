#include "BoundingBox.hpp"

BoundingBox::BoundingBox(Sprite::Ptr owner, glm::vec2 dimensions)
  :_owner(owner),
   _dimensions(dimensions)
{
}

bool BoundingBox::Intersects(const BoundingBox& other)
{
  const auto otherPos = other.GetPosition();
  const auto otherSize = other.GetDimensions();

  return Left() < other.Right() && Right() > other.Left() &&
    Top() > other.Bottom() && Bottom() > other.Top();
}

bool BoundingBox::Contains(const glm::vec2& point)
{
  return point.x >= Left() && point.x <= Right() && point.y >= Top() && point.y <= Bottom();
}
