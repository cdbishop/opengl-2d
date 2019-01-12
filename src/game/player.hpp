#pragma once
#include <object/Sprite.hpp>

#include <string>
#include <system/InputHandler.hpp>

class Player : public Sprite {
public:
  typedef std::shared_ptr<Player> Ptr;

  Player();  
  virtual ~Player();

  void SetupInput(InputHandler::Ptr inputHandler);

  void Update(float dt);

private:
  enum class RotateDir {
    Clockwise,
    Anticlockwise
  };
  void MoveForward();
  void RotateInput(RotateDir);

};