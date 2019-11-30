#include "weapon.hpp"
#include "game/spriteLayer.hpp"

Weapon::Weapon(SpriteManager::Ptr spriteManager, Sprite::Ptr parent, int damage, float bulletSpeed, float fireDelay)
  :_spriteManager(spriteManager),
  _parent(parent),
  _fireDelay(fireDelay),
  _curDelay(0.0),
  _canFire(true),
  _bulletSpeed(bulletSpeed),
  _bulletLife(50.0f),
  _damage(damage)
{
  
}

Weapon::~Weapon()
{

}

void Weapon::Init()
{
  for (unsigned int i = 0; i < MAX_BULLETS; ++i) {
    _bullets[i] = std::make_shared<Bullet>(shared_from_this());
  }

  for (unsigned int i = 0; i < MAX_BULLETS; ++i) {
    _bullets[i]->Init();
  }
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
  bullet->Revive(dir * _bulletSpeed, _bulletLife);
  bullet->SetAnchor(glm::vec2(0.5f, 0.5f));
  bullet->SetPosition(_parent->GetPosition() + 
    glm::vec2((_parent->GetWidth() / 2) - (bullet->GetWidth() / 2),
      (_parent->GetHeight() / 2) - (bullet->GetHeight() / 2)));
  bullet->SetRotation(_parent->GetRotation());
  bullet->SetKillCallback(std::bind(&Weapon::BulletKilled, this, std::placeholders::_1));
  
  _spriteManager->Add(_bullets[nextIdx], static_cast<unsigned int>(SpriteLayer::Projectiles));
  _canFire = false;
}

void Weapon::Update(float dt)
{
  for (auto&& bullet : _bullets) {
    bool wasAlive = bullet->Alive();
    bullet->Update(dt);
    if (!bullet->Alive() && wasAlive) {
      _spriteManager->Remove(bullet);
    }
  }

  if (!_canFire) {
    _curDelay += dt;
    if (_curDelay >= _fireDelay) {
      _curDelay = 0.0f;
      _canFire = true;
    }
  }
}

Bullet::Ptr Weapon::BulletHit(Sprite::Ptr target)
{
  auto it = std::find_if(_bullets.begin(), _bullets.end(), [&target](Bullet::Ptr bullet) {
    if (!bullet->Alive())
      return false;

    return bullet->GetBounds()->Intersects(*target->GetBounds());
  });

  if (it != _bullets.end()) {
    return *it;
  }

  return nullptr;
}

unsigned int Weapon::GetDamange() const
{
  return _damage;
}

void Weapon::Kill()
{
  for (auto&& bullet : _bullets) {
    if (bullet->Alive())
      bullet->Kill();
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

void Weapon::BulletKilled(Bullet::Ptr bullet)
{
  _spriteManager->Remove(bullet);
}
