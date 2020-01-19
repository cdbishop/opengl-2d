#include "./weaponPickup.hpp"

#include <game/spriteLayer.hpp>

WeaponPickup::WeaponPickup(SpriteManager::Ptr spriteManager, glm::vec2 position,
  std::shared_ptr<MainScene> scene)
  : _spriteManager(spriteManager),
  _scene(scene),
  _position(position),
  _alive(true) {}

WeaponPickup::~WeaponPickup() {}

void WeaponPickup::Init() {
  _sprite = std::make_shared<Sprite>(
    "./data/textures/SpaceShooterRedux/png/Power-ups/powerupGreen_bolt.png");
  _sprite->UpdateBounds();
  _spriteManager->Add(_sprite, static_cast<unsigned int>(SpriteLayer::Ships));

  _sprite->SetPosition(_position);
}

void WeaponPickup::Update(float dt) {}

bool WeaponPickup::Alive() { return _alive; }

void WeaponPickup::Kill() {
  _spriteManager->Remove(_sprite);
  _alive = false;
}
