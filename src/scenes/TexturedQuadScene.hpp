#pragma once
#include <System/Scene.hpp>

#include <array>
#include <memory>

#include <glm/gtc/type_ptr.hpp>

class Shader;

class TexturedQuadScene : public Scene
{
public:
	TexturedQuadScene();
	~TexturedQuadScene();

	void Init();
	void Update();
	void Render();

private:
	std::array<float, 32> _vertices;
	std::array<unsigned int, 6> _indices;

	unsigned int _vertex_buffer;
	unsigned int _vertex_array;

	unsigned int _index_buffer;
	unsigned int _index_array;

	std::shared_ptr<Shader> _shader;
	unsigned int _texture;

  glm::mat4 _projection;
};
