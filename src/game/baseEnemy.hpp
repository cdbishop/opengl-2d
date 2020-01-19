#pragma once
#include <object/Sprite.hpp>

#include <string>

#include <game/bullet.hpp>
#include <game/player.hpp>
#include <game/weapon.hpp>

class BaseEnemy : public Sprite {
 public:
  using Ptr = std::shared_ptr<BaseEnemy>;

  BaseEnemy(SpriteManager::Ptr spriteManager, int maxHealth,
            const std::string& asset);
  virtual ~BaseEnemy();

  virtual void Init();
  virtual void Update(float dt);
  virtual void Damange(int amount);

  void SetPlayer(Player::Ptr player);
  void SetKillCallback(std::function<void(Ptr)> cb);

  bool Alive() const;

 protected:
  virtual void Kill();

 protected:
  SpriteManager::Ptr _spriteManager;
  Player::Ptr _player;
  int _maxHealth;
  int _currentHealth;
  std::function<void(Ptr)> _killedCallback;
};