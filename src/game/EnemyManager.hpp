#pragma once
#include <System/SpriteManager.hpp>
#include <game/EnemyWave.hpp>
#include <game/player.hpp>

#include <vector>

class EnemyManager {
public:
  using Ptr = std::shared_ptr<EnemyManager>;

  EnemyManager(SpriteManager::Ptr spriteManager);
  ~EnemyManager();

  void Init(Player::Ptr player);
  void Update(float dt);

private:
  std::vector<EnemyWave::Ptr> _waves;
};