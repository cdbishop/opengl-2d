#pragma once
#include <object/Sprite.hpp>
#include <system/SpriteManager.hpp>

class MainScene;

class HealthPickup {
public:
  using Ptr = std::shared_ptr<HealthPickup>;

  HealthPickup(SpriteManager::Ptr spriteManager, glm::vec2 position,
    std::shared_ptr<MainScene> scene);
  virtual ~HealthPickup();

  void Init();
  void Update(float dt);

  Sprite::Ptr GetSprite() const { return _sprite; }

  bool Alive();
  void Kill();

private:
  SpriteManager::Ptr _spriteManager;
  std::shared_ptr<MainScene> _scene;
  Sprite::Ptr _sprite;
  glm::vec2 _position;
  bool _alive;
};