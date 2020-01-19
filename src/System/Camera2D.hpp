#pragma once
#include <memory>

#include <glm/vec2.hpp>

#include <object/Sprite.hpp>

class Camera2D {
public:
  using Ptr = std::shared_ptr<Camera2D>;

  Camera2D(glm::vec2 worldExtends, glm::vec2 viewSize);

  const glm::vec2& GetPosition() { return _position; }

  void SetPosition(const glm::vec2& pos) { _position = pos; }

  void SetPosition(glm::vec2&& pos) { _position = std::move(pos); }

  void Move(const glm::vec2& pos) {
    _position += pos;
    ClampToWorld();
  }

  void Move(glm::vec2&& pos) {
    _position += pos;
    ClampToWorld();
  }

  void ClampToWorld();

  void Follow(Sprite::Ptr sprite);

  void Update();

private:
  glm::vec2 _position;
  glm::vec2 _worldExtends;
  glm::vec2 _viewSize;

  Sprite::Ptr _target;
};