#pragma once
#include <System/Scene.hpp>
#include <system/SpriteManager.hpp>
#include <System/Camera2D.hpp>
#include <system/collision/CollisionManager.hpp>
#include <game/player.hpp>
#include <game/drone.hpp>

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

private:
  std::array<float, 24> _vertices;

  unsigned int _vertex_buffer;
  unsigned int _vertex_array;

  std::shared_ptr<Shader> _shader;

  glm::mat4 _projection;

  SpriteManager::Ptr _spriteManager;
  EntityManager::Ptr _entityManager;
  CollisionManager::Ptr _collisionManager;
  
  Player::Ptr _player;
  Sprite::Ptr _background;
  Drone::Ptr _drone;

  Camera2D::Ptr _camera;
};
