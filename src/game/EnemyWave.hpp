#pragma once
#include <game/drone.hpp>
#include <game/enemyShip.hpp>
#include <game/player.hpp>

#include <System/SpriteManager.hpp>

class EnemyWave {
 public:
  enum class EnemyType { Drone, Ship };

  using EnemyKilledFn = std::function<void(EnemyType)>;

  using Ptr = std::shared_ptr<EnemyWave>;
  using StartDesc = std::vector<std::pair<EnemyType, glm::vec2>>;
  using WaveEndCb = std::function<void()>;

  EnemyWave(SpriteManager::Ptr spriteManager, StartDesc startDesc);
  ~EnemyWave();

  void Spawn(Player::Ptr player);
  void Update(float dt);

  void SetWaveEndCallback(WaveEndCb callback);
  void SetEnemyKilledCallback(EnemyKilledFn callback);

 private:
  void CheckWaveEnd();

 private:
  SpriteManager::Ptr _spriteManager;
  const StartDesc _startDesc;
  Player::Ptr _player;

  WaveEndCb _waveEndCallback;
  EnemyKilledFn _enemyKilledCallback;

  std::vector<Drone::Ptr> _drones;
  std::vector<EnemyShip::Ptr> _enemyShips;
};