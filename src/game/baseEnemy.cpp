#include "BaseEnemy.hpp"

#include <GLFW/glfw3.h>
#include <glm/gtx/vector_angle.hpp>

#include <iostream>

#include <system/Scene.hpp>
#include <system/Application.hpp>

#include <game/weapons/basic.hpp>

BaseEnemy::BaseEnemy(SpriteManager::Ptr spriteManager, int maxHealth, const std::string& asset)
  :Sprite(asset),
  _spriteManager(spriteManager),
  _maxHealth(maxHealth),
  _currentHealth(maxHealth)
{
  
}

BaseEnemy::~BaseEnemy()
{
}

void BaseEnemy::Init()
{
  UpdateBounds();
}

void BaseEnemy::Update(float dt)
{
  
}

void BaseEnemy::Damange(int amount)
{
  if (!Alive()) {
    return;
  }

  _currentHealth -= amount;
  if (_currentHealth <= 0) {
    Kill();
  }
}

void BaseEnemy::SetPlayer(Player::Ptr player)
{
  _player = player;
}

void BaseEnemy::SetKillCallback(std::function<void(Ptr)> cb)
{
  _killedCallback = cb;
}

bool BaseEnemy::Alive() const {
  return _currentHealth > 0;
}

void BaseEnemy::Kill()
{
  if (_killedCallback)
    _killedCallback(std::static_pointer_cast<BaseEnemy>(shared_from_this()));
}

