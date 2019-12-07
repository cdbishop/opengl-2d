#pragma once
#include <object/Sprite.hpp>
#include <game/bullet.hpp>
#include <system/SpriteManager.hpp>

#include <string>
#include <array>

class Weapon : public std::enable_shared_from_this<Weapon> {
public:
  using Ptr = std::shared_ptr<Weapon>;

  Weapon(SpriteManager::Ptr spriteManager, Sprite::Ptr parent, int damage, float bulletSpeed, float fireDelay);
  ~Weapon();

  void Init();
  void Fire(const glm::vec2& dir, const glm::vec2& src_offset = glm::vec2(0.0f));
  void Update(float dt);

  Bullet::Ptr BulletHit(Sprite::Ptr target);

  unsigned int GetDamange() const;

  void Kill();

private:
  void CreateBullet(const glm::vec2& dir, const glm::vec2& src_offset = glm::vec2(0.0f));

private:
  size_t FindNextBulletIndex();

  void BulletKilled(Bullet::Ptr bullet);

private:
  static const unsigned int MAX_BULLETS = 32;
  static const size_t INVALID_BULLET_INDEX = std::numeric_limits<size_t>::max();

  std::array<Bullet::Ptr, MAX_BULLETS> _bullets;
  SpriteManager::Ptr _spriteManager;
  Sprite::Ptr _parent;
  float _fireDelay;
  float _curDelay;
  bool _canFire;
  float _bulletSpeed;
  float _bulletLife;
  int _damage;
};