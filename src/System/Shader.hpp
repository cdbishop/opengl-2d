#pragma once
#include <map>
#include <limits>
#include <functional>

#include <glad/glad.h>

#include <glm/glm.hpp>

#include "..\Math\Vector.hpp"

class Shader
{
public:
  using UniformCallback = std::function<void(const std::string& variable, Shader*)>;  
  using Ptr = std::shared_ptr<Shader>;

	Shader(unsigned int program);
	~Shader();

	bool HasUniform(const std::string& variable);

	template<typename T>
	void SetUniformValue(const std::string& variable, const T& value);

	template<typename T>
	void SetUniformValuePtr(const std::string& variable, const T& value);

	void SetVariableCb(const std::string& variable, UniformCallback callback);

	void UpdateUniforms();

	unsigned int GetId();

private:
	void UpdateUniform(const std::string& variable);

	template<typename T, typename std::enable_if<std::is_same<T, glm::vec3>::value>::type...>
	void SetUniform(const std::string& variable, const glm::vec3& value) {
		glUniform3f(_uniforms[variable], value.x, value.y, value.z);
	}

	template<typename T, typename std::enable_if<std::is_integral<T>::value>::type...>
	void SetUniform(const std::string& variable, T value) {
		glUniform1i(_uniforms[variable], value);
	}

	template<typename T, typename std::enable_if<std::is_floating_point<T>::value>::type...>
	void SetUniform(const std::string& variable, float value) {
		glUniform1f(_uniforms[variable], value);
	}

	template<typename T, typename IsFloatPtr = typename std::enable_if<std::is_same<T, float*>::value>::type>
	void SetUniformPtr(const std::string& variable, T value) {
		glUniformMatrix4fv(_uniforms[variable], 1, GL_FALSE, value);
	}

private:
	unsigned int _program;
	std::map<std::string, unsigned int> _uniforms;

	std::map<std::string, UniformCallback> _uniform_callbacks;
};

template<typename T>
inline void Shader::SetUniformValue(const std::string & variable, const T & value)
{
	if (!_uniforms.count(variable)) {
		int loc = glGetUniformLocation(_program, variable.c_str());
		if (loc < 0) {
			throw std::runtime_error("Unable to find variable: " + variable + " in shader");
		}
		_uniforms[variable] = loc;
	}

	SetUniform<T>(variable, value);
}

template<typename T>
inline void Shader::SetUniformValuePtr(const std::string & variable, const T & value)
{
	if (!_uniforms.count(variable)) {
		int loc = glGetUniformLocation(_program, variable.c_str());
		if (loc < 0) {
			throw std::runtime_error("Unable to find variable: " + variable + " in shader");
		}
		_uniforms[variable] = loc;
	}

	SetUniformPtr(variable, value);
}
