#pragma once
#include <object/Sprite.hpp>
#include <system/SpriteManager.hpp>

class Weapon;

class WeaponUpgrader {
public:
  using Ptr = std::shared_ptr<WeaponUpgrader>;

  enum class WeaponType { Basic, Dual, Spray };

  explicit WeaponUpgrader(SpriteManager::Ptr spriteManager);
  virtual ~WeaponUpgrader();

  std::shared_ptr<Weapon> UpgradeWeapon(std::shared_ptr<Weapon> weapon);

private:
  SpriteManager::Ptr _spriteManager;
};