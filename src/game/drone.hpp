#pragma once
#include <object/Sprite.hpp>

#include <string>

#include <game/weapon.hpp>
#include <game/bullet.hpp>

class Drone : public Sprite {
public:
  using Ptr = std::shared_ptr<Drone>;

  Drone(std::shared_ptr<EntityManager> entityManager, SpriteManager::Ptr spriteManager);
  virtual ~Drone();

  void Init();
  
  void Update(float dt);

  std::type_index GetId() override {
    return std::type_index(typeid(*this));
  }

private:
  void OnBulletHit(Bullet::Ptr obj);

private:
  Weapon::Ptr _weapon;
  SpriteManager::Ptr _spriteManager;
};