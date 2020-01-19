#include "weaponUpgrader.hpp"

#include "weapon.hpp"
#include "weapons/basic.hpp"
#include "weapons/dual.hpp"
#include "weapons/spray.hpp"

WeaponUpgrader::WeaponUpgrader(SpriteManager::Ptr spriteManager)
    : _spriteManager(spriteManager) {}

WeaponUpgrader::~WeaponUpgrader() {}

std::shared_ptr<Weapon> WeaponUpgrader::UpgradeWeapon(
    std::shared_ptr<Weapon> weapon) {
  switch (weapon->GetType()) {
    case WeaponType::Basic:
      return std::make_shared<DualWeapon>(_spriteManager, weapon->GetParent());

    case WeaponType::Dual:
      return std::make_shared<SprayWeapon>(_spriteManager, weapon->GetParent());

    default:
      return weapon;
  }
}
