#pragma once
#include "System/Camera2D.hpp"
#include "system/ShaderManager.hpp"

#include <array>
#include <vector>

class FTManager;

class TextManager {
 public:
  using Ptr = std::shared_ptr<TextManager>;
  using Id = size_t;

  TextManager(std::shared_ptr<ShaderManager> shaderManager,
              glm::mat4 projection);
  ~TextManager();

  Id AddText(std::string text, glm::vec2 position, float scale = 1.0f,
             glm::vec3 colour = glm::vec3(1.0f));
  void RemoveText(Id id);
  void UpdateText(Id id, std::string newValue);

  void Render();

 private:
  struct Text {
    std::string value;
    glm::vec2 position;
    glm::vec3 colour;
    float scale;
  };

  std::array<float, 24> _vertices;
  unsigned int _vertex_buffer;
  unsigned int _vertex_array;
  Shader::Ptr _shader;
  glm::mat4 _projection;
  std::shared_ptr<FTManager> _ft_manager;
  std::vector<Text> _texts;
};