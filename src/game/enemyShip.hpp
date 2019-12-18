#pragma once
#include "baseEnemy.hpp"

#include <string>

#include <game/weapon.hpp>
#include <game/bullet.hpp>

class EnemyShip : public BaseEnemy {
public:
  using Ptr = std::shared_ptr<EnemyShip>;

  EnemyShip(SpriteManager::Ptr spriteManager, int maxHealth);
  virtual ~EnemyShip();

  void Init();
  void Update(float dt);

  std::shared_ptr<Weapon> GetWeapon() const;

private:
  void Kill();

private:
  Weapon::Ptr _weapon;
  glm::vec2  _patrolCenter;
};