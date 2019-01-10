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

MainScene::MainScene()
  :_spriteManager()
{
}

MainScene::~MainScene()
{

}

void MainScene::Init()
{
  _spriteManager = std::make_shared<SpriteManager>(
    GetApplication()->GetShaderManager()->CreateProgram("textured", "textured"),
    glm::ortho(0.0f, static_cast<float>(this->GetApplication()->GetWidth()),
      static_cast<float>(this->GetApplication()->GetHeight()), 0.0f, -1.0f, 1.0f));

  _sprite = std::make_shared<Sprite>("./data/textures/alienship.png");
  _sprite->SetPosition(std::move(glm::vec2(100.0f, 100.0f)));
  _spriteManager->Add(_sprite);

  _sprite2 = std::make_shared<Sprite>("./data/textures/alienship.png");
  _sprite2->SetPosition(std::move(glm::vec2(200.0f, 200.0f)));
  _spriteManager->Add(_sprite2);

  _sprite->SetAnchor(glm::vec2(0.5f, 0.5f));
  _sprite2->SetAnchor(glm::vec2(0.5f, 0.5f));
}

void MainScene::Update()
{
  _sprite2->Rotate(0.05f);
  _sprite->Rotate(-0.05f);
}

void MainScene::Render()
{	
  _spriteManager->Render();
}
