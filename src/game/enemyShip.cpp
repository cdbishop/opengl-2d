#include "EnemyShip.hpp"

#include <GLFW/glfw3.h>
#include <glm/gtx/vector_angle.hpp>

#include <iostream>

#include <system/Scene.hpp>
#include <system/Application.hpp>

#include <game/weapons/basic.hpp>

EnemyShip::EnemyShip(SpriteManager::Ptr spriteManager, int maxHealth)
  :BaseEnemy(spriteManager, maxHealth, "./data/textures/SpaceShooterRedux/png/Enemies/enemyBlack3.png")
{
  SetPosition(std::move(glm::vec2(1200.0f,300.0f)));
  SetAnchor(glm::vec2(0.5f, 0.5f));

  _patrolCenter = GetPosition();
}

EnemyShip::~EnemyShip()
{
}

void EnemyShip::Init()
{
  BaseEnemy::Init();

  _weapon = std::make_shared<BasicWeapon>(_spriteManager, shared_from_this());
  _weapon->Init();
}

void EnemyShip::Update(float dt)
{
  if (Alive()) {
    /*float dist = glm::distance(_playerPos, GetPosition());
    glm::vec2 dir = glm::normalize(_playerPos - GetPosition());
    if (dist < 500) {
      const auto up = glm::vec2(0.0f, -1.0f);
      float angle = glm::angle(up, dir);
      const auto cross = glm::cross(glm::vec3(up, 0.0f), glm::vec3(dir, 0.0f));
      if (cross.z < 0) {
        angle *= -1;
      }
      SetRotation(angle);
      _weapon->Fire(dir);
    }*/

    auto angle = GetRotation();
    SetRotation(angle += (0.0001f * dt));
    angle = GetRotation();

    auto pos = GetPosition();
    auto circle_rad = 0.5f;

    auto center = _patrolCenter;
    
    //float x = glm::cos(angle) * (pos.x - center.x - 10.0f) - glm::sin(angle) * (pos.y - center.y - 10.0f) + center.x;
    //float y = glm::sin(angle) * (pos.x - center.x - 10.0f) + glm::cos(angle) * (pos.y - center.y - 10.0f) + center.y;

    /*float x = glm::cos(angle) * (center.x - 10.0f) - glm::sin(angle) * (center.y - 10.0f) + center.x;
    float y = glm::sin(angle) * (center.x - 10.0f) + glm::cos(angle) * (center.y - 10.0f) + center.y;*/

    //float x = glm::cos(angle) * (center.x) - glm::sin(angle) * (center.y) + center.x;
    //float y = glm::sin(angle) * (center.x) + glm::cos(angle) * (center.y) + center.y;

    //SetPosition(std::move(glm::vec2(x, y)));

    _weapon->Update(dt);
  }
}

std::shared_ptr<Weapon> EnemyShip::GetWeapon() const
{
  return _weapon;
}

void EnemyShip::Kill()
{
  BaseEnemy::Kill();

  _weapon->Kill();

  if (_killedCallback)
    _killedCallback(std::static_pointer_cast<EnemyShip>(shared_from_this()));
}

