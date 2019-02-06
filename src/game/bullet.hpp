#pragma once
#include <object/Sprite.hpp>

#include <string>

class Bullet : public Sprite {
public:
  using Ptr = std::shared_ptr<Bullet>;

  Bullet(std::shared_ptr<EntityManager> manager);
  Bullet(std::shared_ptr<EntityManager> manager, glm::vec2 velocity, float life);
  virtual ~Bullet();

  void Update(float dt);

  bool Alive() {
    return _curLife > 0;
  }

  void Revive(glm::vec2 velocity, float life);

private:
  glm::vec2 _velocity;
  float _maxLife;
  float _curLife;

};