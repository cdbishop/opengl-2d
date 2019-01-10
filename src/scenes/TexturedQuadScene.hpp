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
	std::array<float, 24> _vertices;

	unsigned int _vertex_buffer;
	unsigned int _vertex_array;

    int _width;
    int _height;

	std::shared_ptr<Shader> _shader;
	unsigned int _texture;

  glm::mat4 _projection;
};
