#pragma once
#include "baseEnemy.hpp"

#include <string>

#include <game/bullet.hpp>
#include <game/weapon.hpp>

class Drone : public BaseEnemy {
public:
  using Ptr = std::shared_ptr<Drone>;

  Drone(SpriteManager::Ptr spriteManager, int maxHealth);
  virtual ~Drone();

  void Init();
  void Update(float dt);

  std::shared_ptr<Weapon> GetWeapon() const;

private:
  void Kill();

private:
  Weapon::Ptr _weapon;
};