#include "player.hpp"

#include <GLFW/glfw3.h>

#include <game/spriteLayer.hpp>

Player::Player(SpriteManager::Ptr spriteManager)
  : _spriteManager(spriteManager),
  _currentDamage(DamageLevel::None),
  _lives(3),
  _startPosition(glm::vec2(100.0f, 100.0f)),
  _alive(true),
  _movementSpeed(250.0f),
  _rotationSpeed(2.0f) {}

Player::~Player() {}

void Player::Init() {
  _spriteShip = std::make_shared<Sprite>(
    "./data/textures/SpaceShooterRedux/png/playerShip3_red.png");
  _spriteShip->UpdateBounds();
  _spriteManager->Add(_spriteShip,
    static_cast<unsigned int>(SpriteLayer::Ships));

  _spriteShip->SetPosition(_startPosition);
  _spriteShip->SetAnchor(glm::vec2(0.5f, 0.5f));

  _spriteDamage[Player::DamageLevel::Low] = std::make_shared<Sprite>(
    "./data/textures/SpaceShooterRedux/png/damage/playerShip3_damage1.png");
  _spriteDamage[Player::DamageLevel::Med] = std::make_shared<Sprite>(
    "./data/textures/SpaceShooterRedux/png/damage/playerShip3_damage2.png");
  _spriteDamage[Player::DamageLevel::High] = std::make_shared<Sprite>(
    "./data/textures/SpaceShooterRedux/png/damage/playerShip3_damage3.png");

  for (auto&& dmgSpr : _spriteDamage) {
    dmgSpr.second->UpdateBounds();
    dmgSpr.second->SetAnchor(glm::vec2(0.5f, 0.5f));
  }
}

void Player::SetupInput(InputHandler::Ptr inputHandler) {
  _inputBindings.push_back(inputHandler->RegisterKey(
    GLFW_KEY_W, std::bind(&Player::MoveForward, this, std::placeholders::_1)));
  _inputBindings.push_back(inputHandler->RegisterKey(
    GLFW_KEY_A, std::bind(&Player::RotateInput, this,
      RotateDir::Anticlockwise, std::placeholders::_1)));
  _inputBindings.push_back(inputHandler->RegisterKey(
    GLFW_KEY_D, std::bind(&Player::RotateInput, this, RotateDir::Clockwise,
      std::placeholders::_1)));
  _inputBindings.push_back(inputHandler->RegisterKey(GLFW_KEY_SPACE, std::bind(&Player::Fire, this)));
}

void Player::SetWeapon(Weapon::Ptr weapon) {
  _weapon = weapon;
  _weapon->Init();
}

void Player::Update(float dt) {
  if (_alive) {
    _weapon->Update(dt);

    if (_currentDamage != DamageLevel::None) {
      _spriteDamage[_currentDamage]->SetPosition(_spriteShip->GetPosition());
      _spriteDamage[_currentDamage]->SetRotation(_spriteShip->GetRotation());
    }
  }
}

Weapon::Ptr Player::GetWeapon() { return _weapon; }

void Player::Damage() {
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

Sprite::Ptr Player::GetSprite() { return _spriteShip; }

void Player::SetKilledCallback(std::function<void()> cb) {
  _killed_callback = cb;
}

void Player::Respawn() {
  _spriteShip->SetPosition(_startPosition);
  UpdateDamage(Player::DamageLevel::None);
  _spriteShip->SetRotation(0.0f);
  _spriteManager->Add(_spriteShip,
    static_cast<unsigned int>(SpriteLayer::Ships));
  _alive = true;
}

void Player::MoveForward(float dt) {
  if (_alive) {
    glm::vec2 facing(sinf(_spriteShip->GetRotation()),
      -cosf(_spriteShip->GetRotation()));
    _spriteShip->Move(facing * _movementSpeed * dt);
  }
}

void Player::RotateInput(RotateDir dir, float dt) {
  if (_alive) {
    float angle = (dir == RotateDir::Clockwise ? _rotationSpeed * dt
      : -_rotationSpeed * dt);
    _spriteShip->Rotate(angle);
  }
}

void Player::Fire() {
  if (_alive) {
    _weapon->Fire(glm::vec2(sinf(_spriteShip->GetRotation()),
      -cosf(_spriteShip->GetRotation())));
  }
}

void Player::UpdateDamage(DamageLevel newDamage) {
  if (_currentDamage != Player::DamageLevel::None) {
    _spriteManager->Remove(_spriteDamage[_currentDamage]);
  }

  if (newDamage != DamageLevel::None) {
    _spriteManager->Add(_spriteDamage[newDamage],
      static_cast<unsigned int>(SpriteLayer::Ships));

    _spriteDamage[newDamage]->SetPosition(_spriteShip->GetPosition());
    _spriteDamage[newDamage]->SetRotation(_spriteShip->GetRotation());
  }

  _currentDamage = newDamage;
}

void Player::Kill() {
  --_lives;
  _alive = false;
  _spriteManager->Remove(_spriteShip);
  UpdateDamage(DamageLevel::None);

  if (_killed_callback) _killed_callback();
}
