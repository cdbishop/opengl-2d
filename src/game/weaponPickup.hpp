#pragma once
#include <object/Sprite.hpp>
#include <system/SpriteManager.hpp>

class MainScene;

class WeaponPickup {
 public:
  using Ptr = std::shared_ptr<WeaponPickup>;

  WeaponPickup(SpriteManager::Ptr spriteManager, glm::vec2 position,
               std::shared_ptr<MainScene> scene);
  virtual ~WeaponPickup();

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