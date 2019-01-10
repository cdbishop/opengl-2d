#pragma once
#include <System/Scene.hpp>

#include <array>
#include <memory>

#include <glm/gtc/type_ptr.hpp>

class Shader;
class Sprite;

class MainScene : public Scene
{
public:
	MainScene();
	~MainScene();

  void Init();
	void Update();
	void Render();

private:
	std::array<float, 24> _vertices;

	unsigned int _vertex_buffer;
	unsigned int _vertex_array;

	std::shared_ptr<Shader> _shader;
	
  std::shared_ptr<Sprite> _sprite;

  glm::mat4 _projection;
};
