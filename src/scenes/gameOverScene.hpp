#pragma once
#include <System/Scene.hpp>
#include <system/SpriteManager.hpp>
#include <system/TextManager.hpp>

#include <array>
#include <memory>

#include <glm/gtc/type_ptr.hpp>

class GameOverScene : public Scene {
 public:
  const static inline std::string Name = "GameOverScene";

  GameOverScene();
  ~GameOverScene();

  void SetArgs(unsigned int score);

  void Init() override;
  void Update(float dt) override;
  void Render();

 private:
  void RestartGame();

 private:
  SpriteManager::Ptr _spriteManager;
  TextManager::Ptr _textManager;
  Sprite::Ptr _background;
  Camera2D::Ptr _camera;

  unsigned int _score;
};
