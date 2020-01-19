#pragma once
#include "baseEnemy.hpp"

#include <string>

#include <game/bullet.hpp>
#include <game/weapon.hpp>

class EnemyShip : public BaseEnemy {
public:
  using Ptr = std::shared_ptr<EnemyShip>;

  EnemyShip(SpriteManager::Ptr spriteManager, int maxHealth,
    const glm::vec2& initialPos);
  virtual ~EnemyShip();

  void Init();
  void Update(float dt);

  void UpdatePatrol(float dt);

  std::shared_ptr<Weapon> GetWeapon() const;

private:
  void Kill();

private:
  Weapon::Ptr _weapon;
  glm::vec2 _patrolCenter;
  float _heading;
  float _range;
};