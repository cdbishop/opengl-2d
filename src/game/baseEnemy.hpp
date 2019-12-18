#pragma once
#include <object/Sprite.hpp>

#include <string>

#include <game/weapon.hpp>
#include <game/bullet.hpp>

class BaseEnemy : public Sprite {
public:
  using Ptr = std::shared_ptr<BaseEnemy>;

  BaseEnemy(SpriteManager::Ptr spriteManager, int maxHealth, const std::string& asset);
  virtual ~BaseEnemy();

  virtual void Init();
  virtual void Update(float dt);
  virtual void Damange(int amount);

  void SetPlayerPos(const glm::vec2& pos);  
  void SetKillCallback(std::function<void(Ptr)> cb);

  bool Alive() const;

protected:
  virtual void Kill();

protected:
  SpriteManager::Ptr _spriteManager;
  glm::vec2 _playerPos;
  int _maxHealth;
  int _currentHealth;
  std::function<void(Ptr)> _killedCallback;
};