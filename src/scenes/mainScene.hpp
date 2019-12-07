#pragma once
#include <System/Scene.hpp>
#include <system/SpriteManager.hpp>
#include <System/Camera2D.hpp>
#include <system/collision/CollisionManager.hpp>
#include <game/player.hpp>
#include <game/drone.hpp>
#include <game/healthPickup.hpp>
#include <game/weaponPickup.hpp>
#include <game/weaponUpgrader.hpp>

#include <array>
#include <memory>

#include <glm/gtc/type_ptr.hpp>

class Shader;
class Sprite;

class MainScene : public Scene
{
public:
	MainScene();
	~MainScene();

  void Init();
	void Update();  
	void Render();

  Player::Ptr GetPlayer() const {
    return _player;
  }

private:
  void UpdateDroneCollision();

private:
  SpriteManager::Ptr _spriteManager;
  
  Player::Ptr _player;
  Sprite::Ptr _background;
  Drone::Ptr _drone;

  HealthPickup::Ptr _healthPickup;
  WeaponPickup::Ptr _weaponPickup;

  WeaponUpgrader::Ptr _weaponUpgrader;

  Camera2D::Ptr _camera;
};
