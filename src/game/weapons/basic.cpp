#include "basic.hpp"

BasicWeapon::BasicWeapon(SpriteManager::Ptr spriteManager, Sprite::Ptr parent, float bulletSpeed, float fireDelay)
  :Weapon(spriteManager, parent, 50, bulletSpeed, fireDelay)
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
