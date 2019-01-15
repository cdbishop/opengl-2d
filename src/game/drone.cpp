#include "drone.hpp"

#include <GLFW/glfw3.h>

Drone::Drone(std::shared_ptr<EntityManager> manager)
  :Sprite(manager, "./data/textures/drone.png")
{
  SetPosition(std::move(glm::vec2(600.0f, 600.0f)));
  SetAnchor(glm::vec2(0.5f, 0.5f));
}

Drone::~Drone()
{
}

void Drone::Update(float dt)
{
  const auto playerPos = GetEntitySystem().Request("player").As<EntityPropContainer>()->Get<glm::vec2>("position");
  float dist = glm::distance(playerPos, GetPosition());
}

