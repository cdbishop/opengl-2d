#pragma once
#include <System/Scene.hpp>
#include <system/SpriteManager.hpp>
#include <system/TextManager.hpp>

#include <array>
#include <memory>

#include <glm/gtc/type_ptr.hpp>

class MenuScene : public Scene {
 public:
  const static inline std::string Name = "MenuScene";

  MenuScene();
  ~MenuScene();

  void Init();
  void Update(float dt) override;
  void Render();

 private:
  void StartGame();
  void ToggleVolume();

 private:
  SpriteManager::Ptr _spriteManager;
  TextManager::Ptr _textManager;
  Sprite::Ptr _background;
  Camera2D::Ptr _camera;
};
