#include "weapon.hpp"
#include "game/spriteLayer.hpp"

Weapon::Weapon(SpriteManager::Ptr spriteManager, Sprite::Ptr parent)
  :_spriteManager(spriteManager),
  _parent(parent),
  _fireDelay(0.5f),
  _curDelay(0.0),
  _canFire(true)
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
  if (!_canFire) {
    return;
  }

  size_t nextIdx = FindNextBulletIndex();
  if (nextIdx == INVALID_BULLET_INDEX) {
    return;
  }

  auto bullet = _bullets[nextIdx];
  bullet->Revive(dir * 10.0f, 5.0f);
  bullet->SetAnchor(glm::vec2(0.5f, 0.5f));
  bullet->SetPosition(_parent->GetPosition() + 
    glm::vec2((_parent->GetWidth() / 2) - (bullet->GetWidth() / 2),
      (_parent->GetHeight() / 2) - (bullet->GetHeight() / 2)));
  bullet->SetRotation(_parent->GetRotation());
  
  _spriteManager->Add(_bullets[nextIdx], static_cast<unsigned int>(SpriteLayer::Projectiles));
  _canFire = false;
}

void Weapon::Update(float dt)
{
  for (auto&& bullet : _bullets) {
    bullet->Update(dt);
  }

  if (!_canFire) {
    _curDelay += dt;
    if (_curDelay >= _fireDelay) {
      _curDelay = 0.0f;
      _canFire = true;
    }
  }
}

size_t Weapon::FindNextBulletIndex()
{
  auto notAlivePred = [](const Bullet::Ptr bullet) { return !bullet->Alive(); };
  auto it = std::find_if(std::begin(_bullets), std::end(_bullets), notAlivePred);
  if (it == std::end(_bullets)) {
    return INVALID_BULLET_INDEX;
  }
  return std::distance(std::begin(_bullets), it);
}
