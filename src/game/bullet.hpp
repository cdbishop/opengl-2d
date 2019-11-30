#pragma once
#include <object/Sprite.hpp>

#include <string>
#include <functional>

class Weapon;

class Bullet : public Sprite {
public:
  using Ptr = std::shared_ptr<Bullet>;

  Bullet(std::shared_ptr<Weapon> owner);
  Bullet(glm::vec2 velocity, float life, std::shared_ptr<Weapon> owner);
  virtual ~Bullet();

  void Init();

  void Update(float dt);

  bool Alive() {
    return _curLife > 0;
  }

  void Revive(glm::vec2 velocity, float life);

  void Kill();

  void SetKillCallback(std::function<void(Ptr)> callback);

  std::shared_ptr<Weapon> GetWeapon() const;
  
private:
  std::shared_ptr<Weapon> _weapon;
  glm::vec2 _velocity;
  float _maxLife;
  float _curLife;
  std::function<void(Ptr)> _killCallback;
};