#pragma once
#include <System/Scene.hpp>
#include <system/SpriteManager.hpp>
#include <system/TextManager.hpp>

#include <array>
#include <memory>

#include <glm/gtc/type_ptr.hpp>

class GameOverScene : public Scene
{
public:
  const static inline std::string Name = "GameOverScene";

  GameOverScene();
	~GameOverScene();

  void Init();
	void Update();  
	void Render();

private:
  void RestartGame();

private:
  SpriteManager::Ptr _spriteManager;
  TextManager::Ptr _textManager;
  Sprite::Ptr _background;
  Camera2D::Ptr _camera;
};
