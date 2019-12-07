#pragma once
#include <game/weapon.hpp>

class BasicWeapon : public Weapon {
public:
  using Ptr = std::shared_ptr<BasicWeapon>;

  BasicWeapon(SpriteManager::Ptr spriteManager, Sprite::Ptr parent);
  ~BasicWeapon();

  void Fire(const glm::vec2& dir) override;

  WeaponUpgrader::WeaponType GetType() const
  {
    return WeaponUpgrader::WeaponType::Basic;
  }
};