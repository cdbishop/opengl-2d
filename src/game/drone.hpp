#pragma once
#include <object/Sprite.hpp>

#include <string>

#include <game/weapon.hpp>
#include <game/bullet.hpp>

class Drone : public Sprite {
public:
  using Ptr = std::shared_ptr<Drone>;

  Drone(SpriteManager::Ptr spriteManager, int maxHealth);
  virtual ~Drone();

  void Init();  
  void Update(float dt);
  void SetPlayerPos(const glm::vec2& pos);
  void Damange(int amount);
  void SetKillCallback(std::function<void(Ptr)> cb);

  bool Alive() const;

  std::shared_ptr<Weapon> GetWeapon() const;

private:
  void Kill();

private:
  Weapon::Ptr _weapon;
  SpriteManager::Ptr _spriteManager;
  glm::vec2 _playerPos;
  int _maxHealth;
  int _currentHealth;
  std::function<void(Ptr)> _killedCallback;
};