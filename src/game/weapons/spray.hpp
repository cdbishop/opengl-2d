#pragma once
#include <game/weapon.hpp>

class SprayWeapon : public Weapon {
public:
  using Ptr = std::shared_ptr<SprayWeapon>;

  SprayWeapon(SpriteManager::Ptr spriteManager, Sprite::Ptr parent);
  ~SprayWeapon();

  void Fire(const glm::vec2& dir) override;

  WeaponUpgrader::WeaponType GetType() const
  {
    return WeaponUpgrader::WeaponType::Spray;
  }

private:
  std::array<float, 4> _offsets;
  unsigned int _current_offset;
};