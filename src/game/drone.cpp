#include "drone.hpp"

#include <GLFW/glfw3.h>
#include <glm/gtx/vector_angle.hpp>

#include <iostream>

#include <system/Scene.hpp>
#include <system/Application.hpp>

Drone::Drone(std::shared_ptr<EntityManager> entityManager, SpriteManager::Ptr spriteManager)
  :Sprite(entityManager, "./data/textures/drone.png"),
  _spriteManager(spriteManager)
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
  GetCollisionSystem().Register(GetId(), GetBounds());

  _weapon = std::make_shared<Weapon>(GetEntitySystemPtr(), _spriteManager, GetPtr<Sprite>());

  //CollsionManager.OnHit(Bullet.GetTypeId(), std::bind(Drone::onBulletHit, this, std::placeholders::_1, std::placeholders::_2));
  //or
  //CollsionManager.OnHit<Bullet>(std::bind(Drone::onBulletHit, this, std::placeholders::_1, std::placeholders::_2));

  const auto cb = std::bind(&Drone::OnBulletHit, this, std::placeholders::_1);
  std::function<void(Bullet::Ptr)> cb2 = cb;
  GetCollisionSystem().OnHit<Bullet>(GetPtr<Bullet>(), cb2);
}

void Drone::Update(float dt)
{
  const auto playerPos = GetEntitySystem().Request("player").As<EntityPropContainer>()->Get<glm::vec2>("position");
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

void Drone::OnBulletHit(Bullet::Ptr obj)
{
  GetScene().GetApplication()->GetLogger()->info("Drone: Bullet hit");
  obj->Kill();
}

