#include "EnemyManager.hpp"

EnemyManager::EnemyManager(SpriteManager::Ptr spriteManager, OnScreenCountdown::Ptr countdown, Player::Ptr player)
  :_player(player),
   _nextWaveCountdown(countdown) {
  
  AddWave(spriteManager, player, std::move(EnemyWave::StartDesc({
    std::make_pair(EnemyWave::EnemyType::Drone, glm::vec2(600.0f, 600.0f)),
    std::make_pair(EnemyWave::EnemyType::Ship, glm::vec2(1200.0f, 300.0f))
    })));

  AddWave(spriteManager, player, std::move(EnemyWave::StartDesc({
    std::make_pair(EnemyWave::EnemyType::Drone, glm::vec2(600.0f, 600.0f)),
    std::make_pair(EnemyWave::EnemyType::Drone, glm::vec2(1200.0f, 600.0f)),
    std::make_pair(EnemyWave::EnemyType::Ship, glm::vec2(1200.0f, 300.0f)),
    std::make_pair(EnemyWave::EnemyType::Ship, glm::vec2(1200.0f, 700.0f))
    })));
}

EnemyManager::~EnemyManager()
{
}

void EnemyManager::Init()
{
  _current_wave = _waves[0];

  _current_wave->Spawn(_player);
}

void EnemyManager::Update(float dt)
{
  _nextWaveCountdown->Update();

  for (auto&& wave : _waves) {
    wave->Update(dt);
  }
}

void EnemyManager::SetAllWavesCompletedCallback(AllWavesCompletedCB callback)
{
  _waves_completed_cb = callback;
}

void EnemyManager::AddWave(SpriteManager::Ptr spriteManager, Player::Ptr player, EnemyWave::StartDesc&& waveDesc)
{
  auto wave = std::make_shared<EnemyWave>(spriteManager, waveDesc);

  wave->SetWaveEndCallback(std::bind(&EnemyManager::NextWave, this, wave, _player, _waves.size()));

  _waves.push_back(wave);
}

void EnemyManager::NextWave(EnemyWave::Ptr current, Player::Ptr player, size_t index)
{
  if (_waves.size() > index + 1) {
    _current_wave = _waves[index + 1];

    _nextWaveCountdown->StartCountdown(3, [player, this]() {
      _current_wave->Spawn(player);
    });
    
  }
  else {
    //all waves beaten
    if (_waves_completed_cb)
      _waves_completed_cb();
  }
}
