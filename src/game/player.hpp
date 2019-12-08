#pragma once
#include <object/Sprite.hpp>
#include <system/InputHandler.hpp>
#include <game/weapon.hpp>

#include <string>
#include <map>

class Player {
public:
  using Ptr = std::shared_ptr<Player>;

  explicit Player(SpriteManager::Ptr spriteManager);
  virtual ~Player();

  void Init();
  void SetupInput(InputHandler::Ptr inputHandler);
  void SetWeapon(Weapon::Ptr weapon);

  void Update(float dt);

  Weapon::Ptr GetWeapon();

  void Damage();
  void Heal();

  Sprite::Ptr GetSprite();

  void SetKilledCallback(std::function<void()> cb);

  unsigned int GetLives() const { return _lives; }

  void Respawn();

  bool IsAlive() const { return _alive; }

private:
  enum class RotateDir {
    Clockwise,
    Anticlockwise
  };

  enum class DamageLevel {
    None,
    Low,
    Med,
    High
  };

  void MoveForward();
  void RotateInput(RotateDir);
  void Fire();
  void UpdateDamage(DamageLevel newDamage);
  void Kill();

private:
  Weapon::Ptr _weapon;
  SpriteManager::Ptr _spriteManager;
  Sprite::Ptr _spriteShip;
  DamageLevel _currentDamage;
  unsigned int _lives;
  glm::vec2 _startPosition;
  bool _alive;
  
  std::map<DamageLevel, Sprite::Ptr> _spriteDamage;

  std::function<void()> _killed_callback;
};