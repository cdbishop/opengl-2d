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

  _background = std::make_shared<Sprite>("./data/textures/starfield_2.jpg");
  _spriteManager->Add(_background);

  _player = std::make_shared<Sprite>("./data/textures/alienship.png");
  _player->SetPosition(std::move(glm::vec2(100.0f, 100.0f)));
  _spriteManager->Add(_player);

  _player->SetAnchor(glm::vec2(0.5f, 0.5f));
}

void MainScene::Update()
{
  if (glfwGetKey(GetApplication()->GetWindow(), GLFW_KEY_W) == GLFW_PRESS) {
    glm::vec2 facing(sinf(_player->GetRotation()), -cosf(_player->GetRotation()));
    _player->Move(facing * 0.5f);
  }

  if (glfwGetKey(GetApplication()->GetWindow(), GLFW_KEY_A) == GLFW_PRESS) {
    _player->Rotate(-1.0f * GetApplication()->GetFrameDelta());
  }
  else if (glfwGetKey(GetApplication()->GetWindow(), GLFW_KEY_D) == GLFW_PRESS) {
    _player->Rotate(1.0f * GetApplication()->GetFrameDelta());
  }
}

void MainScene::Render()
{	
  _spriteManager->Render();
}
