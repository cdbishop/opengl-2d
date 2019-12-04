#pragma once
#include <object/Sprite.hpp>
#include <system/SpriteManager.hpp>
#include <scenes/mainScene.hpp>

class HealthPickup {
public:
  using Ptr = std::shared_ptr<HealthPickup>;

  HealthPickup(SpriteManager::Ptr spriteManager, glm::vec2 position, MainScene::Ptr scene);
  virtual ~HealthPickup();

  void Init();
  void Update(float dt);
 

private:
  SpriteManager::Ptr _spriteManager;
  MainScene::Ptr _scene;
  Sprite::Ptr _sprite;
  glm::vec2 _position;
};