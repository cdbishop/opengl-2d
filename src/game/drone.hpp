#pragma once
#include <object/Sprite.hpp>

#include <string>
#include <system/InputHandler.hpp>

#include <game/weapon.hpp>
#include <game/bullet.hpp>

class Drone : public Sprite {
public:
  using Ptr = std::shared_ptr<Drone>;

  Drone(std::shared_ptr<EntityManager> entityManager, SpriteManager::Ptr spriteManager);
  virtual ~Drone();

  void Init();
  
  void Update(float dt);

private:
  void OnBulletHit(Bullet::Ptr obj);

private:
  Weapon::Ptr _weapon;
  SpriteManager::Ptr _spriteManager;
};