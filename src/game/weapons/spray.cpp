#include "spray.hpp"

SprayWeapon::SprayWeapon(SpriteManager::Ptr spriteManager, Sprite::Ptr parent)
  :Weapon(spriteManager, parent, 50, 25.0f, 0.1f),
  _offsets({0.0f, 20.0f, 0.0f, -20.0f}),
  _current_offset(0)
{
}

SprayWeapon::~SprayWeapon()
{
}

void SprayWeapon::Fire(const glm::vec2 & dir)
{
  if (!_canFire) {
    return;
  }

  const glm::vec2 offset = glm::vec2(-dir.y, dir.x) * _offsets[_current_offset];
  CreateProjectile(offset, dir);

  _current_offset++;

  if (_current_offset > (_offsets.size() - 1))
    _current_offset = 0;

  _canFire = false;
}
