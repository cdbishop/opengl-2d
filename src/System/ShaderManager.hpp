#pragma once
#include <map>
#include <memory>
#include <string>

#include "Shader.hpp"

class ShaderManager {
public:
  using ShaderMap = std::map<std::string, unsigned int>;

  ShaderManager(const std::string& directory);
  ~ShaderManager();

  Shader::Ptr CreateProgram(const std::string& vertexShader,
    const std::string& fragmentShader);

private:
  void LoadVertexShader(const std::string& name, const std::string& data);
  void LoadFragmentShader(const std::string& name, const std::string& data);

private:
  ShaderMap _vertex_shaders;
  ShaderMap _fragment_shaders;
};
