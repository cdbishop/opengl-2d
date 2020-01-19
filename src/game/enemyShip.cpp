#include "EnemyShip.hpp"

#include <GLFW/glfw3.h>
#include <glm/gtx/vector_angle.hpp>

#include <iostream>

#include <system/Application.hpp>
#include <system/Scene.hpp>

#include <game/weapons/basic.hpp>

EnemyShip::EnemyShip(SpriteManager::Ptr spriteManager, int maxHealth,
                     const glm::vec2& initialPos)
    : BaseEnemy(
          spriteManager, maxHealth,
          "./data/textures/SpaceShooterRedux/png/Enemies/enemyBlack3.png"),
      _heading(0.0f),
      _range(350.0f) {
  SetAnchor(glm::vec2(0.5f, 0.5f));
  _patrolCenter = initialPos;
  SetPosition(initialPos);
}

EnemyShip::~EnemyShip() {}

void EnemyShip::Init() {
  BaseEnemy::Init();

  _weapon = std::make_shared<BasicWeapon>(_spriteManager, shared_from_this());
  _weapon->Init();
}

void EnemyShip::Update(float dt) {
  if (Alive()) {
    auto distToPlayer =
        glm::distance(GetPosition(), _player->GetSprite()->GetPosition());
    if (distToPlayer > _range) {
      UpdatePatrol(dt);
    } else if (_player->IsAlive()) {
      // move + rotate towards player
      auto pos = GetPosition();
      auto playerPos = _player->GetSprite()->GetPosition();
      auto targetRot = glm::atan(playerPos.x - pos.x, playerPos.y - pos.y);
      SetRotation(glm::pi<float>() - targetRot);

      auto dir = playerPos - pos;
      auto norm = glm::normalize(dir);

      _weapon->Fire(norm);
    }

    _weapon->Update(dt);
  }
}

void EnemyShip::UpdatePatrol(float dt) {
  _heading += (1.0f * dt);

  auto pos = GetPosition();
  auto circle_rad = 150.5f;
  auto center = _patrolCenter;

  auto offset = glm::vec2(glm::sin(_heading), glm::cos(_heading)) * circle_rad;
  SetPosition(_patrolCenter + offset);

  pos = GetPosition();

  auto rot = glm::atan(pos.x - _patrolCenter.x, pos.y - _patrolCenter.y);
  SetRotation(glm::half_pi<float>() - rot);
}

std::shared_ptr<Weapon> EnemyShip::GetWeapon() const { return _weapon; }

void EnemyShip::Kill() {
  BaseEnemy::Kill();

  _weapon->Kill();

  // if (_killedCallback)
  //  _killedCallback(std::static_pointer_cast<EnemyShip>(shared_from_this()));
}
