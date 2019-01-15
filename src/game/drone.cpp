#include "drone.hpp"

#include <GLFW/glfw3.h>

Drone::Drone(std::shared_ptr<EntityManager> entityManager, std::shared_ptr<SpriteManager> spriteManager)
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
  _weapon = std::make_shared<Weapon>(GetEntitySystemPtr(), _spriteManager, std::static_pointer_cast<Sprite>(shared_from_this()));
}

void Drone::Update(float dt)
{
  const auto playerPos = GetEntitySystem().Request("player").As<EntityPropContainer>()->Get<glm::vec2>("position");
  float dist = glm::distance(playerPos, GetPosition());
  glm::vec2 dir = playerPos - GetPosition();
  if (dist < 300) {
    _weapon->Fire(glm::normalize(dir));
  }

  _weapon->Update(dt);
}

