#pragma once
#include <object/Sprite.hpp>

#include <string>
#include <system/InputHandler.hpp>

#include <game/weapon.hpp>

class Player : public Sprite {
public:
  using Ptr = std::shared_ptr<Player>;

  explicit Player(std::shared_ptr<EntityManager> manager);
  virtual ~Player();

  void Init();
  void SetupInput(InputHandler::Ptr inputHandler);
  void SetWeapon(Weapon::Ptr weapon);

  void Update(float dt);

  std::type_index GetId() override {
    return std::type_index(typeid(*this));
  }

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