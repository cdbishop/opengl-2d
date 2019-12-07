#include "player.hpp"

#include <GLFW/glfw3.h>

#include <game/spriteLayer.hpp>

Player::Player(SpriteManager::Ptr spriteManager)
  :_spriteManager(spriteManager),
  _currentDamage(DamageLevel::None)
{
  
}

Player::~Player()
{
}

void Player::Init()
{
  _spriteShip = std::make_shared<Sprite>("./data/textures/SpaceShooterRedux/png/playerShip3_red.png");
  _spriteShip->UpdateBounds();
  _spriteManager->Add(_spriteShip, static_cast<unsigned int>(SpriteLayer::Ships));

  _spriteShip->SetPosition(std::move(glm::vec2(100.0f, 100.0f)));
  _spriteShip->SetAnchor(glm::vec2(0.5f, 0.5f));      

  _spriteDamage[Player::DamageLevel::Low] = std::make_shared<Sprite>("./data/textures/SpaceShooterRedux/png/damage/playerShip3_damage1.png");
  _spriteDamage[Player::DamageLevel::Med] = std::make_shared<Sprite>("./data/textures/SpaceShooterRedux/png/damage/playerShip3_damage2.png");
  _spriteDamage[Player::DamageLevel::High] = std::make_shared<Sprite>("./data/textures/SpaceShooterRedux/png/damage/playerShip3_damage3.png");

  for (auto&& dmgSpr : _spriteDamage) {
    dmgSpr.second->UpdateBounds();
    dmgSpr.second->SetAnchor(glm::vec2(0.5f, 0.5f));
  }
}

void Player::SetupInput(InputHandler::Ptr inputHandler)
{
  inputHandler->RegisterKey(GLFW_KEY_W, std::bind(&Player::MoveForward, this));
  inputHandler->RegisterKey(GLFW_KEY_A, std::bind(&Player::RotateInput, this, RotateDir::Anticlockwise));
  inputHandler->RegisterKey(GLFW_KEY_D, std::bind(&Player::RotateInput, this, RotateDir::Clockwise));
  inputHandler->RegisterKey(GLFW_KEY_SPACE, std::bind(&Player::Fire, this));
}

void Player::SetWeapon(Weapon::Ptr weapon)
{
  _weapon = weapon;
  _weapon->Init();
}

void Player::Update(float dt)
{
  _weapon->Update(dt);

  if (_currentDamage != DamageLevel::None) {
    _spriteDamage[_currentDamage]->SetPosition(_spriteShip->GetPosition());
    _spriteDamage[_currentDamage]->SetRotation(_spriteShip->GetRotation());
  }
}

Weapon::Ptr Player::GetWeapon()
{
  return _weapon;
}

void Player::Damage()
{
  switch (_currentDamage) {
    case Player::DamageLevel::None:
      UpdateDamage(Player::DamageLevel::Low);
      break;

    case Player::DamageLevel::Low:
      UpdateDamage(Player::DamageLevel::Med);
      break;

    case Player::DamageLevel::Med:
      UpdateDamage(Player::DamageLevel::High);
      break;

    case Player::DamageLevel::High:
      Kill();
      break;

    default:
      throw std::runtime_error("Unknown damage level!");
  }
}

void Player::Heal() {
  switch (_currentDamage) {
    case Player::DamageLevel::None:
      break;

    case Player::DamageLevel::Low:
      UpdateDamage(Player::DamageLevel::None);
      break;

    case Player::DamageLevel::Med:
      UpdateDamage(Player::DamageLevel::Low);
      break;

    case Player::DamageLevel::High:
      UpdateDamage(Player::DamageLevel::Med);
      break;

    default:
      throw std::runtime_error("Unknown damage level!");
  }
}

Sprite::Ptr Player::GetSprite()
{
  return _spriteShip;
}

void Player::MoveForward()
{
  glm::vec2 facing(sinf(_spriteShip->GetRotation()), -cosf(_spriteShip->GetRotation()));
  _spriteShip->Move(facing * 5.5f);
}

void Player::RotateInput(RotateDir dir)
{
  float angle = (dir == RotateDir::Clockwise ? 0.02f : -0.02f);
  _spriteShip->Rotate(angle);
}

void Player::Fire()
{
  _weapon->Fire(glm::vec2(sinf(_spriteShip->GetRotation()), -cosf(_spriteShip->GetRotation())));
}

void Player::UpdateDamage(DamageLevel newDamage)
{
  if (_currentDamage != Player::DamageLevel::None) {
    _spriteManager->Remove(_spriteDamage[_currentDamage]);
  }

  if (newDamage != DamageLevel::None) {
    _spriteManager->Add(_spriteDamage[newDamage], static_cast<unsigned int>(SpriteLayer::Ships));
  }

  _currentDamage = newDamage;
}

void Player::Kill()
{
}

