#include "ShaderManager.hpp"

#include <boost/filesystem.hpp>
#include <sstream>
#include <fstream>
#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace fs = boost::filesystem;

ShaderManager::ShaderManager(std::string directory)
{
	std::cerr << fs::current_path() << std::endl;

	// given a directory - will load all the files ending in .vert and .frag
	// will store vertex (.vert) and fragment (.frag) shaders by name as key
	// can request a program by specifiying .vert and .frag
	for (auto& file : fs::directory_iterator(directory)) {
		const auto& ext = file.path().extension();
		const auto& name = file.path().stem().string();
		if (ext == ".vert") {
			std::ifstream in(file.path().string());
			std::string str(static_cast<std::stringstream const&>(std::stringstream() << in.rdbuf()).str());
			LoadVertexShader(name, str);
		}
		else if (ext == ".frag") {
			std::ifstream in(file.path().string());
			std::string str(static_cast<std::stringstream const&>(std::stringstream() << in.rdbuf()).str());
			LoadFragmentShader(name, str);
		}
	}
}


ShaderManager::~ShaderManager()
{
	for (auto&& vert : _vertex_shaders) {
		glDeleteShader(vert.second);
	}

	for (auto&& frag : _fragment_shaders) {
		glDeleteShader(frag.second);
	}
}

std::shared_ptr<Shader> ShaderManager::CreateProgram(const std::string & vertexShader, const std::string & fragmentShader)
{
	unsigned int program = glCreateProgram();
	glAttachShader(program, _vertex_shaders.at(vertexShader));
	glAttachShader(program, _fragment_shaders.at(fragmentShader));
	glLinkProgram(program);

	int success = 0;
	char infoLog[512];
	glGetProgramiv(program, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(program, 512, NULL, infoLog);
		std::cerr << "Error Linking: " << vertexShader << " and " << fragmentShader << " Failed: " << infoLog << std::endl;
		throw std::runtime_error("Failed to compile shader");
	}

	return std::make_shared<Shader>(program);
}

void ShaderManager::LoadVertexShader(const std::string& name, const std::string& data)
{
	unsigned int vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	auto pSrc = static_cast<const GLchar* const>(data.c_str());
	glShaderSource(vertexShader, 1, &pSrc, NULL);
	glCompileShader(vertexShader);

	int success;
	char infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

	if (!success) {
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cerr << "Error Vertex Shader: " << name << " Compilation Failed: " << infoLog << std::endl;
	}

	_vertex_shaders[name] = vertexShader;
}

void ShaderManager::LoadFragmentShader(const std::string& name, const std::string& data)
{
	unsigned int fragmentShader;
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	auto pSrc = static_cast<const GLchar* const>(data.c_str());
	glShaderSource(fragmentShader, 1, &pSrc, NULL);
	glCompileShader(fragmentShader);

	int success;
	char infoLog[512];
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);

	if (!success) {
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		std::cerr << "Error Fragment Shader: " << name << " Compilation Failed: " << infoLog << std::endl;
	}

	_fragment_shaders[name] = fragmentShader;
}
