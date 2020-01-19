#include "./healthPickup.hpp"

#include <game/spriteLayer.hpp>

HealthPickup::HealthPickup(SpriteManager::Ptr spriteManager, glm::vec2 position,
  std::shared_ptr<MainScene> scene)
  : _spriteManager(spriteManager),
  _scene(scene),
  _position(position),
  _alive(true) {}

HealthPickup::~HealthPickup() {}

void HealthPickup::Init() {
  _sprite = std::make_shared<Sprite>(
    "./data/textures/SpaceShooterRedux/png/Power-ups/pill_green.png");
  _sprite->UpdateBounds();
  _spriteManager->Add(_sprite, static_cast<unsigned int>(SpriteLayer::Ships));

  _sprite->SetPosition(_position);
}

void HealthPickup::Update(float dt) {}

bool HealthPickup::Alive() { return _alive; }

void HealthPickup::Kill() {
  _spriteManager->Remove(_sprite);
  _alive = false;
}
