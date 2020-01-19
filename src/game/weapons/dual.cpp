#include "dual.hpp"

DualWeapon::DualWeapon(SpriteManager::Ptr spriteManager, Sprite::Ptr parent)
    : Weapon(spriteManager, parent, 50, 650.0f, 0.5) {}

DualWeapon::~DualWeapon() {}

void DualWeapon::Fire(const glm::vec2& dir) {
  if (!_canFire) {
    return;
  }

  const glm::vec2 first_offset = glm::vec2(-dir.y, dir.x) * 10.0f;
  const glm::vec2 second_offset = glm::vec2(-dir.y, dir.x) * -10.0f;

  CreateProjectile(first_offset, dir);
  CreateProjectile(second_offset, dir);
  _canFire = false;
}
