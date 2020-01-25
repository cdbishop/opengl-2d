#include "drone.hpp"

#include <GLFW/glfw3.h>
#include <glm/gtx/vector_angle.hpp>

#include <iostream>

#include <system/Application.hpp>
#include <system/Scene.hpp>

#include <game/weapons/basic.hpp>

Drone::Drone(SpriteManager::Ptr spriteManager, int maxHealth)
  : BaseEnemy(spriteManager, maxHealth,
    "./data/textures/SpaceShooterRedux/png/ufoBlue.png") {
  SetAnchor(std::move(glm::vec2(0.5f, 0.5f)));
}

Drone::~Drone() {}

void Drone::Init() {
  BaseEnemy::Init();

  _weapon = std::make_shared<BasicWeapon>(_spriteManager, shared_from_this());
  _weapon->Init();
}

void Drone::Update(float dt) {
  if (Alive()) {
    auto& playerPos = _player->GetSprite()->GetPosition();
    float dist = glm::distance(playerPos, GetPosition());
    glm::vec2 dir = glm::normalize(playerPos - GetPosition());
    if (dist < 500) {
      const auto up = glm::vec2(0.0f, -1.0f);
      float angle = glm::angle(up, dir);
      const auto cross = glm::cross(glm::vec3(up, 0.0f), glm::vec3(dir, 0.0f));
      if (cross.z < 0) {
        angle *= -1;
      }
      SetRotation(angle);
      _weapon->Fire(dir);
    }

    _weapon->Update(dt);
  }
}

std::shared_ptr<Weapon> Drone::GetWeapon() const { return _weapon; }

void Drone::Kill() {
  _weapon->Kill();

  BaseEnemy::Kill();
}
