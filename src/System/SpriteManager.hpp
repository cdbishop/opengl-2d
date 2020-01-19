#pragma once
#include "object/Sprite.hpp"

#include "System/Camera2D.hpp"
#include "system/Shader.hpp"

#include <array>
#include <vector>

class SpriteManager {
public:
  using Ptr = std::shared_ptr<SpriteManager>;
  using SpriteVector = std::vector<Sprite::Ptr>;
  using SpriteLayerMap = std::map<unsigned int, SpriteVector>;

  SpriteManager(Shader::Ptr shader, glm::mat4 projection);
  ~SpriteManager();

  void Add(Sprite::Ptr sprite, unsigned int layer = 0);
  void RemoveFromLayer(Sprite::Ptr sprite, unsigned int layer);
  void Remove(Sprite::Ptr sprite);
  void Render(Camera2D::Ptr camera);

private:
  SpriteLayerMap _sprites;

  std::array<float, 24> _vertices;

  unsigned int _vertex_buffer;
  unsigned int _vertex_array;

  Shader::Ptr _shader;

  glm::mat4 _projection;
};