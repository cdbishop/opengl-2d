#pragma once
#include <System/Camera2D.hpp>
#include <System/Scene.hpp>
#include <game/EnemyManager.hpp>
#include <game/healthPickup.hpp>
#include <game/onScreenCountdown.hpp>
#include <game/player.hpp>
#include <game/weaponPickup.hpp>
#include <game/weaponUpgrader.hpp>
#include <system/EventManager.hpp>
#include <system/SpriteManager.hpp>
#include <system/UIManager.hpp>
#include <system/collision/CollisionManager.hpp>

#include <array>
#include <memory>

#include <glm/gtc/type_ptr.hpp>

class Shader;
class Sprite;

class MainScene : public Scene {
 public:
  const static inline std::string Name = "MainScene";

  MainScene();
  ~MainScene();

  void Init() override;
  void Update(float dt) override;
  void Render() override;

  void OnLeave() override;

  Player::Ptr GetPlayer() const { return _player; }

 private:
  void OnPlayerKilled();
  void CreateLivesUI();
  void OnAllEnemyWavesComplete();
  void OnEnemyKilled(EnemyWave::EnemyType enemyType);

 private:
  SpriteManager::Ptr _spriteManager;
  UIManager::Ptr _uiManager;
  EventManager::Ptr _eventManager;
  TextManager::Ptr _textManager;
  EnemyManager::Ptr _enemyManager;

  Player::Ptr _player;
  Sprite::Ptr _background;

  HealthPickup::Ptr _healthPickup;
  WeaponPickup::Ptr _weaponPickup;

  WeaponUpgrader::Ptr _weaponUpgrader;

  Camera2D::Ptr _camera;

  std::vector<Sprite::Ptr> _lives;

  std::shared_ptr<OnScreenCountdown> _respawnCountdown;

  unsigned int _score;
  TextManager::Id _scoreTextId;
  InputHandler::Id _gameOverKeyBinding;
};
