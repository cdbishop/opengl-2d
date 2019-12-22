#include "EnemyManager.hpp"

EnemyManager::EnemyManager(SpriteManager::Ptr spriteManager)
{
  _waves.push_back(std::make_shared<EnemyWave>(spriteManager, EnemyWave::StartDesc({
      std::make_pair(EnemyWave::EnemyType::Drone, glm::vec2(600.0f, 600.0f)),
      std::make_pair(EnemyWave::EnemyType::Ship, glm::vec2(1200.0f, 300.0f))
    })));
}

EnemyManager::~EnemyManager()
{
}

void EnemyManager::Init(Player::Ptr player)
{
  for (auto&& wave : _waves) {
    wave->Init(player);
  }
}

void EnemyManager::Update(float dt)
{
  for (auto&& wave : _waves) {
    wave->Update(dt);
  }
}
