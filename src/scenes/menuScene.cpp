#include "menuScene.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>

#include "System/Application.hpp"
#include "System/ShaderManager.hpp"

#include "game/spriteLayer.hpp"

#include "mainScene.hpp"

MenuScene::MenuScene()
  :Scene()
{
}

MenuScene::~MenuScene()
{
}

void MenuScene::Init()
{
  _spriteManager = std::make_shared<SpriteManager>(
    GetApplication()->GetShaderManager()->CreateProgram("textured", "textured"),
    glm::ortho(0.0f, static_cast<float>(this->GetApplication()->GetWidth()),
      static_cast<float>(this->GetApplication()->GetHeight()), 0.0f, -1.0f, 1.0f));

  _textManager = std::make_shared<TextManager>(GetApplication()->GetShaderManager(),
    glm::ortho(0.0f, static_cast<float>(this->GetApplication()->GetWidth()),
      static_cast<float>(this->GetApplication()->GetHeight()), 0.0f, -1.0f, 1.0f));

  _background = std::make_shared<Sprite>("./data/textures/SpaceShooterRedux/Backgrounds/blue.png");
  _background->SetWidth(GetApplication()->GetWidth());
  _background->SetHeight(GetApplication()->GetHeight());
  _spriteManager->Add(_background, static_cast<unsigned int>(SpriteLayer::Background));

  _camera = std::make_shared<Camera2D>(std::move(glm::vec2(_background->GetWidth(), _background->GetHeight())),
    std::move(glm::vec2(GetApplication()->GetWidth(), GetApplication()->GetHeight())));

  
  _textManager->AddText("SPAY-SSEE", glm::vec2(GetApplication()->GetWidth() / 2.0f, 20.0f));
  _textManager->AddText("press space to start", glm::vec2(GetApplication()->GetWidth() / 2.0f, GetApplication()->GetHeight() - 50.0f), 0.5f);

  GetInputHandler()->RegisterKey(GLFW_KEY_SPACE, std::bind(&MenuScene::SpacePressed, this));
}

void MenuScene::Update()
{
  GetInputHandler()->Update();
  _camera->Update();
}

void MenuScene::Render()
{	
  _spriteManager->Render(_camera);  
  _textManager->Render();
}

void MenuScene::SpacePressed()
{
  GetApplication()->SetScene(MainScene::Name);
}
