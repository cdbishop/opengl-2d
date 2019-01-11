#pragma once
#include <glm/vec2.hpp>

class Camera2D {
public:
  Camera2D();

  const glm::vec2& GetPosition() {
    return _position;
  }

  void SetPosition(const glm::vec2& pos) {
    _position = pos;
  }

  void SetPosition(glm::vec2&& pos) {
    _position = std::move(pos);
  }

  void Move(const glm::vec2& pos) {
    _position += pos;
  }

  void Move(glm::vec2&& pos) {
    _position += pos;
  }

private:
  glm::vec2 _position;
};