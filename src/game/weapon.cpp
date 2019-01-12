#include "weapon.hpp"

Weapon::Weapon(SpriteManager::Ptr spriteManager)
  :_spriteManager(spriteManager)
{
  for (unsigned int i = 0; i < MAX_BULLETS; ++i) {
    _bullets[i] = std::make_shared<Bullet>();
  }
}

Weapon::~Weapon()
{
}

void Weapon::Fire(const glm::vec2 & dir)
{
  size_t nextIdx = FindNextBulletIndex();
  if (nextIdx == INVALID_BULLET_INDEX) {
    return;
  }

  _bullets[nextIdx]->Revive(dir * 10.0f, 5.0f);
}

size_t Weapon::FindNextBulletIndex()
{
  auto alivePred = [](const Bullet::Ptr bullet) { return bullet->Alive(); };
  auto it = std::find_if(std::begin(_bullets), std::end(_bullets), alivePred);
  if (it == std::end(_bullets)) {
    return INVALID_BULLET_INDEX;
  }
  return std::distance(std::begin(_bullets), it);
}
