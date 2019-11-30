#pragma once
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>

#include <string>

#include <system/collision/BoundingBox.hpp>

class Sprite : public std::enable_shared_from_this<Sprite> {
public:
  using Ptr = std::shared_ptr<Sprite>;

  Sprite(const std::string& filepath);

  virtual ~Sprite();

  void UpdateBounds();

  BoundingBox::Ptr GetBounds() const noexcept {
    return _boundingBox;
  }

  unsigned int GetTexture() const noexcept {
    return _texture;
  }

  unsigned int GetWidth() const noexcept {
    return _width;
  }

  unsigned int GetHeight() const noexcept {
    return _height;
  }

  const glm::vec2& GetPosition() const noexcept {
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

  const glm::vec2& GetScale() const noexcept {
    return _scale;
  }

  const glm::vec3& GetColour() const noexcept {
    return _colour;
  }

  const glm::vec2& GetAnchor() const noexcept {
    return _anchor;
  }

  void SetAnchor(const glm::vec2& anchor) {
    _anchor = anchor;
  }

  void SetAnchor(glm::vec2&& anchor) {
    _anchor = std::move(anchor);
  }

  void SetRotation(float radians) {
    _rotation = radians;
  }

  float GetRotation() const noexcept {
    return _rotation;
  }

  void Rotate(float amount) {
    _rotation += amount;
  }
  
private:
  unsigned int _texture;
  unsigned int _width;
  unsigned int _height;

  glm::vec2 _position;
  glm::vec2 _anchor;
  float _rotation;
  glm::vec2 _scale;
  glm::vec3 _colour;

  BoundingBox::Ptr _boundingBox;
};