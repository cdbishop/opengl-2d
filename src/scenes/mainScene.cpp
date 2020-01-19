#include "mainScene.hpp"

#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <glm/gtc/matrix_transform.hpp>

#include <iostream>
#include <stdexcept>

#include "Math/Vector.hpp"
#include "System/Application.hpp"
#include "System/ShaderManager.hpp"
#include "game/spriteLayer.hpp"
#include "game/weapons/basic.hpp"
#include "game/weapons/dual.hpp"
#include "game/weapons/spray.hpp"
#include "object/Sprite.hpp"

#include "gameOverScene.hpp"

MainScene::MainScene() : Scene(), _spriteManager(), _camera(), _score(0) {}

MainScene::~MainScene() {}

void MainScene::Init() {
  _score = 0;

  const auto projection =
      glm::ortho(0.0f, static_cast<float>(this->GetApplication()->GetWidth()),
                 static_cast<float>(this->GetApplication()->GetHeight()), 0.0f,
                 -1.0f, 1.0f);

  _spriteManager = std::make_shared<SpriteManager>(
      GetApplication()->GetShaderManager()->CreateProgram("textured",
                                                          "textured"),
      projection);

  _eventManager = std::make_shared<EventManager>();

  _uiManager = std::make_shared<UIManager>(
      GetApplication()->GetShaderManager()->CreateProgram("textured",
                                                          "textured"),
      projection);

  _background = std::make_shared<Sprite>(
      "./data/textures/SpaceShooterRedux/Backgrounds/blue.png");
  _background->SetWidth(2000);
  _background->SetHeight(2000);
  _spriteManager->Add(_background,
                      static_cast<unsigned int>(SpriteLayer::Background));

  _camera = std::make_shared<Camera2D>(
      std::move(glm::vec2(_background->GetWidth(), _background->GetHeight())),
      std::move(glm::vec2(GetApplication()->GetWidth(),
                          GetApplication()->GetHeight())));

  _player = std::make_shared<Player>(_spriteManager);
  _player->Init();
  auto weapon = std::make_shared<BasicWeapon>(
      _spriteManager, _player->GetSprite(), 650.0f, 1.0f);
  _player->SetWeapon(weapon);
  _player->SetKilledCallback(std::bind(&MainScene::OnPlayerKilled, this));

  CreateLivesUI();

  _player->SetupInput(GetInputHandler());
  _camera->Follow(_player->GetSprite());

  _textManager = std::make_shared<TextManager>(
      GetApplication()->GetShaderManager(),
      glm::ortho(0.0f, static_cast<float>(this->GetApplication()->GetWidth()),
                 static_cast<float>(this->GetApplication()->GetHeight()), 0.0f,
                 -1.0f, 1.0f));

  auto nextWaveCountdown = std::make_shared<OnScreenCountdown>(
      _textManager, glm::vec2(GetApplication()->GetWidth() / 2, 20.0f),
      "Next Wave: ");
  _enemyManager = std::make_shared<EnemyManager>(_spriteManager,
                                                 nextWaveCountdown, _player);
  _enemyManager->Init();
  _enemyManager->SetAllWavesCompletedCallback(
      std::bind(&MainScene::OnAllEnemyWavesComplete, this));
  _enemyManager->SetEnemyKilledCallback(
      std::bind(&MainScene::OnEnemyKilled, this, std::placeholders::_1));

  _healthPickup = std::make_shared<HealthPickup>(
      _spriteManager, glm::vec2(800.0f, 100.0f),
      std::static_pointer_cast<MainScene>(shared_from_this()));
  _healthPickup->Init();

  _weaponPickup = std::make_shared<WeaponPickup>(
      _spriteManager, glm::vec2(300.0f, 800.0f),
      std::static_pointer_cast<MainScene>(shared_from_this()));
  _weaponPickup->Init();

  _weaponUpgrader = std::make_shared<WeaponUpgrader>(_spriteManager);

  _respawnCountdown = std::make_shared<OnScreenCountdown>(
      _textManager, glm::vec2(GetApplication()->GetWidth() / 2.0f,
                              GetApplication()->GetHeight() / 2.0f));

  _scoreTextId = _textManager->AddText(
      "Score: 0", glm::vec2(GetApplication()->GetWidth() - 150, 10), 0.5f);
}

void MainScene::Update(float dt) {
  _eventManager->Update();
  GetInputHandler()->Update(dt);
  _respawnCountdown->Update();

  _camera->Update();
  _player->Update(dt);

  if (_player->IsAlive()) _enemyManager->Update(dt);

  if (_healthPickup->Alive()) {
    if (_player->GetSprite()->GetBounds()->Intersects(
            _healthPickup->GetSprite()->GetBounds())) {
      _healthPickup->Kill();
      _player->Heal();
    }
  }

  if (_weaponPickup->Alive()) {
    if (_player->GetSprite()->GetBounds()->Intersects(
            _weaponPickup->GetSprite()->GetBounds())) {
      _weaponPickup->Kill();
      auto curWeapon = _player->GetWeapon();
      auto newWeapon = _weaponUpgrader->UpgradeWeapon(curWeapon);

      if (newWeapon != curWeapon) {
        _player->SetWeapon(newWeapon);
      }
    }
  }
}

void MainScene::OnPlayerKilled() {
  if (_lives.size() > 0) {
    auto life = _lives[_lives.size() - 1];
    _uiManager->Remove(life);
    _lives.erase(_lives.end() - 1);

    _respawnCountdown->StartCountdown(5, [&]() { _player->Respawn(); });

  } else {
    _textManager->AddText("Loose - space to continue",
                          glm::vec2(GetApplication()->GetWidth() / 2.0f,
                                    GetApplication()->GetHeight() / 2.0f));
    GetInputHandler()->RegisterKey(GLFW_KEY_SPACE, [&](float) {
      GetApplication()->SetScene(GameOverScene::Name);
    });
  }
}

void MainScene::CreateLivesUI() {
  auto num_lives = _player->GetLives();
  const auto spacing = 10.0f;

  auto x = 10.0f;
  for (auto i = 0u; i < num_lives; ++i) {
    auto life = std::make_shared<Sprite>(
        "./data/textures/SpaceShooterRedux/PNG/UI/playerLife3_Red.png");
    life->SetPosition(std::move(glm::vec2(x, 10.0f)));
    _lives.push_back(life);
    _uiManager->Add(life);

    x += (life->GetWidth() + spacing);
  }
}

void MainScene::OnAllEnemyWavesComplete() {
  _textManager->AddText("Win", glm::vec2(GetApplication()->GetWidth() / 2.0f,
                                         GetApplication()->GetHeight() / 2.0f));
  _gameOverKeyBinding =
      GetInputHandler()->RegisterKey(GLFW_KEY_SPACE, [&](float) {
        GetApplication()->SetScene<GameOverScene>(_score);
        GetInputHandler()->UnregisterKey(_gameOverKeyBinding, GLFW_KEY_SPACE);
      });
}

void MainScene::OnEnemyKilled(EnemyWave::EnemyType enemyType) {
  switch (enemyType) {
    case EnemyWave::EnemyType::Drone:
      _score += 100;
      break;

    case EnemyWave::EnemyType::Ship:
      _score += 150;
      break;
  }

  _textManager->UpdateText(_scoreTextId, "score: " + std::to_string(_score));
}

void MainScene::Render() {
  _spriteManager->Render(_camera);
  _uiManager->Render();
  _textManager->Render();
}

void MainScene::OnLeave() {}
