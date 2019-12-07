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
#include "game/weapons/basic.hpp"
#include "game/weapons/dual.hpp"
#include "game/weapons/spray.hpp"

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
  _spriteManager = std::make_shared<SpriteManager>(
    GetApplication()->GetShaderManager()->CreateProgram("textured", "textured"),
    glm::ortho(0.0f, static_cast<float>(this->GetApplication()->GetWidth()),
      static_cast<float>(this->GetApplication()->GetHeight()), 0.0f, -1.0f, 1.0f));
 
  _background = std::make_shared<Sprite>("./data/textures/SpaceShooterRedux/Backgrounds/blue.png");
  _background->SetWidth(2000);
  _background->SetHeight(2000);
  _spriteManager->Add(_background, static_cast<unsigned int>(SpriteLayer::Background));

  _camera = std::make_shared<Camera2D>(std::move(glm::vec2(_background->GetWidth(), _background->GetHeight())),
    std::move(glm::vec2(GetApplication()->GetWidth(), GetApplication()->GetHeight())));

  _player = std::make_shared<Player>(_spriteManager);
  _player->Init();
  auto weapon = std::make_shared<BasicWeapon>(_spriteManager, _player->GetSprite());  
  _player->SetWeapon(weapon);

  _player->SetupInput(GetInputHandler());
  _camera->Follow(_player->GetSprite());

  _drone = std::make_shared<Drone>(_spriteManager, 100);
  _drone->Init();
  _spriteManager->Add(_drone, static_cast<unsigned int>(SpriteLayer::Ships));
  _drone->SetKillCallback([this](Drone::Ptr drone) {
    _spriteManager->Remove(drone);
  });
  

  _healthPickup = std::make_shared<HealthPickup>(_spriteManager, glm::vec2(800.0f, 100.0f), std::static_pointer_cast<MainScene>(shared_from_this()));
  _healthPickup->Init();

  _weaponPickup = std::make_shared<WeaponPickup>(_spriteManager, glm::vec2(300.0f, 800.0f), std::static_pointer_cast<MainScene>(shared_from_this()));
  _weaponPickup->Init();

  _weaponUpgrader = std::make_shared<WeaponUpgrader>(_spriteManager);
}

void MainScene::Update()
{
  GetInputHandler()->Update();

  _camera->Update();
  _player->Update(GetApplication()->GetFrameDelta());

  _drone->SetPlayerPos(_player->GetSprite()->GetPosition());
  _drone->Update(GetApplication()->GetFrameDelta());

  UpdateDroneCollision();

  if (_healthPickup->Alive()) {
    if (_player->GetSprite()->GetBounds()->Intersects(_healthPickup->GetSprite()->GetBounds())) {
      _healthPickup->Kill();
      _player->Heal();
    }
  }

  if (_weaponPickup->Alive()) {
    if (_player->GetSprite()->GetBounds()->Intersects(_weaponPickup->GetSprite()->GetBounds())) {
      _weaponPickup->Kill();
      auto curWeapon = _player->GetWeapon();
      auto newWeapon = _weaponUpgrader->UpgradeWeapon(curWeapon);

      if (newWeapon != curWeapon) {
        _player->SetWeapon(newWeapon);
      }
    }
  }
}

void MainScene::UpdateDroneCollision()
{
  if (_drone->Alive()) {
    if (auto bullet = _player->GetWeapon()->BulletHit(_drone)) {
      bullet->Kill();
      _drone->Damange(bullet->GetWeapon()->GetDamange());
    }

    if (auto bullet = _drone->GetWeapon()->BulletHit(_player->GetSprite())) {
      bullet->Kill();
      _player->Damage();
    }
  }
}

void MainScene::Render()
{	
  _spriteManager->Render(_camera);
}
