#include "Camera2D.hpp"

Camera2D::Camera2D(glm::vec2 worldExtends, glm::vec2 viewSize)
  : _position(0.0f),
  _worldExtends(std::move(worldExtends)),
  _viewSize(viewSize) {}

void Camera2D::ClampToWorld() {
  if (_position.x < 0.0f) {
    _position.x = 0.0f;
  } else if (_position.x > (_worldExtends.x - _viewSize.x)) {
    _position.x = _worldExtends.x - _viewSize.x;
  }

  if (_position.y < 0.0f) {
    _position.y = 0.0f;
  } else if (_position.y > (_worldExtends.y - _viewSize.y)) {
    _position.y = _worldExtends.y - _viewSize.y;
  }
}

void Camera2D::Follow(std::shared_ptr<Sprite> sprite) { _target = sprite; }

void Camera2D::Update() {
  if (_target) {
    _position.x = _target->GetPosition().x - (_viewSize.x / 2.0f);
    _position.y = _target->GetPosition().y - (_viewSize.y / 2.0f);
    ClampToWorld();
  }
}
