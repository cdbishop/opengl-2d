#pragma once
#include <object/Sprite.hpp>
#include <system/SpriteManager.hpp>

class World {
public:
  using Ptr = std::shared_ptr<World>;

  World(SpriteManager::Ptr spriteManager, unsigned int width,
    unsigned int height);
  virtual ~World();

  void Init();
  void Update(float dt);

private:
  SpriteManager::Ptr _spriteManager;
};