#pragma once
#include <object/Sprite.hpp>

#include <string>
#include <system/InputHandler.hpp>

#include <game/weapon.hpp>

class Drone : public Sprite {
public:
  typedef std::shared_ptr<Drone> Ptr;

  explicit Drone(std::shared_ptr<EntityManager> manager);
  virtual ~Drone();
  
  void Update(float dt);
};