#include "player.hpp"

#include <GLFW/glfw3.h>

Player::Player(std::shared_ptr<EntityManager> manager)
  :Sprite(manager, "./data/textures/alienship.png")
{
  SetPosition(std::move(glm::vec2(100.0f, 100.0f)));
  SetAnchor(glm::vec2(0.5f, 0.5f));

  
  std::function<glm::vec2()> g = std::bind(&Player::GetPosition, this);
  std::function<void(glm::vec2)> s = std::bind((void(Player::*)(const glm::vec2&))&Player::SetPosition, this, std::placeholders::_1);
    
  //GetEntitySystem().Publish("player.position", g, s);

  const auto pos = std::make_shared<EntityPropContainer>();
  pos->Publish("position", g, s);
  GetEntitySystem().Publish("player", pos);
}

Player::~Player()
{
}

void Player::SetupInput(InputHandler::Ptr inputHandler)
{
  inputHandler->RegisterKey(GLFW_KEY_W, std::bind(&Player::MoveForward, this));
  inputHandler->RegisterKey(GLFW_KEY_A, std::bind(&Player::MoveForward, this));
  inputHandler->RegisterKey(GLFW_KEY_A, std::bind(&Player::RotateInput, this, RotateDir::Anticlockwise));
  inputHandler->RegisterKey(GLFW_KEY_D, std::bind(&Player::RotateInput, this, RotateDir::Clockwise));
  inputHandler->RegisterKey(GLFW_KEY_SPACE, std::bind(&Player::Fire, this));
}

void Player::SetWeapon(Weapon::Ptr weapon)
{
  _weapon = weapon;
}

void Player::Update(float dt)
{
  _weapon->Update(dt);
}

void Player::MoveForward()
{
  glm::vec2 facing(sinf(GetRotation()), -cosf(GetRotation()));
  Move(facing * 5.5f);
}

void Player::RotateInput(RotateDir dir)
{
  float angle = (dir == RotateDir::Clockwise ? 0.02f : -0.02f);
  Rotate(angle);
}

void Player::Fire()
{
  _weapon->Fire(glm::vec2(sinf(GetRotation()), -cosf(GetRotation())));
}

