#pragma once
#include <string>
#include <map>
#include <memory>

#include "Shader.hpp"

class ShaderManager
{
public:
	ShaderManager(std::string directory);
	~ShaderManager();

	std::shared_ptr<Shader> CreateProgram(const std::string& vertexShader, const std::string& fragmentShader);

private:
	void LoadVertexShader(const std::string& name, const std::string& data);
	void LoadFragmentShader(const std::string& name, const std::string& data);

private:
	std::map<std::string, unsigned int> _vertex_shaders;
	std::map<std::string, unsigned int> _fragment_shaders;
};
