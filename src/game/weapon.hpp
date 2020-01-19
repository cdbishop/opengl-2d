#pragma once
#include <game/bullet.hpp>
#include <game/weaponUpgrader.hpp>
#include <object/Sprite.hpp>
#include <system/SpriteManager.hpp>

#include <array>
#include <string>

class Weapon : public std::enable_shared_from_this<Weapon> {
 public:
  using Ptr = std::shared_ptr<Weapon>;

  Weapon(SpriteManager::Ptr spriteManager, Sprite::Ptr parent, int damage,
         float bulletSpeed, float fireDelay);
  ~Weapon();

  void Init();
  virtual void Fire(const glm::vec2& dir) = 0;
  void Update(float dt);

  Bullet::Ptr BulletHit(Sprite::Ptr target);

  unsigned int GetDamange() const;

  void Kill();

  virtual WeaponUpgrader::WeaponType GetType() const = 0;

  Sprite::Ptr GetParent() const { return _parent; }

 protected:
  void CreateProjectile(const glm::vec2& src_offset, const glm::vec2& dir);

 private:
  size_t FindNextBulletIndex();

  void BulletKilled(Bullet::Ptr bullet);

 protected:
  bool _canFire;

 private:
  static const unsigned int MAX_BULLETS = 32;
  static const size_t INVALID_BULLET_INDEX = std::numeric_limits<size_t>::max();

  std::array<Bullet::Ptr, MAX_BULLETS> _bullets;
  SpriteManager::Ptr _spriteManager;
  Sprite::Ptr _parent;
  float _fireDelay;
  float _curDelay;
  float _bulletSpeed;
  float _bulletLife;
  int _damage;
};