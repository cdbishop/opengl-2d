#include "mainScene.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>

#include <iostream>
#include <stdexcept>

#include "System/Application.hpp"
#include "System/ShaderManager.hpp"
#include "object/Sprite.hpp"
#include "Math/Vector.hpp"
#include "game/spriteLayer.hpp"

MainScene::MainScene()
  :Scene(),
  _spriteManager(),
  _camera()
{
}

MainScene::~MainScene()
{
}

void MainScene::Init()
{
  _entityManager = std::make_shared<EntityManager>();
  _spriteManager = std::make_shared<SpriteManager>(
    GetApplication()->GetShaderManager()->CreateProgram("textured", "textured"),
    glm::ortho(0.0f, static_cast<float>(this->GetApplication()->GetWidth()),
      static_cast<float>(this->GetApplication()->GetHeight()), 0.0f, -1.0f, 1.0f));

  _background = std::make_shared<Sprite>(_entityManager, "./data/textures/starfield_2.jpg");
  _spriteManager->Add(_background, static_cast<unsigned int>(SpriteLayer::Background));

  _camera = std::make_shared<Camera2D>(std::move(glm::vec2(_background->GetWidth(), _background->GetHeight())),
    std::move(glm::vec2(GetApplication()->GetWidth(), GetApplication()->GetHeight())));

  _player = std::make_shared<Player>(_entityManager);
  _drone = std::make_shared<Drone>(_entityManager, _spriteManager);
  _drone->Init();

  auto weapon = std::make_shared<Weapon>(_entityManager, _spriteManager, _player);
  _player->SetWeapon(weapon);

  _player->SetupInput(GetInputHandler());
  _spriteManager->Add(_player, static_cast<unsigned int>(SpriteLayer::Ships));
  _spriteManager->Add(_drone, static_cast<unsigned int>(SpriteLayer::Ships));
  _camera->Follow(_player);
}

void MainScene::Update()
{
  GetInputHandler()->Update();
  _camera->Update();
  _player->Update(GetApplication()->GetFrameDelta());
  _drone->Update(GetApplication()->GetFrameDelta());
}

void MainScene::Render()
{	
  _spriteManager->Render(_camera);
}
