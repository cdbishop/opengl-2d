#include "EnemyWave.hpp"

#include <memory>

#include "game/spriteLayer.hpp"

EnemyWave::EnemyWave(SpriteManager::Ptr spriteManager, StartDesc startDesc)
  :_spriteManager(spriteManager),
   _startDesc(std::move(startDesc))
{

}

EnemyWave::~EnemyWave()
{
}

void EnemyWave::Init(Player::Ptr player)
{
  _player = player;

  for (auto&& desc : _startDesc) {
    switch (desc.first) {
      case EnemyType::Ship: {
        auto ship = std::make_shared<EnemyShip>(_spriteManager, 200, desc.second);
        ship->Init();
        ship->SetPlayer(player);
        ship->SetPosition(desc.second);
        _spriteManager->Add(ship, static_cast<unsigned int>(SpriteLayer::Ships));
        ship->SetKillCallback([this](BaseEnemy::Ptr enemy) {
          _spriteManager->Remove(enemy);
        });
        _enemyShips.push_back(ship);
      }
      break;

      case EnemyType::Drone: {
        auto ship = std::make_shared<Drone>(_spriteManager, 200);
        ship->Init();
        ship->SetPlayer(player);
        ship->SetPosition(desc.second);
        _spriteManager->Add(ship, static_cast<unsigned int>(SpriteLayer::Ships));
        ship->SetKillCallback([this](BaseEnemy::Ptr enemy) {
          _spriteManager->Remove(enemy);
        });
        _drones.push_back(ship);
      }
      break;
    }
  }
}

void EnemyWave::Update(float dt)
{
  for (auto&& enemyShip : _enemyShips) {
    enemyShip->Update(dt);
  }

  for (auto&& drone : _drones) {
    drone->Update(dt);
  }

  for (auto&& drone : _drones) {
    if (drone->Alive()) {
      if (auto bullet = _player->GetWeapon()->BulletHit(drone)) {
        bullet->Kill();
        drone->Damange(bullet->GetWeapon()->GetDamange());
      }

      if (auto bullet = drone->GetWeapon()->BulletHit(_player->GetSprite())) {
        bullet->Kill();
        _player->Damage();
      }

    }
  }

  for (auto&& enemyShip : _enemyShips) {

    // player bullet hit enemy
    if (auto bullet = _player->GetWeapon()->BulletHit(enemyShip)) {
      bullet->Kill();
      enemyShip->Damange(bullet->GetWeapon()->GetDamange());
    }


    // enemy bullet hit player
    if (auto bullet = enemyShip->GetWeapon()->BulletHit(_player->GetSprite())) {
      bullet->Kill();
      _player->Damage();
    }
  }
}
