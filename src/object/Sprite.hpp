#pragma once
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>

#include <string>

class Sprite {
public:
  explicit Sprite(const std::string& filepath);

  unsigned int GetTexture() const noexcept {
    return _texture;
  }

  unsigned int GetWidth() const noexcept {
    return _width;
  }

  unsigned int GetHeight() const noexcept {
    return _height;
  }

  glm::vec2 GetPosition() const noexcept {
    return _position;
  }

  glm::vec2 GetScale() const noexcept {
    return _scale;
  }

  glm::vec3 GetColour() const noexcept {
    return _colour;
  }

private:
  unsigned int _texture;
  unsigned int _width;
  unsigned int _height;

  glm::vec2 _position;
  glm::vec2 _scale;
  glm::vec3 _colour;
};