#pragma once
#include <object/Sprite.hpp>
#include <game/bullet.hpp>
#include <system/SpriteManager.hpp>

#include <string>
#include <array>

class CollisionManager;

class Weapon {
public:
  using Ptr = std::shared_ptr<Weapon>;

  Weapon(EntityManager::Ptr entityManager, SpriteManager::Ptr spriteManager, Sprite::Ptr parent);
  ~Weapon();

  void Init();
  void Fire(const glm::vec2& dir);
  void Update(float dt);

  void SetCollisionSystem(std::shared_ptr<CollisionManager> mgr);

  void Remove(std::shared_ptr<Bullet>);

private:
  size_t FindNextBulletIndex();

private:
  static const unsigned int MAX_BULLETS = 32;
  static const size_t INVALID_BULLET_INDEX = std::numeric_limits<size_t>::max();

  std::array<Bullet::Ptr, MAX_BULLETS> _bullets;
  EntityManager::Ptr _entityManager;
  SpriteManager::Ptr _spriteManager;
  Sprite::Ptr _parent;
  float _fireDelay;
  float _curDelay;
  bool _canFire;
  float _bulletSpeed;
  float _bulletLife;
};