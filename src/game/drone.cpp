#include "drone.hpp"

#include <GLFW/glfw3.h>
#include <glm/gtx/vector_angle.hpp>

#include <iostream>

#include <system/Scene.hpp>
#include <system/Application.hpp>

Drone::Drone(SpriteManager::Ptr spriteManager, int maxHealth)
  :Sprite("./data/textures/drone.png"),
  _spriteManager(spriteManager),
  _maxHealth(maxHealth),
  _currentHealth(maxHealth)
{
  SetPosition(std::move(glm::vec2(600.0f, 600.0f)));
  SetAnchor(glm::vec2(0.5f, 0.5f));
}

Drone::~Drone()
{
}

void Drone::Init()
{
  UpdateBounds();

  _weapon = std::make_shared<Weapon>(_spriteManager, shared_from_this(), 25, 5.0f, 1.5f);
  _weapon->Init();
}

void Drone::Update(float dt)
{
  if (Alive()) {
    float dist = glm::distance(_playerPos, GetPosition());
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
    }

    _weapon->Update(dt);
  }
}

void Drone::SetPlayerPos(const glm::vec2 & pos)
{
	_playerPos = pos;
}

void Drone::Damange(int amount)
{
  if (!Alive()) {
    return;
  }

  _currentHealth -= amount;
  if (_currentHealth <= 0) {
    Kill();
  }
}

void Drone::SetKillCallback(std::function<void(Ptr)> cb)
{
  _killedCallback = cb;
}

bool Drone::Alive() const {
  return _currentHealth > 0;
}

std::shared_ptr<Weapon> Drone::GetWeapon() const
{
  return _weapon;
}

void Drone::Kill()
{
  _weapon->Kill();

  if (_killedCallback)
    _killedCallback(std::static_pointer_cast<Drone>(shared_from_this()));
}

