#pragma once
#include <object/Sprite.hpp>

#include <string>
#include <system/InputHandler.hpp>

#include <game/weapon.hpp>

class Player : public Sprite {
public:
  typedef std::shared_ptr<Player> Ptr;

  explicit Player(std::shared_ptr<EntityManager> manager);
  virtual ~Player();

  void SetupInput(InputHandler::Ptr inputHandler);
  void SetWeapon(Weapon::Ptr weapon);

  void Update(float dt);

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