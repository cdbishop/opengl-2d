#pragma once
#include <object/Sprite.hpp>

#include <string>
#include <system/InputHandler.hpp>

#include <game/weapon.hpp>

class Player : public Sprite {
public:
  using Ptr = std::shared_ptr<Player>;

  explicit Player();
  virtual ~Player();

  void Init();
  void SetupInput(InputHandler::Ptr inputHandler);
  void SetWeapon(Weapon::Ptr weapon);

  void Update(float dt);

  Weapon::Ptr GetWeapon();

  void Damage(unsigned int damage);

private:
  enum class RotateDir {
    Clockwise,
    Anticlockwise
  };

  void MoveForward();
  void RotateInput(RotateDir);
  void Fire();

private:
  Weapon::Ptr _weapon;
};