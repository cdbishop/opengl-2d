#pragma once
#include <game/weapon.hpp>

class DualWeapon : public Weapon {
public:
  using Ptr = std::shared_ptr<DualWeapon>;

  DualWeapon(SpriteManager::Ptr spriteManager, Sprite::Ptr parent);
  ~DualWeapon();

  void Fire(const glm::vec2& dir) override;

  WeaponUpgrader::WeaponType GetType() const
  {
    return WeaponUpgrader::WeaponType::Dual;
  }
};