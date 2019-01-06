#include "Shader.hpp"

Shader::Shader(unsigned int program)
	:_program(program) 
{
}

Shader::~Shader()
{
}

void Shader::SetVariableCb(const std::string & variable, UniformCallback callback)
{
	_uniform_callbacks[variable] = callback;
}

void Shader::UpdateUniforms()
{
	for (auto&& cb : _uniform_callbacks) {
		cb.second(cb.first, this);
	}
}

void Shader::UpdateUniform(const std::string & variable)
{
	_uniform_callbacks.at(variable)(variable, this);
}

unsigned int Shader::GetId()
{
	return _program;
}

bool Shader::HasUniform(const std::string& uniform) {
	int loc = glGetUniformLocation(_program, uniform.c_str());
	return loc >= 0;
}
