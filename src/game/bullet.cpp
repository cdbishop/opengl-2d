#include "bullet.hpp"

#include <game/weapon.hpp>

#include <system/Scene.hpp>

Bullet::Bullet(std::shared_ptr<Weapon> weapon)
  :Sprite("./data/textures/bullet.png"),
  _weapon(weapon),
  _velocity(glm::vec2(0.0f)),
  _maxLife(0.0f),
  _curLife(0.0f)
{
}

Bullet::Bullet(glm::vec2 velocity, float life, std::shared_ptr<Weapon> owner)
  :Sprite("./data/textures/bullet.png"),
  _weapon(owner),
  _velocity(std::move(velocity)),
  _maxLife(life),
  _curLife(life)
{
}

Bullet::~Bullet()
{
}

void Bullet::Init()
{
  UpdateBounds();
}

void Bullet::Update(float dt)
{
  if (!Alive()) {
    return;
  }

  Move(_velocity);
  _curLife -= dt;

  if (_curLife <= 0.0f) {
    _curLife = 0.0f;
  }
}

void Bullet::Revive(glm::vec2 velocity, float life)
{
  _velocity = std::move(velocity);
  _curLife = life;
  _maxLife = life;
}

void Bullet::Kill()
{
  _curLife = 0.0f;

  if (_killCallback)
    _killCallback(std::static_pointer_cast<Bullet>(shared_from_this()));
}

void Bullet::SetKillCallback(std::function<void(Ptr)> callback)
{
  _killCallback = callback;
}

std::shared_ptr<Weapon> Bullet::GetWeapon() const
{
  return _weapon;
}
