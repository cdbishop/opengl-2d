#pragma once
#include <object/Sprite.hpp>

#include <string>

class Weapon;

class Bullet : public Sprite {
public:
  using Ptr = std::shared_ptr<Bullet>;

  Bullet(std::shared_ptr<EntityManager> manager);
  Bullet(std::shared_ptr<EntityManager> manager, glm::vec2 velocity, float life);
  virtual ~Bullet();

  void Init();

  void Update(float dt);

  bool Alive() {
    return _curLife > 0;
  }

  void Revive(glm::vec2 velocity, float life);

  void Kill();

  std::type_index GetId() override {
    return std::type_index(typeid(*this));
  }

private:
  glm::vec2 _velocity;
  float _maxLife;
  float _curLife;
};