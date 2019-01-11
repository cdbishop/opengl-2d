#pragma once
#include "object/Sprite.hpp"

#include "system/Shader.hpp"
#include "System/Camera2D.hpp"

#include <vector>
#include <array>

class SpriteManager {
public:
  typedef std::shared_ptr<SpriteManager> Ptr;

  SpriteManager(Shader::Ptr shader, glm::mat4 projection);
  ~SpriteManager();

  void Add(Sprite::Ptr sprite);

  void Render(Camera2D::Ptr camera);

private:
  std::vector<Sprite::Ptr> _sprites;

  std::array<float, 24> _vertices;

  unsigned int _vertex_buffer;
  unsigned int _vertex_array;

  Shader::Ptr _shader;

  glm::mat4 _projection;
};