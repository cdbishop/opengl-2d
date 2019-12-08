#pragma once
#include "object/Sprite.hpp"

#include "system/Shader.hpp"
#include "System/Camera2D.hpp"

#include <vector>
#include <array>

class UIManager {
public:
  using Ptr = std::shared_ptr<UIManager>;
  using SpriteVector = std::vector<Sprite::Ptr>;  

  UIManager(Shader::Ptr shader, glm::mat4 projection);
  ~UIManager();

  void Add(Sprite::Ptr sprite);
  void Remove(Sprite::Ptr sprite);
  void Render();

private:
  SpriteVector _sprites;

  std::array<float, 24> _vertices;

  unsigned int _vertex_buffer;
  unsigned int _vertex_array;

  Shader::Ptr _shader;

  glm::mat4 _projection;
};