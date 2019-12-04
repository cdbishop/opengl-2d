#pragma once
#include <System/Scene.hpp>
#include <system/SpriteManager.hpp>
#include <System/Camera2D.hpp>
#include <system/collision/CollisionManager.hpp>
#include <game/player.hpp>
#include <game/drone.hpp>
#include <game/healthPickup.hpp>

#include <array>
#include <memory>

#include <glm/gtc/type_ptr.hpp>

class Shader;
class Sprite;

class MainScene : public Scene
{
public:
  using Ptr = std::shared_ptr<MainScene>;

	MainScene();
	~MainScene();

  void Init();
	void Update();
	void Render();

  Player::Ptr GetPlayer() const {
    return _player;
  }

private:
  SpriteManager::Ptr _spriteManager;
  
  Player::Ptr _player;
  Sprite::Ptr _background;
  Drone::Ptr _drone;
  HealthPickup::Ptr _pickup;

  Camera2D::Ptr _camera;
};
