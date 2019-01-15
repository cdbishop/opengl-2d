#include "bullet.hpp"

Bullet::Bullet(std::shared_ptr<EntityManager> manager)
  :Sprite(manager, "./data/textures/bullet.png"),
  _velocity(glm::vec2(0.0f)),
  _maxLife(0.0f),
  _curLife(0.0f)
{
}

Bullet::Bullet(std::shared_ptr<EntityManager> manager, glm::vec2 velocity, float life)
  :Sprite(manager, "./data/textures/bullet.png"),
  _velocity(std::move(velocity)),
  _maxLife(life),
  _curLife(life)
{
}

Bullet::~Bullet()
{
}

void Bullet::Update(float dt)
{
  if (!Alive()) {
    return;
  }

  Move(_velocity);
  _curLife += dt;
}

void Bullet::Revive(glm::vec2 velocity, float life)
{
  _velocity = std::move(velocity);
  _curLife = life;
  _maxLife = life;
}
