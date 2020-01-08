#pragma once
#include <System/SpriteManager.hpp>
#include <game/EnemyWave.hpp>
#include <game/player.hpp>

#include <vector>

class EnemyManager {
public:
  using Ptr = std::shared_ptr<EnemyManager>;
  using AllWavesCompletedCB = std::function<void()>;

  EnemyManager(SpriteManager::Ptr spriteManager, Player::Ptr player);
  ~EnemyManager();

  void Init();
  void Update(float dt);

  void SetAllWavesCompletedCallback(AllWavesCompletedCB callback);

private:
  void AddWave(SpriteManager::Ptr spriteManager, Player::Ptr player, EnemyWave::StartDesc&& waveDesc);

  void NextWave(EnemyWave::Ptr current, Player::Ptr player, size_t index);

private:
  std::vector<EnemyWave::Ptr> _waves;
  const Player::Ptr _player;
  EnemyWave::Ptr _current_wave;
  AllWavesCompletedCB _waves_completed_cb;
};