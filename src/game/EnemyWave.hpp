#pragma once
#include <game/drone.hpp>
#include <game/enemyShip.hpp>
#include <game/player.hpp>

#include <System/SpriteManager.hpp>

class EnemyWave {
public:
  enum class EnemyType {
    Drone,
    Ship
  };

  using Ptr = std::shared_ptr<EnemyWave>;
  using StartDesc = std::vector<std::pair<EnemyType, glm::vec2>>;

  EnemyWave(SpriteManager::Ptr spriteManager, StartDesc startDesc);
  ~EnemyWave();

  void Init(Player::Ptr player);
  void Update(float dt);

private:
  SpriteManager::Ptr _spriteManager;
  const StartDesc _startDesc;
  Player::Ptr _player;

  std::vector<Drone::Ptr> _drones;
  std::vector<EnemyShip::Ptr> _enemyShips;
};