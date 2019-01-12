#pragma once
#include <object/Sprite.hpp>
#include <game/bullet.hpp>
#include <system/SpriteManager.hpp>

#include <string>
#include <array>

class Weapon {
public:
  typedef std::shared_ptr<Weapon> Ptr;

  Weapon(SpriteManager::Ptr spriteManager, Sprite::Ptr parent);
  ~Weapon();

  void Fire(const glm::vec2& dir);
  void Update(float dt);

private:
  size_t FindNextBulletIndex();

private:
  static const unsigned int MAX_BULLETS = 32;
  static const size_t INVALID_BULLET_INDEX = std::numeric_limits<size_t>::max();

  std::array<Bullet::Ptr, MAX_BULLETS> _bullets;
  SpriteManager::Ptr _spriteManager;
  Sprite::Ptr _parent;
  float _fireDelay;
  float _curDelay;
  bool _canFire;
};