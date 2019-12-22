#include "basic.hpp"

BasicWeapon::BasicWeapon(SpriteManager::Ptr spriteManager, Sprite::Ptr parent)
  :Weapon(spriteManager, parent, 50, 325.0f, 3.0)
{
}

BasicWeapon::~BasicWeapon()
{
}

void BasicWeapon::Fire(const glm::vec2 & dir)
{
  if (!_canFire) {
    return;
  }

  const glm::vec2 offset = glm::vec2(0.0f);

  CreateProjectile(offset, dir);
  _canFire = false;
}
